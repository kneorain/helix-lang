#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from __future__ import annotations
PRODUCTION_BUILD = True
import gc
gc.disable() # disable garbage collection for performance

import atexit

import src.core.core as core
from src.core.imports import (
    os,
    sys,
    Any,
    Tuple,
    panic,
    Event,
    Timer,
    Scope,
    signal,
    shutil,
    CONFIG,
    Hashing,
    Callable,
    Optional,
    Namespace,
    FrameType,
    Tokenizer,
    ArgParser,
    framework,
    ModuleType,
    subprocess,
    Transpiler,
    py_compile,
    inject_core,
    HelixLanguage,
    color_print as print,
    perf_counter_ns as time,
    Processed_Line, Token_List,
)

__version__: str = "0.10.0-alpha.a"
bar_thread = Event()

class DisabledKeyboardInterrupt(framework.DisabledKeyboardInterrupt):
    """
    Context manager for temporarily disabling KeyboardInterrupt exceptions.

    This class is used to disable KeyboardInterrupt (Ctrl+C) handling
    in critical sections of code where interruption could cause issues.

    Attributes
    ----------
    signal_received : Incomplete
        Stores any signal received during the disabled period.
    old_handler : Incomplete
        The original signal handler.

    Methods
    -------
    __enter__(self) -> None
        Enters a block with KeyboardInterrupt disabled.
    handler(self, sig: int, frame: Any) -> None
        Custom signal handler for signals received during the disabled period.
    __exit__(self, type: Any, value: Any, traceback: Any) -> None
        Restores the original signal handler upon exiting the block.
    """
    def __enter__(self) -> None:
        self.signal_received: Optional[Tuple[int, Any]] = (
            None
        )
        self.old_handler: (
            Callable[[int, FrameType | None], Any]
            | int
            | None
        ) = signal.signal(signal.SIGINT, self.handler)

    def handler(self, sig: int, frame: Any) -> None:
        self.signal_received = (sig, frame)
        print(
            "KeyboardInterrupt detected. use exit() to quit.",
            style="rgb(200, 50, 50)",
        )

    def __exit__(
        self, type: Any, value: Any, traceback: Any
    ) -> None:
        signal.signal(signal.SIGINT, self.old_handler)
        if self.signal_received:
            self.old_handler(*self.signal_received)  # type: ignore

