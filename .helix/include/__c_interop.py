from ctypes import CDLL as __CDLL__
from os import makedirs as __os_makedirs__
from os import path as __os_path__
from os import remove as __os_remove__
from subprocess import PIPE as __PIPE__
from subprocess import run as __subprocess_run__
from typing import Any, NoReturn, override

from include.__c_abstraction import c_interop_abstraction as __c_interop_abstraction__


class __c_lib__(__c_interop_abstraction__):
    __lib_name__: str = ""
    __path__: str = ""
    __compiled_path__: str = ""
    __compiled__: list[str] = []
    __user_dir__: str = __os_path__.expanduser("~")
    __lib_ref__: Any = None

    @staticmethod
    def __import__(path: str, attr: str = ""):
        out = __c_lib__(path, attr).__lib_ref__
        return out

    @override
    def __init__(self, path: str, attr: str = ""):
        self.__lib_name__ = "".join(__os_path__.basename(path).split(".")[:-1])
        self.__compiled_path__ = (
            f"{__c_lib__.__user_dir__}\\.helix\\temp\\gcc\\{self.__lib_name__}.hx_c_lib"
        )
        self.__path__ = (
            __os_path__.abspath(path) if not __os_path__.isabs(path) else path
        )

        if attr:
            if path.endswith(".cpp"):
                self.__lib_ref__ = getattr(
                    __CDLL__(self.__compile_c_cpp__("clang++")), attr
                )

            self.__lib_ref__ = getattr(__CDLL__(self.__compile_c_cpp__()), attr)

        if path.endswith(".cpp"):
            self.__lib_ref__ = __CDLL__(self.__compile_c_cpp__("clang++"))

        self.__lib_ref__ = __CDLL__(self.__compile_c_cpp__())

    @override
    def __create_compile_dir__(self):
        if not __os_path__.exists(f"{__c_lib__.__user_dir__}\\.helix\\temp\\gcc"):
            __os_makedirs__(f"{__c_lib__.__user_dir__}\\.helix\\temp\\gcc")

    @override
    @staticmethod
    def __remove_compiled_files__():
        for compiled_path in __c_lib__.__compiled__:
            __os_remove__(compiled_path)

    @override
    def __append_to_compiled__(self):
        __c_lib__.__compiled__.append(self.__compiled_path__)

    def __run_compile_command__(self, compiler: str) -> NoReturn:
        try:
            result = __subprocess_run__(
                [compiler, "-shared", "-o", self.__compiled_path__, self.__path__],
                stderr=__PIPE__,
                text=True,
            )
            if result.returncode != 0:
                print("\nGCC Compilation Error:\n", result.stderr)
        except Exception as e:
            print("\nAn error occurred during compilation:", e)
        exit(1)

    def __compile_c_cpp__(self, compiler: str = "clang") -> str:
        if self.__compiled_path__ in __c_lib__.__compiled__:
            return self.__compiled_path__

        self.__create_compile_dir__()
        self.__append_to_compiled__()
        self.__run_compile_command__(compiler)

        return self.__compiled_path__
