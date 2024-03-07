#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from __future__ import annotations
from datetime import datetime

import gc
gc.disable()

import os
import signal
import sys
import shutil
import hashlib
import threading
import subprocess
import functools
from sys import exit
from threading import Event
from io import TextIOWrapper
from types import ModuleType
from typing import Any, Callable, Iterable, Optional
from argparse import Namespace, ArgumentParser
from time import perf_counter_ns as time

from black import FileMode, format_file_contents
#from black.parsing import InvalidInput
from classes.Token import Processed_Line, Token_List

from globals import POOL, EARLY_REPLACEMENTS
from core.better_print import color_print as print
from core.token.tokenize_file import Tokenizer
from core.config import load_config
from core.panic import panic
from classes.Scope import Scope
from classes.Transpiler import Transpiler

__version__: str = "0.0.2-alpha.p"
PRODUCTION_BUILD: bool = False
USE_CACHE: bool = False

bar_thread = Event()

class ERROR_CODES:
    CLI_ARGUMENT = "[HEX-001]"
    
class Hashing:
    def __init__(self, file_path: str, output_path: str):
        file: TextIOWrapper = open(file_path, "r")
        self.__hash = Hashing.compute_hash(file.read())

        file.close()
        del file

        self.__output_path = output_path

    def __str__(self) -> str:
        return f"Hashing(hash={self.__hash}, output_path={self.__output_path})"

    def __repr__(self) -> str:
        return self.__str__()

    def __int__(self) -> int:
        return int.from_bytes(self.__hash, "big")

    @staticmethod
    def compute_hash(code: str) -> bytes:
        return hashlib.md5(code.encode("utf-8")).digest()

    def create_hash_only(self) -> None:
        open(self.__output_path + ":hash", "wb").write(self.__hash)
    
    @staticmethod
    def get_mount(path):
        path = os.path.realpath(os.path.abspath(path))
        while path != os.path.sep:
            if os.path.ismount(path):
                return path
            path = os.path.abspath(os.path.join(path, os.pardir))

        return path

    def __windows_io(self, writeable: str = "") -> Optional[bytes]:
        if writeable:
            with open(self.__output_path, "wb") as file, open(
                self.__output_path + ":hash", "wb"
            ) as ads:
                file.write(writeable.encode("utf-8"))
                ads.write(self.__hash)
        return open(self.__output_path + ":hash", "rb").read()

    def __linux_io(self, writeable: str = "") -> Optional[bytes]:
        import xattr
        
        if writeable:
            with open(self.__output_path, "wb") as file:
                file.write(writeable.encode("utf-8"))

            attr = xattr.xattr(self.__output_path)
            attr.set("user.hash", self.__hash)

        attr = xattr.xattr(self.__output_path)
        return attr.get("user.hash")

    def __io(self, writeable: str = "") -> Optional[bytes]:
        if sys.platform == "win32":
            return self.__windows_io(writeable)

        elif sys.platform in ["linux", "linux2", "darwin"]:
            return self.__linux_io(writeable)
        
        else:
            raise ImportError(
                "xattr library is required on Linux and macOS for setting extended attributes."
            )

    def create_file(self, code: str) -> None:
        try:
            self.__io(code)
        
        except ImportError:
            raise ImportError(
                "xattr library is required on Linux and macOS for setting extended attributes."
            )

        except PermissionError:
            raise PermissionError("You do not have permission to write to the file.")

        except FileNotFoundError:
            raise FileNotFoundError("The file does not exist.")

    def is_code_altered(self) -> bool:
        if not USE_CACHE:
            return True
        
        if (
            not os.path.exists(self.__output_path)
            or (os.path.exists(self.__output_path + ":hash") if sys.platform in ["linux", "linux2", "darwin"] else False)
        ):
            return True  # Hash file doesn't exist or is empty

        existing_hash = self.get_hash()
        if self.__hash != existing_hash:
            return True
        
        return False

    def get_hash(self) -> bytes | None:
        try:
            return self.__io()
        except FileNotFoundError:
            open(self.__output_path + ":hash", "wb").write(self.__hash)
        return None


