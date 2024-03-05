#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__version__: str = "0.0.2-alpha.p"
PRODUCTION_BUILD: bool = False
USE_CACHE: bool = True

import hashlib
from io import FileIO
import mmap
import os
import shutil
import subprocess
import sys
from typing import IO, Generator, Optional

from core.better_print import color_print as print
from core.panic import panic
from core.token.tokenize_file import Tokenizer
from argparse import Namespace, ArgumentParser
from classes.Transpiler import Transpiler
from core.compile_bar import show_bar
from black import FileMode, format_file_contents, InvalidInput
from core.config import load_config
from classes.Scope import Scope
from time import perf_counter_ns as time, sleep
from globals import POOL, EARLY_REPLACEMENTS
from threading import Event
from sys import exit

bar_thread = Event()

class UNICODE_ERROR_LINERS:
    left_starting  =  "├",
    right_starting =  "┤",
    down_right     = ["┐", "╮"]
    down_left      = ["┌", "╭"]
    up_left        = ["└", "╰"]
    up_right       = ["┘", "╯"]
    vertical       =  "│"
    horizontal     =  "─"
    underline      =  "~"

class ERROR_CODES:
    cli_argument = "[HEX-001]"

def help_screen():
    print("""usage: helix [-h] [-v] [-o COMPILE] [-d] [-l LOG] [-c CONFIG] [-s] file ...

Welcome to the Helix CLI, the gateway to harnessing the power and simplicity of Helix,
a programming language designed for developers who cherish Python's ease but crave more
robust features. This CLI tool empowers you to write, manage, and transpile Helix code
with a range of commands and options tailored for a seamless development experience.

positional arguments:
  file                  the name of the file to be executed
  doc                   the name of the documentation page to be displayed
  other                 other arguments to be passed to the file as argv

options:
  -h, --help                         show this help message and exit
  -v, --version                      show the version number and exit
  -o COMPILE, --compile COMPILE_FILE compile the file to a specific output file
  -d, --debug                        enable debug mode
  -l LOG, --log LOG_FILE             the name of the log file
  -c CONFIG, --config CONFIG_FILE    specify or create a config file
  -s, --silent                       enable silent mode
  -w, --watch                        watch the file for changes and recompile
  -i, --install PACKAGE_NAME         install new packages
  -u, --uninstall PACKAGE_NAME       uninstall packages
  -doc DOC                           the name of the documentation page to be displayed
""", word_wrap=False, end="")
    exit()
    
def version_screen():
    print(__version__)
    exit()

def parse_args() -> Namespace:
    parser = ArgumentParser(
        description="Welcome to the Helix CLI, the gateway to harnessing the power and simplicity of Helix,"
                    "a programming language designed for developers who cherish Python's ease but crave more"
                    "robust features. This CLI tool empowers you to write, manage, and transpile Helix code"
                    "with a range of commands and options tailored for a seamless development experience."
    )
    
    # Positional arguments
    parser.add_argument('file',  nargs='?', help='the name of the file to be executed')
    parser.add_argument('other', nargs='*', help='other arguments to be passed to the file as argv')
    
    # Optional arguments
    parser.add_argument('-v', '--version', action='store_true',        help='show the version number and exit')
    parser.add_argument('-d', '--debug',   action='store_true',        help='enable debug mode')
    parser.add_argument('-w', '--watch',   action='store_true',        help='watch the file for changes and recompile')
    parser.add_argument('-s', '--silent',  action='store_true',        help='enable silent mode')
    parser.add_argument('-r', '--run',     action='store_true',        help='run the file')
    parser.add_argument('-o', '--compile',   dest='compile_file',      help='compile the file to a specific output file')
    parser.add_argument('-l', '--log',       dest='log_file',          help='the name of the log file')
    parser.add_argument('-c', '--config',    dest='config_file',       help='specify or create a config file')
    parser.add_argument('-i', '--install',   dest='install_package',   help='install new packages')
    parser.add_argument('-u', '--uninstall', dest='uninstall_package', help='uninstall packages')
    parser.add_argument('-doc',              dest='store_true',        help='the name of the documentation page to be displayed')

    args = parser.parse_args()

    # Handling version flag
    if args.version:
        version_screen()
        
    # Handling doc flag
    try:
        if args.doc:
            from docs.doc import doc
            doc(args.doc)
            exit()
    except AttributeError:
        pass

    # Handling help flag
    if not args.file and not any(vars(args).values()):
        help_screen()

    return args

