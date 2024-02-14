#!/usr/bin/env python3
HELIX_VERSION = "Helix 1.0.0"
PRODUCTION_BUILD = False

from core.better_print import color_print as print
from core.token.tokenize_file import tokenize_file
from argparse import Namespace, ArgumentParser
from classes.Transpiler import Transpiler
from core.compile_bar import show_bar
from core.config import save_config
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
    print(HELIX_VERSION)
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
    #args = parse_args()

    start = time()
    
    a = tokenize_file("syntax/syntax.hlx")
    b = Scope.process_from_lines(a)
    c = Transpiler.transpile(b)
    
    print((time()-start) / 1_000_000, " ms")
    POOL.close()
    exit()
    #i: Token_List
    #for i in a:
    #    print(("    "*i.indent_level) + str(i))
    
    bar_thread.set()

if __name__ == "__main__":
    try:
        # 7357813 function calls (7918273 primitive calls) in 1.235 ms  (close to 18000 lines of code)
        # 3420506 function calls (3369961 primitive calls) in 0.803 ms  (close to 10000 lines of code)
        # 1052186 function calls (1037209 primitive calls) in 0.044 ms (close to 3000 lines of code)
        # 274039 function calls (268734 primitive calls) in 0.013 ms   (close to 1000 lines of code)
        # 93556 function calls (92307 primitive calls) in 0.008 ms     (close to 200 lines of code)
        # 65722 function calls (65097 primitive calls) in 0.005 ms     (close to 100 lines of code)
        main()
    except KeyboardInterrupt:
        print("Exiting...")
        exit()
    finally:
        bar_thread.set()