def watch_processes() -> None:
    while True:
        for pid, thread in ThreadedProcess.__processes_queue__.items():
            if not thread.is_alive():
                ThreadedProcess.__processes_queue__[pid].join(1 / 1000)
                del ThreadedProcess.__processes_queue__[pid]

class ThreadedProcess:
    # TODO: GET DONE
    # this is supposed to be a threaded process decorator to be applied to fucntions
    # that are supposed to be run in a separate thread. the process can not have a return
    __processes_queue__: dict[int, threading.Thread] = {}

    def __new__(cls, func: Callable[..., None]):
        threading.Thread(target=watch_processes, daemon=True).start()
        return super().__new__(cls)

    def __init__(self, func: Callable[..., None]):
        self.__func__ = func
        functools.update_wrapper(self, func)

    def __call__(self, *args, **kwargs):
        def thread_target():
            try:
                self.__func__(*args, **kwargs)
            finally:
                try:
                    ThreadedProcess.__processes_queue__[self.__pid__].join(1 / 1000)
                except RuntimeError:
                    pass
                del ThreadedProcess.__processes_queue__[self.__pid__]

        self.__pid__ = id(self.__func__)
        self.__thread__ = threading.Thread(target=thread_target)
        self.__thread__.start()
        self.__class__.__processes_queue__[self.__pid__] = self.__thread__

        if not self.__thread__.is_alive():
            try:
                ThreadedProcess.__processes_queue__[self.__pid__].join(1 / 1000)
            except RuntimeError:
                pass
            del ThreadedProcess.__processes_queue__[self.__pid__]
            raise Exception("Thread has stopped unexpectedly.")

    @property
    def processes(self) -> dict[int, threading.Thread]:
        return self.__class__.__processes_queue__

    def __str__(self) -> str:
        return f"ThreadedProcess(func={self.__func__.__name__})"

    def __repr__(self) -> str:
        return self.__str__()


# @ThreadedProcess
# def test() -> None:
#    for i in range(10):
#        print(i)
#        sleep(1/3)

# test()


class ArgParser:
    def help_screen(self):
        print(
            """usage: helix [-h] [-v] [-o COMPILE] [-d] [-l LOG] [-c CONFIG] [-s] file ...
        
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
        """,
            word_wrap=False,
            end="",
        )
        exit()

    def version_screen(self):
        print(__version__)
        exit()

    def __init__(self, argv: Optional[Iterable[str]] = None):
        parser = ArgumentParser(
            description="Welcome to the Helix CLI, the gateway to harnessing the power and simplicity of Helix,"
            "a programming language designed for developers who cherish Python's ease but crave more"
            "robust features. This CLI tool empowers you to write, manage, and transpile Helix code"
            "with a range of commands and options tailored for a seamless development experience."
        )

        # Positional arguments
        parser.add_argument(
            "file", nargs="?", help="the name of the file to be executed"
        )
        parser.add_argument(
            "other", nargs="*", help="other arguments to be passed to the file as argv"
        )

        # Optional arguments
        parser.add_argument(
            "-v",
            "--version",
            action="store_true",
            help="show the version number and exit",
        )
        parser.add_argument(
            "-d", "--debug", action="store_true", help="enable debug mode"
        )
        parser.add_argument(
            "-w",
            "--watch",
            action="store_true",
            help="watch the file for changes and recompile",
        )
        parser.add_argument(
            "-s", "--silent", action="store_true", help="enable silent mode"
        )
        parser.add_argument("-r", "--run", action="store_true", help="run the file")
        parser.add_argument(
            "-o",
            "--compile",
            dest="compile_file",
            help="compile the file to a specific output file",
        )
        parser.add_argument(
            "-l", "--log", dest="log_file", help="the name of the log file"
        )
        parser.add_argument(
            "-c", "--config", dest="config_file", help="specify or create a config file"
        )
        parser.add_argument(
            "-i", "--install", dest="install_package", help="install new packages"
        )
        parser.add_argument(
            "-u", "--uninstall", dest="uninstall_package", help="uninstall packages"
        )
        parser.add_argument(
            "-doc",
            dest="store_true",
            help="the name of the documentation page to be displayed",
        )

        self.__args__ = parser.parse_args(argv)  # type: ignore

        # Handling version flag
        if self.__args__.version:
            self.version_screen()

        # Handling doc flag
        try:
            if self.__args__.doc:
                from docs.doc import doc

                doc(self.__args__.doc)
                exit()
        except AttributeError:
            pass

        if not self.__args__.file and not any(vars(self.__args__).values()):
            self.help_screen()

    @property
    def args(self) -> Namespace:
        return self.__args__