def init_code(code: str, path: str, no_code=False) -> str:
    return f"""# This file was automatically generated by the Helix transpiler
# Do not modify this file, as it will be overwritten\n
# License: CC0 1.0 Universal
# SPDX-License-Identifier: CC0-1.0\n
from __future__ import annotations
import os, sys
sys.path.append(os.path.dirname(os.path.realpath(\"{__file__.replace("\\", "\\\\")}\")))
sys.path.append(os.path.dirname(os.path.realpath(os.getcwd())))
from include.core import *\n
from include.core import __import_c__\n

def exception_handler(exception_type: type[BaseException], exception: Exception, tb: types.TracebackType, debug_hook: bool = False):
    import traceback, linecache, inspect
    stack = traceback.extract_tb(tb)
    current_exception = exception
    relevant_frames = []

    early_replacements = dict((v, k) for k, v in {EARLY_REPLACEMENTS}.items())
    
    # First loop: filter out irrelevant frames
    for index, frame in enumerate(reversed(stack)):
        filename = frame.filename
        line_no = frame.lineno

        if "source_py_" in filename:
            filename = sys.argv[0]
            line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])
            print(f"{{filename}}:{{line_no}}")
            if line_no == -1:
                continue

        # Check specific conditions to skip
        if (
            linecache.getline(filename, line_no-1).strip() == "func = self.dispatch(*args)"
            and
            linecache.getline(filename, line_no).strip() == "return func(*args, **kwargs)"
        ):
            continue
        
        relevant_frames.append((index, frame))
    
    # Second loop: process each relevant frame
    if len(relevant_frames) > 1:
        for frame_info in relevant_frames:
            index, frame = frame_info
            filename = frame.filename
            line_no = frame.lineno

            if "source_py_" in filename:
                filename = sys.argv[0]
                line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])

            # repalce early replacements within the current_exception message
            current_exception.__str__ = lambda: current_exception.__str__().format(**early_replacements)
        
            panic(
                current_exception,
                file=filename,
                line_no=line_no,
                multi_frame=True,
                pos=0 if index == 0 else 1 if index < len(stack) - 1 else 2,
                replacements=early_replacements
            )
            current_exception = current_exception.__cause__ if current_exception.__cause__ else current_exception
        else:
            exit(1)
    else:
        index, frame = relevant_frames[0]
        filename = frame.filename
        line_no = frame.lineno

        if "source_py_" in filename:
            filename = sys.argv[0]
            line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])

        panic(
            current_exception,
            file=filename,
            line_no=line_no,
            replacements=early_replacements
        )

sys.excepthook = exception_handler\n

def __internal_replace_argv(args: list[str]) -> list[str]:
    sys.argv = ["{path.replace("\\", "\\\\")}"] + list(args)[2:]
    return sys.argv\n
    

----------------------------------------------- code -----------------------------------------------

if __name__ == "__main__":
    try:
        try:
            main(hx_list(__internal_replace_argv(sys.argv)).__set_generic__("[str]"))
        except TypeError:
            try:
                main()
            except KeyboardInterrupt as e2:
                panic(
                    e2.__cause__,
                    ":",
                    file=inspect.stack()[0].filename,
                    line_no=e2.__traceback__.tb_lineno,
                )
    except KeyboardInterrupt as e2:
        panic(
            e2.__cause__,
            ":",
            file=inspect.stack()[0].filename,
            line_no=e2.__traceback__.tb_lineno,
        )
""".replace("----------------------------------------------- code -----------------------------------------------", code if not no_code else "__CODE_GOES_HERE__")

