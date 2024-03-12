from abc import ABC, abstractmethod
from src.core.imports import (
    Any,
    Callable,
    Iterable,
    ModuleType,
    Namespace,
    Optional,
    Processed_Line,
    Scope,
    threading
)

class Hashing(ABC):
    @abstractmethod
    def __init__(self, file_path: str, output_path: str) -> None:
        pass
    @abstractmethod
    def __int__(self) -> int:
        pass
    @staticmethod
    @abstractmethod
    def compute_hash(code: str) -> bytes:
        pass
    @abstractmethod
    def create_hash_only(self) -> None:
        pass
    @staticmethod
    @abstractmethod
    def get_mount(path):
        pass
    @abstractmethod
    def create_file(self, code: str) -> None:
        pass
    @abstractmethod
    def is_code_altered(self) -> bool:
        pass
    @abstractmethod
    def get_hash(self) -> bytes | None:
        pass

class ThreadedProcess:
    __processes_queue__: dict[int, threading.Thread]
    @abstractmethod
    def __new__(cls, func: Callable[..., None]):
        pass
    @abstractmethod
    def __init__(self, func: Callable[..., None]) -> None:
        pass
    @abstractmethod
    def __call__(self, *args, **kwargs) -> None:
        pass
    @property
    @abstractmethod
    def processes(self) -> dict[int, threading.Thread]:
        pass

class ArgParser:
    @abstractmethod
    def help_screen(self) -> None:
        pass
    @abstractmethod
    def version_screen(self) -> None:
        pass
    @abstractmethod
    def __init__(self, argv: Optional[Iterable[str]] = None) -> None:
        pass
    @property
    @abstractmethod
    def args(self) -> Namespace:
        pass

class HelixLanguage:
    @abstractmethod
    def __init__(self, *args: str, **kwargs: str) -> None:
        pass
    @staticmethod
    @abstractmethod
    def make_folder(directory: str) -> None:
        pass
    @staticmethod
    @abstractmethod
    def make_file(file: str) -> None:
        pass
    @staticmethod
    @abstractmethod
    def generate_folder_structure(directory: str = ...):
        pass
    @staticmethod
    @abstractmethod
    def install_helix(config: dict) -> None:
        pass
    @staticmethod
    @abstractmethod
    def remove_blank_lines(file: str, hash: Hashing | None) -> None:
        pass

class Timer:
    @abstractmethod
    def __init__(self) -> None:
        pass
    @abstractmethod
    def start(self, name: str) -> None:
        pass
    @abstractmethod
    def end(self, name: str) -> None:
        pass
    @abstractmethod
    def get_time(self, name: str) -> float:
        pass
    @abstractmethod
    def decorator(self, func: Callable) -> Callable:
        pass

class DisabledKeyboardInterrupt:
    @abstractmethod
    def __enter__(self) -> None:
        pass
    @abstractmethod
    def handler(self, sig: int, frame: Any) -> None:
        pass
    @abstractmethod
    def __exit__(self, type: Any, value: Any, traceback: Any) -> None:
        pass

class Helix:
    @classmethod
    @abstractmethod
    def interpreter(cls, code: str, globals_: dict, locals_: dict) -> str:
        pass
    @abstractmethod
    def build_path(self) -> str:
        pass
    @abstractmethod
    def __init__(self, conf_file: Optional[str] = None, *args: str, profile: bool = False, import_: bool = False) -> None:
        pass
    @classmethod
    @abstractmethod
    def factory(cls, config_file: str, *args: str, **kwargs: Any) -> None:
        pass
    @abstractmethod
    def run(self) -> None:
        pass
    @abstractmethod
    def cleanup(self) -> None:
        pass
    @abstractmethod
    def compile_file(self, file: Optional[str] = None) -> Scope:
        pass
    @abstractmethod
    def transpile(self, file: Optional[str] = None) -> tuple[Scope, list[Processed_Line]]:
        pass
    @abstractmethod
    def generate_line_numbers(self, transpiled: list[Processed_Line]) -> str:
        pass
    @abstractmethod
    def generate_source_code(self, scope_parsed: Scope, transpiled_lines: list[Processed_Line], format_source: bool = False, is_main: bool = True, no_inject: bool = False) -> str:
        pass
    @abstractmethod
    def inject_core(self, code: Optional[str] = None, is_main: bool = True) -> str:
        pass
    @staticmethod
    @abstractmethod
    def REPL() -> None:
        pass
    @classmethod
    @abstractmethod
    def __hook_import__(cls, file: str, *args: str, config_file: Optional[str] = None, **kwargs: Any) -> ModuleType:
        pass