class HelixLanguage:
    def __init__(self, *args: str, **kwargs: str):
        raise NotImplementedError("Cannot instantiate HelixLanguage.")

    @staticmethod
    def make_folder(directory: str) -> None:
        if not os.path.isdir(directory):
            os.mkdir(directory)

    @staticmethod
    def make_file(file: str) -> None:
        if not os.path.exists(file):
            with open(file, "w", encoding="utf-8") as file:
                return

    @staticmethod
    def generate_folder_structure(
        directory: str = os.path.expanduser("~") + os.sep + ".helix",
    ):
        if os.path.isdir(directory) and os.listdir(directory) != []:
            return

        HelixLanguage.make_folder(directory)
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs"))
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs", "helix"))
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs", "c++"))
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs", "c"))
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs", "python"))
        HelixLanguage.make_folder(os.path.join(directory, "intl_libs", "rust"))

        HelixLanguage.make_folder(os.path.join(directory, "logs"))
        HelixLanguage.make_folder(os.path.join(directory, "temp"))
        HelixLanguage.make_folder(os.path.join(directory, "cache"))
        HelixLanguage.make_folder(os.path.join(directory, "cache", "build_cache"))
        HelixLanguage.make_folder(os.path.join(directory, "include"))

        HelixLanguage.make_file(os.path.join(directory, "config.json"))
        HelixLanguage.make_file(os.path.join(directory, "include", "core.py"))

    @staticmethod
    def install_helix(config: dict) -> None:
        if config["core_location"] != os.path.expanduser("~") + os.sep + ".helix":
            HelixLanguage.generate_folder_structure(config["core_location"])
        else:
            HelixLanguage.generate_folder_structure()

        if config["add_to_path"]:
            # permanently add to path
            print("Not yet implemented.")

        if config["add_to_desktop"]:
            # add to desktop
            print("Not yet implemented.")

class Timer:
    def __init__(self):
        self.__times: dict[str, tuple[float, float, int]] = {}  # name: (start, end, level)
        self.__active_timers = []  # Stack to keep track of active timers

    def start(self, name: str) -> None:
        self.__times[name] = (time(), 0, len(self.__active_timers))
        self.__active_timers.append(name)
        
    def end(self, name: str) -> None:
        self.__times[name] = (self.__times[name][0], time(), self.__times[name][2])
        self.__active_timers.remove(name)
        
    def get_time(self, name: str) -> float: # in ms
        start, end, _ = self.__times[name]
        return (end - start) / 1_000_000
    
    def __str__(self) -> str:
        result = []
        for name in self.__times:
            indent = "|    " * self.__times[name][2]
            result.append(f'{indent}"{name}" took {self.get_time(name):.2f}ms')
        return "\n".join(result)
    
    def __repr__(self) -> str:
        return self.__str__()

    def decorator(self, func: Callable) -> Callable:
        @functools.wraps(func)
        def wrapper(*args, **kwargs) -> Any:
            self.start(func.__name__)
            result = func(*args, **kwargs)
            self.end(func.__name__)
            return result
        return wrapper