def generate_source_code(file: str, format_source: bool = False) -> str:
    a = Tokenizer.tokenize_file(file)
    b = Scope.process_from_lines(a)
    # TODO: add fucntions and other namespace processing to scope, since at this point
    #       the scope is only processing the scope, and stuff like the functions
    #       are not being added to the scope.functions and so on.
    c = Transpiler.transpile(b)
    if "main" not in b.functions:
        panic(
            SyntaxError("No main function found."),
            file=file,
            line_no=1,
            no_lines=True
        )
    
    code: str = '\n'.join([c.to_code() for c in c]).splitlines()
    # remove blank lines
    code = '\n'.join([_ for _ in code if _.strip()])
    line_numbers: str = '\n'.join(
        ["-1" if _ != "__CODE_GOES_HERE__" else "__CODE_GOES_HERE__" for _ in init_code(None, file, True).splitlines() if _.strip()]
    )
    line_numbers = line_numbers.split("__CODE_GOES_HERE__")
    line_numbers.insert(1, '\n'.join([c.to_line_number() for c in c]))

    line_numbers = '\n'.join(line_numbers)
    line_numbers = '\n'.join([_ for _ in line_numbers.splitlines() if _.strip()])

    if format_source:
        try:
            code = format_file_contents(code, fast=True, mode=FileMode())
        except InvalidInput as e:
            # extract the line number and column number from the error message
            import inspect, traceback , re
            line_no, col_no = map(int, re.findall(r'\d+', str(e)))
            print(f"Error: {e}\n")
            exit(1)
    return init_code(code, file), line_numbers

def remove_blank_lines(file: str) -> None:
    with open(file, 'r') as read_file, open(file + ".tmp", 'w') as write_file:
        for line in read_file:
            if line.strip():
                write_file.write(line)
    shutil.move(file + ".tmp", file)

class Hashing:
    def __init__(self, file_path: str, output_path: str):
        file: FileIO = open(file_path, 'r')
        self.__hash  = Hashing.compute_hash(file.read())
        
        file.close()
        del file
        
        self.__output_path = output_path
    
    @staticmethod
    def compute_hash(code: str) -> bytes:
        return hashlib.md5(code.encode('utf-8')).digest()
    
    @staticmethod
    def getmount(path):
        path = os.path.realpath(os.path.abspath(path))
        while path != os.path.sep:
            if os.path.ismount(path):
                return path
            path = os.path.abspath(os.path.join(path, os.pardir))
        return path

    def generate_meta(self, code: str) -> None:
        if sys.platform == "win32":
            with open(self.__output_path, 'wb') as file, open(self.__output_path + ':hash', 'wb') as ads:
                file.write(code.encode('utf-8'))
                ads. write(self.__hash)
                
        elif sys.platform in ["linux", "linux2", "darwin"]:
            with open(self.__output_path, 'wb') as file:
                file.write(code.encode('utf-8'))
            try:
                import xattr
                attr = xattr.xattr(self.__output_path)
                attr.set('user.hash', self.__hash)
            except ImportError:
                print("xattr library is required on Linux and macOS for setting extended attributes.")
    
    def is_code_altered(self) -> bool:
        if not USE_CACHE:
            return True
        if not os.path.exists(self.__output_path) or os.path.getsize(self.__output_path) < 16:
            return True  # Hash file doesn't exist or is empty

        existing_hash = self.get_hash()
        
        if self.__hash != existing_hash:
            return True

        return False

    def get_hash(self) -> bytes | None:
        if sys.platform == "win32":
            try:
                with open(self.__output_path + ':hash', 'rb') as ads:
                    return ads.read()
            except FileNotFoundError:
                return None
        elif sys.platform in ["linux", "linux2", "darwin"]:
            try:
                import xattr
                attr = xattr.xattr(self.__output_path)
                return attr.get('user.hash')
            except (ImportError, KeyError):
                return None

def make_folder(directory: str) -> None:
    if not os.path.isdir(directory):
        os.mkdir(directory)

def make_file(file: str) -> None:
    if not os.path.exists(file):
        with open(file, "w", encoding="utf-8") as file:
            return

