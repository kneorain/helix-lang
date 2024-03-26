from abc import ABC, abstractmethod
<<<<<<< HEAD
=======
import ctypes
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
from src.core.imports import (
    Any,
    Callable,
    Iterable,
    ModuleType,
    Namespace,
    Optional,
    Processed_Line,
    Scope,
<<<<<<< HEAD
    threading
)

=======
    threading,
    Token_List,
)

class Translate(ABC):
    @abstractmethod
    def __init__(self, ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope):
        pass
    @abstractmethod
    def parse(self) -> Processed_Line:
        pass


>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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

<<<<<<< HEAD
class ThreadedProcess:
=======
class ThreadedProcess(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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

<<<<<<< HEAD
class ArgParser:
=======
class ArgParser(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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

<<<<<<< HEAD
class HelixLanguage:
=======
class HelixLanguage(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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
<<<<<<< HEAD
    def remove_blank_lines(file: str, hash: Hashing | None) -> None:
        pass

class Timer:
=======
    def remove_blank_lines(file: str, hash: Optional[Hashing]) -> None:
        pass

class Timer(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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

<<<<<<< HEAD
class DisabledKeyboardInterrupt:
=======
class DisabledKeyboardInterrupt(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
    @abstractmethod
    def __enter__(self) -> None:
        pass
    @abstractmethod
    def handler(self, sig: int, frame: Any) -> None:
        pass
    @abstractmethod
    def __exit__(self, type: Any, value: Any, traceback: Any) -> None:
        pass

<<<<<<< HEAD
class Helix:
=======
class Helix(ABC):
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
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
<<<<<<< HEAD
    @abstractmethod
    def inject_core(self, code: Optional[str] = None, is_main: bool = True) -> str:
        pass
=======
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
    @staticmethod
    @abstractmethod
    def REPL() -> None:
        pass
    @classmethod
    @abstractmethod
    def __hook_import__(cls, file: str, *args: str, config_file: Optional[str] = None, **kwargs: Any) -> ModuleType:
        pass
<<<<<<< HEAD
=======


class Interop(ABC):
    cache_dir: str
    input_file: str
    output_file: str
    hash: Hashing

    @abstractmethod
    def __init__(self, input_file: str, *attrs: str) -> None:
        pass
    @abstractmethod
    def __getattr__(self, attr: str) -> Any:
        pass
    @abstractmethod
    def __setattr__(self, attr: str, value: Any) -> None:
        raise AttributeError("Cannot set attribute")
    @abstractmethod
    def __delattr__(self, attr: str) -> None:
        pass
    @abstractmethod
    def __compile__(self) -> None:
        pass
    @abstractmethod
    def get(self) -> tuple[ctypes.CDLL._FuncPtr, ...]:
        pass
    @abstractmethod
    def __del__(self) -> None:
        pass
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
