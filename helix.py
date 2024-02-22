#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__version__: str = "0.0.2-alpha.p"
PRODUCTION_BUILD: bool = False

import os
import sys
import tempfile
from classes.Token import Token, Token_List
from core.better_print import color_print as print
from core.token.tokenize_file import Tokenizer
from argparse import Namespace, ArgumentParser
from classes.Transpiler import Transpiler
from core.compile_bar import show_bar
from black import FileMode, format_file_contents
from core.config import load_config
from classes.Scope import Scope
from time import perf_counter_ns as time
from globals import POOL
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
    parser.add_argument('file', nargs='?', help='the name of the file to be executed')
    parser.add_argument('doc', nargs='?', help='the name of the documentation page to be displayed')
    parser.add_argument('other', nargs='*', help='other arguments to be passed to the file as argv')
    
    # Optional arguments
    parser.add_argument('-v', '--version', action='store_true', help='show the version number and exit')
    parser.add_argument('-o', '--compile', dest='compile_file', help='compile the file to a specific output file')
    parser.add_argument('-d', '--debug', action='store_true', help='enable debug mode')
    parser.add_argument('-l', '--log', dest='log_file', help='the name of the log file')
    parser.add_argument('-c', '--config', dest='config_file', help='specify or create a config file')
    parser.add_argument('-s', '--silent', action='store_true', help='enable silent mode')
    parser.add_argument('-w', '--watch', action='store_true', help='watch the file for changes and recompile')
    parser.add_argument('-i', '--install', dest='install_package', help='install new packages')
    parser.add_argument('-u', '--uninstall', dest='uninstall_package', help='uninstall packages')
    parser.add_argument('-doc', dest='doc', help='the name of the documentation page to be displayed')

    args = parser.parse_args()

    # Handling version flag
    if args.version:
        version_screen()
        
    # Handling doc flag
    if args.doc:
        from docs.doc import doc
        doc(args.doc)
        exit()

    # Handling help flag
    if not args.file and not any(vars(args).values()):
        help_screen()

    return args
    
def main():
    args = parse_args()
    args.other.insert(0, args.file)
    
    start = time()
    
    a = Tokenizer.tokenize_file("syntax/test.hlx")
    b = Scope.process_from_lines(a)
    c = Transpiler.transpile(b)
 
    code = '\n'.join([c.to_code() for c in c])
    code =  (
           "# This file was automatically generated by the Helix transpiler\n"
        +  "# Do not modify this file, as it will be overwritten\n\n"
        +  "# License: CC0 1.0 Universal\n"
        +  "# SPDX-License-Identifier: CC0-1.0\n\n"
        +  "import os, sys\n"
        + f"sys.path.append(os.path.dirname(os.path.realpath(\"{__file__.replace("\\", "\\\\")}\")))\n"
        + f"sys.path.append(os.path.dirname(os.path.realpath(os.getcwd())))\n"
        + f"from include.core import *\n\n"
        +  "from include.core import __import_c__\n\n"
        + code + "\n\n"
        + f"if __name__ == '__main__':\n"
        +  "    try:\n"
        + f"        main(hx_list([{(', '.join([f'\"{_}\"'.replace('\\', '\\\\') for _ in args.other])).strip()}]).__set_generic__(\"[str]\"))\n"
        +  "    except DispatchError:\n"
        +  "        main()\n"
    )
    #code = format_file_contents(code, fast=True, mode=FileMode())

    output_path = "output" + ".py"
    with open(output_path, "w", encoding="utf-8") as file:
        file.write(code)
        #print(code)
    try:
        os.system(f"{sys.executable} {output_path}")
    finally:
        #os.remove(output_path)
        pass
        
    print("\n", (time()-start) / 10000000, " ms to transpile and run the code.")
    
    #import subprocess, sys
    #subprocess.run([sys.executable, "output.py"], shell=True)
    
    POOL.close()

def start():
    try:
        main()
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        bar_thread.set()
        
if __name__ == "__main__":
    start()
    
# _iprcgml