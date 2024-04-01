import src.core.core as core
from src.core.imports import (
    exit,
    Iterable,
    Namespace, ArgumentParser, Optional,
    color_print as print,
    framework,
)

class ArgParser(framework.ArgParser):
    """
    Parses command-line arguments for the Helix language application.

    Attributes
    ----------
    __args__ : Incomplete
        Parsed arguments from the command line.

    Methods
    -------
    help_screen(self) -> None
        Displays the help screen with usage instructions.
    version_screen(self) -> None
        Displays the version information of the Helix language.
    __init__(self, argv: Optional[Iterable[str]] = None)
        Initializes the argument parser with command-line arguments.
    args(self) -> Namespace
        Returns the namespace of parsed command-line arguments.
    """
    def help_screen(self):
        print(core.clean_docstring("""usage: helix [-h] [-v] [-o COMPILE] [-d] [-l LOG] [-c CONFIG] [-s] file ...

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
            The internal repl environment does not work at the moment.
            \u001b[32m
            WARN: This version of Helix is being \u001b[1;91mDeprecated.\u001b[0m\u001b[32m
            NOTE: This entire language is being rewritten with some key changes:
            \t- Syntax (.hlx) will remain the same as the current version.
            \t- The language will no longer be transpiled it will be compiled.
            \t- The compiler will be written in C++, Rust and Python.
            \t- The language will be more powerful and more robust.
            \t- The language will be faster.
            \t- The language will be more secure.
            \u001b[0m
        """),
            word_wrap=False,
            end="",
        )
        exit()

    def version_screen(self):
        print("🧬 " + self.__version__)
        exit()

    def __init__(
        self, argv: Optional[Iterable[str]] = None, version: str = "NOT SET"
    ):
        self.__version__ = version
        parser = ArgumentParser(
            description="Welcome to the Helix CLI, the gateway to harnessing the power and simplicity of Helix,"
            "a programming language designed for developers who cherish Python's ease but crave more"
            "robust features. This CLI tool empowers you to write, manage, and transpile Helix code"
            "with a range of commands and options tailored for a seamless development experience."
        )

        # Positional arguments
        parser.add_argument(
            "file",
            nargs="?",
            help="the name of the file to be executed",
        )
        parser.add_argument(
            "other",
            nargs="*",
            help="other arguments to be passed to the file as argv",
        )

        # Optional arguments
        parser.add_argument(
            "-v",
            "--version",
            action="store_true",
            help="show the version number and exit",
        )
        parser.add_argument(
            "-d",
            "--debug",
            action="store_true",
            help="enable debug mode",
        )
        parser.add_argument(
            "-w",
            "--watch",
            action="store_true",
            help="watch the file for changes and recompile",
        )
        parser.add_argument(
            "-s",
            "--silent",
            action="store_true",
            help="enable silent mode",
        )
        parser.add_argument(
            "-r",
            "--reset_cache",
            action="store_true",
            help="recompile the file and store in cache",
        )
        parser.add_argument(
            "-o",
            "--compile",
            dest="compile_file",
            help="compile the file to a specific output file",
        )
        parser.add_argument(
            "-l",
            "--log",
            dest="log_file",
            help="the name of the log file",
        )
        parser.add_argument(
            "-c",
            "--config",
            dest="config_file",
            help="specify or create a config file",
        )
        parser.add_argument(
            "-i",
            "--install",
            dest="install_package",
            help="install new packages",
        )
        parser.add_argument(
            "-u",
            "--uninstall",
            dest="uninstall_package",
            help="uninstall packages",
        )
        parser.add_argument(
            "-doc",
            dest="store_true",
            help="the name of the documentation page to be displayed",
        )

        self.__args__ = parser.parse_args(argv)  # type: ignore

        if self.__args__.reset_cache:
            core.USE_CACHE = False
        
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

        if not self.__args__.file and not any(
            vars(self.__args__).values()
        ):
            self.help_screen()
            

    @property
    def args(self) -> Namespace:
        return self.__args__