class DisabledKeyboardInterrupt:
    def __enter__(self):
        self.signal_received = False
        self.old_handler = signal.signal(signal.SIGINT, self.handler)
                
    def handler(self, sig, frame):
        self.signal_received = (sig, frame)
        print("KeyboardInterrupt detected. use exit() to quit.", style="rgb(200, 50, 50)")
    
    def __exit__(self, type, value, traceback):
        signal.signal(signal.SIGINT, self.old_handler)
        if self.signal_received:
            self.old_handler(*self.signal_received)
    
    
class HelixProcess:
    config: Namespace

    @classmethod
    def interpreter(cls, code: str, globals_: dict, locals_: dict) -> str:
        inst: HelixProcess = cls(os.path.join(".helix", "config.json"), "__REPL__")
        
        tokenized_line: tuple[Token_List, ...] = Tokenizer.tokenize_line(code, inst.__file__, indent=1)
        scope_parsed: Scope   = Scope.process_from_lines(tokenized_line)
        transpiled_lines: list[Processed_Line] = Transpiler().transpile(scope_parsed, ignore_main=True)
        
        
        source_code: str = inst.generate_source_code(
            scope_parsed, transpiled_lines, False, is_main=False, no_inject=True
        )
        
        if not globals_ and not locals_:
            source_code = inst.inject_core(source_code, is_main=False)
        
        #print(source_code)
        code_block = compile(source_code, '<string>', 'exec')
        exec(code_block, globals_, locals_)
        
        return source_code
            

    def build_path(self) -> str:
        return os.path.join(
            ".helix",
            "cache",
            "build_cache",
            f"source_py_{os.path.basename(self.__file__).split('.')[0]}.py",
        )

    def remove_blank_lines(self, file: str, hash: Hashing | None) -> None:
        with open(file, "r") as read_file, open(file + ".tmp", "w") as write_file:
            for line in read_file:
                if line.strip():
                    write_file.write(line)
                    
        shutil.move(file + ".tmp", file)
        if hash:hash.create_hash_only()

    def __exit__(self, exc_type, exc_val, exc_tb):
        if POOL.is_alive:
            POOL.close()
        
    def __del__(self):
        if POOL.is_alive:
            POOL.close()
        
    def __delattr__(self, name):
        if POOL.is_alive:
            POOL.close()

    def __init__(self, conf_file: Optional[str] = None, *args: str, profile: bool = False, import_: bool = False):
        self.profile = profile
        self.import_ = import_
        
        self.timer = Timer()
        self.timer.start("init")
        self.timer.start("parse_args")
        
        if args and not import_:
            _args = ArgParser(args).args
        elif not args and import_:
            _args = ArgParser().args
        else:
            _args = Namespace()
            _args.file = args[0]
            _args.other = []
            
        self.timer.end("parse_args")
            
        if not _args.file:
            panic(
                FileNotFoundError("No file specified."),
                # code=ERROR_CODES.CLI_ARGUMENT, # TODO: add error codes
                line_no=1,
                no_lines=True,
            )

        if conf_file:
            self.__config_file__ = conf_file
        else:
            # TODO: add a default config file location
            raise NotImplementedError("Default config file location not implemented.")

        _args.other.insert(0, _args.file)
        self.__args__ = _args
        del _args

        self.__argv__ = self.__args__.other
        self.__file__ = self.__args__.file
        self.__format_out__ = False
        self.__out_file__ = self.build_path()  # TODO: custom output file
        
        if self.__file__ != "__REPL__":
            self.__file_hash__ = Hashing(self.__file__, self.__out_file__)
        else:
            self.__file_hash__ = None

        self.__class__.config = load_config(
            self.__config_file__
        )  # TODO: INTERGRATE CONFIG FILE

        self.timer.end("init")

    @classmethod
    def factory(cls, *args: str, **kwargs: Any) -> None:
        inst: HelixProcess = cls(*args, **kwargs)
        inst.compile_file()
        inst.run()
    
    def run(self) -> None:
        terminal_width = shutil.get_terminal_size().columns
        
        if os.path.exists(self.__out_file__):
            if self.profile:
                print(" Starting Compiled File ".center(terminal_width, "-"), style="red")
            
            self.timer.start("run")
            subprocess.Popen([sys.executable, self.__out_file__] + self.__argv__).wait()
            self.timer.end("run")
            
            if self.profile:
                print()
                print(" Finished Exec ".center(terminal_width, "-"), style="red")
        
        else:
            raise FileNotFoundError(
                "The file has been removed or modified before execution."
            )
            
        self.cleanup()
            
    def cleanup(self) -> None:
        if self.profile:
            print("Profile", style="bold")
            print(self.timer, border=True, style="bold")
            # print all the additional variables stroed in self
            print('\n'.join([f"{k}: {v}" for k, v in self.__dict__.items() if k.strip() not in ("__args__", "timer")]), style="bold", border=True)
    
    def compile_file(self, file: Optional[str] = None) -> Scope:
        self.timer.start("compile_file")

        scope_parsed, transpiled_lines = self.transpile(file if file else self.__file__)
        
        print(self.__file_hash__.is_code_altered())
        if self.__file_hash__.is_code_altered():
            self.__file_hash__.create_file(
                self.generate_source_code(
                    scope_parsed, transpiled_lines, self.__format_out__
                )
            )
            if not self.__format_out__:
                with open(self.__out_file__ + ".lines", "w") as f:
                    f.write(self.generate_line_numbers(transpiled_lines))
            
            self.timer.start("remove_blank_lines")
            self.remove_blank_lines(self.__out_file__ + ".lines", self.__file_hash__)
            self.remove_blank_lines(self.__out_file__, self.__file_hash__)
            self.timer.end("remove_blank_lines")
            
        self.timer.end("compile_file")
        
        return scope_parsed

    def transpile(
        self, file: Optional[str] = None
    ) -> tuple[Scope, list[Processed_Line]]:
        self.timer.start("transpile")
        input_file: str = file if file else self.__file__

        self.timer.start("tokenize_file")
        tokenized_file: tuple[Token_List, ...] = Tokenizer.tokenize_file(input_file)
        self.timer.end("tokenize_file")

        self.timer.start("process_from_lines")
        scope_parsed: Scope = Scope.process_from_lines(tokenized_file)
        self.timer.end("process_from_lines")

        # TODO: add fucntions and other namespace processing to scope, since at this point
        #       the scope is only processing the scope, and stuff like the functions
        #       are not being added to the scope.functions and so on.

        self.timer.start("Transpiler.transpile")
        transpiled_lines: list[Processed_Line] = Transpiler().transpile(scope_parsed)
        self.timer.end("Transpiler.transpile")

        # TODO: inject core here rather than in generate_source_code

        self.timer.end("transpile")
        return scope_parsed, transpiled_lines

    def generate_line_numbers(
        self, transpiled: list[Processed_Line]
    ) -> str:
        self.timer.start("generate_line_numbers")

        _line_numbers: list[str] = "\n".join(
            [
                "-1" if line != "\x92" else "\x92"
                for line in self.inject_core(None, is_main=not self.import_).splitlines()
                if line.strip()
            ]
        ).split("\x92")

        _line_numbers.insert(
            1, "\n".join([line.to_line_number() for line in transpiled])
        )
        line_numbers: str = "\n".join(
            [_ for _ in "\n".join(_line_numbers).splitlines() if _.strip()]
        )

        del _line_numbers
        
        self.timer.end("generate_line_numbers")
        return line_numbers

    def generate_source_code(
        self,
        scope_parsed: Scope,
        transpiled_lines: list[Processed_Line],
        format_source: bool = False,
        is_main: bool = True,
        no_inject: bool = False,
    ) -> str:
        self.timer.start("generate_source_code")
        
        if "main" not in scope_parsed.functions and is_main:
            panic(
                SyntaxError("No main function found."),
                file=self.__file__,
                line_no=1,
                no_lines=True,
            )

        transpiled_code: str = "\n".join(
            [
                _
                for _ in "\n".join(
                    [line.to_code() for line in transpiled_lines]
                ).splitlines()
                if _.strip()
            ]
        )

        self.timer.start("format_source")
        if format_source:
            # TODO: Handle InvalidInput
            transpiled_code = format_file_contents(
                transpiled_code, fast=True, mode=FileMode()
            )

        self.timer.end("format_source")
        self.timer.end("generate_source_code")
        print(self.inject_core(transpiled_code, is_main=is_main) if not no_inject else transpiled_code, is_main)
        return self.inject_core(transpiled_code, is_main=is_main) if not no_inject else transpiled_code

    def inject_core(self, code: Optional[str] = None, is_main: bool = True) -> str:
        inject_code = f"""# This file was automatically generated by the Helix transpiler
# Date, Time: {datetime.now().strftime("%Y-%m-%d %H:%M:%S")}
# Do not modify this file, as it will be overwritten\n
# License: CC0 1.0 Universal
# SPDX-License-Identifier: CC0-1.0\n
from __future__ import annotations
import os, sys
sys.path.append(os.path.dirname(os.path.realpath(\"{__file__.replace("\\", "\\\\")}\")))
sys.path.append(os.path.dirname(os.path.realpath(os.getcwd())))
from include.core import *\n
from include.core import __import_c__\n
import threading
import functools

__lock = threading.Lock()
__file__ = "{os.path.realpath(self.__file__).replace("\\", "\\\\")}"

def exception_handler(exception_type: type[BaseException], exception: Exception = None, tb: types.TracebackType = None, debug_hook: bool = False, thread_error: bool = False):
    import traceback, linecache, inspect, os
    from include.core import __tokenize_line__
    
    print()
    
    thread_name = None
    if thread_error:
        thread_name = exception_type.thread.name
        exception = exception_type.exc_value
        tb = exception_type.exc_traceback
        exception_type = exception_type.exc_type
        
    stack = traceback.extract_tb(tb)
    current_exception = exception
    relevant_frames = []

    early_replacements = dict((v, k) for k, v in {EARLY_REPLACEMENTS}.items())
    
    # First loop: filter out irrelevant frames
    index = 0
    for frame in stack:
        filename = frame.filename
        line_no = frame.lineno
        if "source_py_" in os.path.basename(filename):
            filename = __file__
            line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])
            
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
        index += 1
    
    if len(relevant_frames) > 1:
        __lock.acquire(blocking=True, timeout=1.2)
        for frame_info in relevant_frames:
            index, frame = frame_info
            filename = frame.filename
            line_no = frame.lineno

            if "source_py_" in os.path.basename(filename):
                filename = __file__
                line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])

            # Attempt to find the marked part in the error message
            # see if the frame contains colno and end_colno
            marks = None
            if hasattr(frame, "colno") and hasattr(frame, "end_colno"):
                marks = list(__tokenize_line__(frame._line[frame.colno:frame.end_colno]))
            try:
                file_ext =  os.path.basename(filename).split('.')[1]
            except IndexError:
                file_ext = "py"
            if marks:
                panic(
                    current_exception,
                    *marks,
                    file=filename,
                    line_no=line_no,
                    multi_frame=True,
                    pos=0 if index == 0 else 1 if index < len(relevant_frames) - 1 else 2,
                    replacements=early_replacements,
                    follow_marked_order=True,
                    mark_start=frame.colno,
                    thread_name=thread_name,
                    lang=file_ext
                )
            else:
                panic(
                    current_exception,
                    file=filename,
                    line_no=line_no,
                    replacements=early_replacements,
                    multi_frame=True,
                    pos=0 if index == 0 else 1 if index < len(relevant_frames) - 1 else 2,
                    thread_name=thread_name,
                    lang=file_ext
                )
            current_exception = current_exception.__cause__ if current_exception.__cause__ else current_exception
        else:
            __lock.release()
            exit(1)
    else:
        __lock.acquire(blocking=True, timeout=0.1)
        index, frame = relevant_frames[0]
        filename = frame.filename
        line_no = frame.lineno

        if "source_py_" in filename:
            filename = sys.argv[0]
            line_no = int(open(frame.filename + ".lines", "r").readlines()[line_no])
        
        # Attempt to find the marked part in the error message
        # see if the frame contains colno and end_colno
        marks = None
        if hasattr(frame, "colno") and hasattr(frame, "end_colno"):
            marks = list(__tokenize_line__(frame._line[frame.colno:frame.end_colno]))
        
        try:
            file_ext =  os.path.basename(filename).split('.')[1]
        except IndexError:
            file_ext = "py"
        if marks:
            panic(
                current_exception,
                *marks,
                file=filename,
                line_no=line_no,
                replacements=early_replacements,
                no_exit=True,
                follow_marked_order=True,
                mark_start=frame.colno,
                thread_name=thread_name,
                lang=file_ext
            )
        else:
            panic(
                current_exception,
                file=filename,
                line_no=line_no,
                replacements=early_replacements,
                no_exit=True,
                thread_name=thread_name,
                lang=file_ext
            )
            
        __lock.release()
        exit(1)

sys.excepthook = exception_handler
threading.excepthook = functools.partial(exception_handler, thread_error=True)

def __internal_replace_argv(args: list[str]) -> list[str]:
    sys.argv = ["{self.__file__.replace("\\", "\\\\")}"] + list(args)[2:]
    return sys.argv\n

\x92

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
    """
        if not is_main:
            return inject_code.split('\x92')[0] + (code if code else "\x92")
        
        if code is not None:
            return inject_code.replace("\x92", code)
        else:
            return inject_code
    
    @staticmethod
    def REPL() -> None:
        # this is a repl environment for helix
        locals_: dict[str, Any] = {}
        globals_: dict[str, Any] = {}
        context: tuple[dict[str, Any], dict[str, Any]] = (globals_, locals_)
        
        with DisabledKeyboardInterrupt():
            prev_code: str = ""
            code: str = ""
            while True:
                try:
                    code = input(">>> ").strip()
                    if code.strip() == "--code":
                        print(HelixProcess.interpreter(prev_code, *context))
                        continue
                    prev_code = code
                except (KeyboardInterrupt, EOFError):
                    pass
                
                if code.strip() == "exit()":
                    break
                
                if not code.strip():
                    if prev_code:
                        code = prev_code
                    else:
                        continue
                
                HelixProcess.interpreter(code, *context)
    
    @classmethod
    def __import__(cls, file: str, *args: str, config_file: Optional[str] = None, **kwargs: Any) -> ModuleType:
        config_file = config_file if config_file else os.path.join(".helix", "config.json")
        
        inst: HelixProcess = cls(config_file, file, *args, import_=True, **kwargs)
        scope = inst.compile_file(file)
        
        # append the loc to path and import it
        sys.path.append(os.path.dirname(os.path.realpath(inst.__out_file__)))
        helix_import: ModuleType = __import__(os.path.basename(inst.__out_file__).split('.')[0])

        # for everyhting in scope, look if anyhting is marked as private, if so remove it from helix import
        remove = ["__internal_replace_argv", "exception_handler"]

        # scope coantains, .fucntions, .classes, .variables, , and then .children with more scopes
        
        
        for k, v in scope.functions.items():
            if v["private"]:
                remove.append(k)
                
        for k, v in scope.classes.items():
            if v["private"]:
                remove.append(k)
                
        for k, v in scope.variables.items():
            if v["private"]:
                remove.append(k)
                
        # remove all the private ones from helix_import
        for private in remove:
            delattr(helix_import, private)
        
        return helix_import
        

if __name__ == "__main__":
    try:
        HelixProcess.factory(os.path.join(".helix", "config.json"), "-r", "syntax/test.hlx", profile=False)
    finally:
        gc.collect(0)
        gc.collect(1)
        gc.collect(2)
    #test_hlx = HelixProcess.__import__("syntax/test.hlx")
    #print(test_hlx.subtract(5, 3))
    #HelixProcess.REPL()