class Helix(framework.Helix):
    """
    Main class for the Helix programming language interpreter and compiler.

    Attributes
    ----------
    config : Namespace
        Configuration namespace for Helix.
    profile : Incomplete
        Profiling attribute for performance analysis.

    Methods
    -------
    __init__(self, conf_file: Optional[str] = None, *args: str,
             profile: bool = False, import_: bool = False)
        Initialize the Helix interpreter/compiler with configuration.
    factory(cls, config_file: str, *args: str, **kwargs: Any)
        Factory method to create Helix instances.
    run(self)
        Runs the Helix interpreter/compiler.
    cleanup(self)
        Performs cleanup operations.
    compile_file(self, file: Optional[str] = None) -> Scope
        Compiles the specified Helix file.
    transpile(self,
              file: Optional[str] = None) -> tuple[Scope, list[Processed_Line]]
        Transpiles the specified Helix file to another language.
    generate_line_numbers(self, transpiled: list[Processed_Line]) -> str
        Generates line numbers for the transpiled code.
    generate_source_code(self, scope_parsed: Scope,
                         transpiled_lines: list[Processed_Line],
                         format_source: bool = False,
                         is_main: bool = True,
                         no_inject: bool = False) -> str
        Generates source code from parsed scope and transpiled lines.
    REPL() -> None
        Launches the Helix Read-Eval-Print Loop.
    __hook_import__(cls,
                    file: str,
                    *args: str,
                    config_file: Optional[str] = None,
                    **kwargs: Any) -> ModuleType
        Hook method for importing modules in Helix.
    """
    config: Any

    @classmethod
    def interpreter(
        cls, code: str, globals_: dict, locals_: dict
    ) -> str:
        inst: Helix = cls(
            os.path.join(".helix", "config.toml"),
            "__REPL__",
        )

        tokenized_line: tuple[Token_List, ...] = (
            Tokenizer.tokenize_line(
                code, inst.__file__, indent=1
            )
        )
        scope_parsed: Scope = Scope.process_from_lines(
            tokenized_line
        )
        transpiled_lines: list[
            Processed_Line
        ] = Transpiler().transpile(
            scope_parsed, ignore_main=True
        )

        source_code: str = inst.generate_source_code(
            scope_parsed,
            transpiled_lines,
            False,
            is_main=False,
            no_inject=True,
        )

        if not globals_ and not locals_:
            source_code = inject_core(
                inst,
                source_code,
                is_main=False,
                __version__=__version__,
                __file__=__file__
            )

        # print(source_code)
        code_block = compile(
            source_code, "<string>", "exec"
        )
        exec(code_block, globals_, locals_)

        return source_code

    def build_path(self) -> str:
        return os.path.join(
            ".helix",
            "cache",
            "build_cache",
            f"{os.path.basename(self.__file__).split('.')[0]}_hlx.hir",
        )

    def __init__(
        self,
        conf_file: Optional[str] = None,
        *args: str,
        profile: bool = False,
        import_: bool = False,
    ):
        self.profile = profile
        self.import_ = import_

        self.timer = Timer()
        self.timer.start("init")
        self.timer.start("parse_args")

        if args and not import_:
            _args = ArgParser(args, __version__).args
        elif not args and not import_:
            _args = ArgParser(version=__version__).args
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
            raise NotImplementedError(
                "Default config file location not implemented."
            )

        _args.other.insert(0, _args.file)
        self.__args__ = _args
        del _args

        self.__argv__ = self.__args__.other
        self.__file__ = self.__args__.file
        self.__format_out__ = False
        self.__out_file__ = (
            self.build_path()
        )  # TODO: custom output file
        self.__file_hash__: Optional[Hashing] = None
        if self.__file__ != "__REPL__":
            self.__file_hash__ = Hashing(
                self.__file__, self.__out_file__
            )

        self.__class__.config = CONFIG

        self.timer.end("init")

    @classmethod
    def factory(
        cls, config_file: str, *args: str, **kwargs: Any
    ) -> None:
        inst: Helix = cls(
            config_file, *args, **kwargs
        )
        inst.compile_file()
        inst.run()

    def run(self) -> None:
        terminal_width = shutil.get_terminal_size().columns

        if os.path.exists(self.__out_file__):
            if self.profile:
                print(
                    " Starting Compiled File ".center(
                        terminal_width, "-"
                    ),
                    style="red",
                )

            if core.COMPILE:
                py_compile.compile(self.__out_file__, cfile=self.__out_file__, optimize=2)
            
            self.timer.start("run")
            try:
                subprocess.Popen(
                    [sys.executable, self.__out_file__]
                    + self.__argv__
                ).wait()
            except KeyboardInterrupt:
                pass
            self.timer.end("run")

            if self.profile:
                print()
                print(
                    " Finished Exec ".center(
                        terminal_width, "-"
                    ),
                    style="red",
                )

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
            print(
                "\n".join(
                    [
                        f"{k}: {v}"
                        for k, v in self.__dict__.items()
                        if k.strip()
                        not in ("__args__", "timer")
                    ]
                ),
                style="bold",
                border=True,
            )
        
        gc.collect(0)
        gc.collect(1)
        gc.collect(2)
        

    def compile_file(
        self, file: Optional[str] = None
    ) -> Scope:
        self.timer.start("compile_file")

        scope_parsed, transpiled_lines = self.transpile(
            file if file else self.__file__
        )

        if self.__file_hash__ is None:
            raise ValueError("File hash is None.")

        if self.__file_hash__.is_code_altered():
            self.__file_hash__.create_file(
                self.generate_source_code(
                    scope_parsed,
                    transpiled_lines,
                    self.__format_out__,
                )
            )
            if not self.__format_out__:
                with open(
                    self.__out_file__ + ".lines", "w"
                ) as f:
                    f.write(
                        self.generate_line_numbers(
                            transpiled_lines
                        )
                    )

            self.timer.start("remove_blank_lines")
            HelixLanguage.remove_blank_lines(
                self.__out_file__ + ".lines",
                self.__file_hash__,
            )
            HelixLanguage.remove_blank_lines(
                self.__out_file__, self.__file_hash__
            )
            self.timer.end("remove_blank_lines")

        self.timer.end("compile_file")

        return scope_parsed

    def transpile(
        self, file: Optional[str] = None
    ) -> tuple[Scope, list[Processed_Line]]:
        self.timer.start("transpile")
        input_file: str = file if file else self.__file__

        self.timer.start("tokenize_file")
        tokenized_file: tuple[Token_List, ...] = (
            Tokenizer.tokenize_file(input_file)
        )
        self.timer.end("tokenize_file")

        self.timer.start("process_from_lines")
        scope_parsed: Scope = Scope.process_from_lines(
            tokenized_file
        )
        self.timer.end("process_from_lines")

        # TODO: add fucntions and other namespace processing to scope, since at
        #       this point the scope is only processing the scope, and stuff
        #       like the functions are not being added to the scope.functions
        #       and so on.

        self.timer.start("Transpiler.transpile")
        transpiled_lines: list[Processed_Line] = (
            Transpiler().transpile(scope_parsed)
        )
        self.timer.end("Transpiler.transpile")

        # TODO: inject core here rather than in generate_source_code

        self.timer.end("transpile")
        return scope_parsed, transpiled_lines

    def generate_line_numbers(
        self, transpiled: list[Processed_Line]
    ) -> str:
        self.timer.start("generate_line_numbers")

        _line_numbers: list[str] = str("\n".join(
            [
                "-1" if line != "\x92" else "\x92"
                for line in inject_core(
                    self, None, is_main=not self.import_, __version__=__version__, __file__=__file__
                ).splitlines()
                if line.strip()
            ]
        )).split("\x92")

        _line_numbers.insert(
            1,
            str("\n".join(
                [
                    line.to_line_number()
                    for line in transpiled
                ]
            )),
        )
        line_numbers: str = "\n".join(
            [
                _
                for _ in "\n".join(
                    _line_numbers
                ).splitlines()
                if _.strip()
            ]
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
                    [
                        line.to_code()
                        for line in transpiled_lines
                    ]
                ).splitlines()
                if _.strip()
            ]
        )

        self.timer.start("format_source")

        self.timer.end("format_source")
        self.timer.end("generate_source_code")

        return (
            inject_core(
                self, transpiled_code, is_main=is_main, __version__=__version__, __file__=__file__
            )
            if not no_inject
            else transpiled_code
        )

    @staticmethod
    def REPL() -> None:
        # this is a repl environment for helix
        locals_: dict[str, Any] = {}
        globals_: dict[str, Any] = {}
        context: tuple[dict[str, Any], dict[str, Any]] = (
            globals_,
            locals_,
        )

        # TODO: add auto printing, and also indentation for multiline inputs

        with DisabledKeyboardInterrupt():
            prev_code: str = ""
            code: str = ""
            while True:
                try:
                    code = input(">>> ").strip()
                    if code.strip() == "--code":
                        print(
                            Helix.interpreter(
                                prev_code, *context
                            )
                        )
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

                Helix.interpreter(code, *context)

    @classmethod
    def __hook_import__(
        cls,
        file: str,
        *args: str,
        config_file: Optional[str] = None,
        **kwargs: Any,
    ) -> ModuleType:
        config_file = (
            config_file
            if config_file
            else os.path.join(".helix", "config.toml")
        )

        inst: Helix = cls(
            config_file, file, *args, import_=True, **kwargs
        )
        scope = inst.compile_file(file)

        sys.path.append(
            os.path.dirname(
                os.path.realpath(inst.__out_file__)
            )
        )

        # Create a temporary module to hold the imported content
        module_name = os.path.basename(file).split(".")[0]
        helix_import = __import__(
            os.path.basename(inst.__out_file__).split(".")[
                0
            ]
        )

        # Set the file and name for the module
        helix_import.__file__ = inst.__out_file__
        helix_import.__name__ = module_name

        # Update sys.modules
        sys.modules[helix_import.__name__] = helix_import

        # Process scope items
        remove = []
        for attr, value in {
            **scope.functions,
            **scope.classes,
            **scope.variables,
        }.items():
            if "private" in value: # CHANGED from: if value.get("private", False):
                remove.append(attr)

        # Clean up private attributes
        for private in remove:
            delattr(helix_import, private)

        return helix_import

    def __del__(self) -> None:
        gc.collect(0)
        gc.collect(1)
        gc.collect(2)
        
def exit_func(*args: Any) -> None:
    if core.POOL.is_alive:
        core.POOL.close()
    
    #print("Memory Usage: ", tracemalloc.get_traced_memory()[1] / 10**6, "MB")
    
    gc.collect(0)
    gc.collect(1)
    gc.collect(2)

atexit.register(exit_func)
signal.signal(signal.SIGTERM, exit_func)

if __name__ == "__main__":
    Helix.factory(
        os.path.join(".helix", "config.toml"),
        profile=True,
    )
    #Helix.__hook_import__("syntax/test.hlx")
    # from test_hlx import subtract
    # subtract(5, 3)
    