def generate_folder_structure(directory: str = os.path.expanduser("~") + os.sep + ".helix"):
    if os.path.isdir(directory) and os.listdir(directory) != []:
        return
    
    make_folder(directory)
    make_folder(os.path.join(directory, "intl_libs"))
    make_folder(os.path.join(directory, "intl_libs", "helix"))
    make_folder(os.path.join(directory, "intl_libs", "c++"))
    make_folder(os.path.join(directory, "intl_libs", "c"))
    make_folder(os.path.join(directory, "intl_libs", "python"))
    make_folder(os.path.join(directory, "intl_libs", "rust"))
    
    make_folder(os.path.join(directory, "logs"))
    make_folder(os.path.join(directory, "temp"))
    make_folder(os.path.join(directory, "cache"))
    make_folder(os.path.join(directory, "cache", "build_cache"))
    make_folder(os.path.join(directory, "include"))
    
    make_file  (os.path.join(directory, "config.json"))
    make_file  (os.path.join(directory, "include", "core.py"))

def install_helix(config: dict) -> None:
    if config["core_location"] != os.path.expanduser("~") + os.sep + ".helix":
        generate_folder_structure(config["core_location"])
    else:
        generate_folder_structure()
        
    if config["add_to_path"]:
        import sys
        # permanently add to path
        print("Not yet implemented.")
        
    if config["add_to_desktop"]:
        # add to desktop
        print("Not yet implemented.")

def remove_from_file(file_path: str, line: bytes, whence: int = 0) -> bool:
    """Remove all lines after a specified line is reached in a file.
    whence can be 0 for from start, and 1 for from end."""
    line_found = False

    if whence == 0:
        # From start
        temp_file_path = file_path + ".tmp"
        with open(file_path, 'rb') as file, open(temp_file_path, 'wb') as temp_file:
            for file_line in file:
                temp_file.write(file_line)
                if file_line.strip() == line:
                    line_found = True
                    break

        if line_found:
            # Replace original file with temporary file
            shutil.move(temp_file_path, file_path)
        else:
            # Remove the temporary file if line not found
            os.remove(temp_file_path)

    else:
        # From end
        with open(file_path, 'r+b') as file:
            file.seek(0, os.SEEK_END)
            file_size = file.tell()
            buffer_size = 8192  # Larger buffer size for faster reads
            buffer = b''
            current_pos = file_size

            while current_pos > 0:
                size_to_read = min(buffer_size, current_pos)
                file.seek(current_pos - size_to_read)
                chunk = file.read(size_to_read)
                buffer = chunk + buffer
                current_pos -= size_to_read

                line_pos = buffer.find(line)
                if line_pos != -1:
                    # Calculate the position to truncate
                    truncate_pos = current_pos + line_pos
                    if buffer[line_pos:].lstrip().startswith(b'\n'):
                        truncate_pos += 1
                    file.truncate(truncate_pos)
                    line_found = True
                    break

    return line_found

def main():
    args = parse_args()
    args.other.insert(0, args.file)
    pass_args = args.other

    # generate output file name eg: source_py_{file}.py
    generate_folder_structure(".helix")
    start = time()
    
    output_path = ".helix" + os.sep + "cache" + os.sep + "build_cache" + os.sep + f"source_py_{os.path.basename(args.file).split('.')[0]}.py"
    hash = Hashing(args.file, output_path)

    if hash.is_code_altered() or args.run:
        code, line_numbers = generate_source_code(args.file, format_source=False)
        hash . generate_meta(code)
        with open(output_path + ".lines", "w") as file:
            file.write(line_numbers)
        remove_blank_lines(output_path + ".lines")
        remove_blank_lines(output_path)
    
    end = time()
    if os.path.exists(output_path):
        os.system(f"{sys.executable} {output_path} {' '.join(pass_args)}")
    else:
        raise FileNotFoundError("The file has been removed or modified before execution.")

    print("\n", f"{(time()-start) / 1_0000_000} ms to transpile and run the code.")
    print(f"{(time()-end) / 1_0000_000} ms to run only the code.")
    print(f"{(end-start) / 1_0000_000} ms to transpile only the code.")
    print(f"code output path: {output_path}")

    #import subprocess, sys
    #subprocess.run([sys.executable, "output.py"], shell=True)

    POOL.close()

def start():
    try:
        main()
    except KeyboardInterrupt:
        print("Exiting...")
        
if __name__ == "__main__":
    start()
    
# _iprcgml