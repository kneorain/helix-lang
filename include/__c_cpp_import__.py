from ctypes import CDLL as __CDLL__
from ctypes import cdll as __cpp_dll__
from os import makedirs as __os_makedirs__
from os import remove as __os_remove__
from subprocess import run as __subprocess_run__
from subprocess import PIPE as __PIPE__
from sys import stdout as __sys_stdout__
from threading import Thread as __thread__
from time import sleep as __sleep__
from os import path as __os_path__
from typing import Any
        
        
        
        
        
class __c_lib__():
    __lib_name__: str = ""
    __path__: str = ""
    __compiled_path__: str = ""
    __compiled__: list[str] = []
    __user_dir__: str = __os_path__.expanduser("~")
    __lib_ref__: Any = None
    
    @staticmethod
    def __c_cpp_import__(path: str, attr: str = ""):
        # TODO: add comments
        out = __c_lib__(path, attr).__lib_ref__
        return out

    def __init__(self, path: str, attr: str = ""):
        
        self.__lib_name__ = ''.join(__os_path__.basename(path).split(".")[:-1])
        self. __compiled_path__ = f"{__c_lib__.__user_dir__}/.helix/temp/gcc/{self.__lib_name__}.hx_c_lib"
        self. __path__ = __os_path__.abspath(path) if not __os_path__.isabs(path) else path
        
        if attr:
            if path.endswith(".cpp"):
                self.__lib_ref__ = getattr(__CDLL__(self.__compile_c_cpp__("g++")), attr)

            self.__lib_ref__ = getattr(__CDLL__(self.__compile_c_cpp__()), attr)
        
        if path.endswith(".cpp"):
            self.__lib_ref__ = __CDLL__(self.__compile_c_cpp__("g++"))

        self.__lib_ref__ = __CDLL__(self.__compile_c_cpp__())
    
    def __create_compile_dir__(self):
        """
        Creates the directory where compiled files will be stored.
        """
        
        if not __os_path__.exists(f"{__c_lib__.__user_dir__}/.helix/temp/gcc"):
            __os_makedirs__(f"{__c_lib__.__user_dir__}/.helix/temp/gcc")

    def __remove_compiled_files__():
        """
        Removes all compiled files from the directory.
        """
        
        for compiled_path in __c_lib__.__compiled__:
            __os_remove__(compiled_path)

    def __append_to_compiled__(self):
        """
        Adds a file to the list of compiled files.
        This is used to prevent the same file from being compiled multiple times.

        Args:
            path (str): The path to the file to be added.
        """
        
        __c_lib__.__compiled__.append(self.__compiled_path__)

    def __run_compile_command__(self, compiler: str):
        """
        Runs the compilation command.

        Args:
            compiler (str): The compiler to be used. Defaults to "gcc".
            compiled_path (str): The path to the compiled file.
            path (str): The path to the file to be compiled.
        """
        
        try:
            result = __subprocess_run__([compiler, "-shared", "-o", self.__compiled_path__, self.__path__], stderr=__PIPE__, text=True)
            if result.returncode != 0:
                print("\nGCC Compilation Error:\n", result.stderr)
                exit(1)
        except Exception as e:
            print("\nAn error occurred during compilation:", e)
            exit(1)

    def __compile_c_cpp__(self, compiler: str = "gcc") -> str:
        """
        Compiles a C or C++ file.

        Args:
            path (str): The path to the file to be compiled.
            compiler (str, optional): The compiler to be used. Defaults to "gcc".
        """
        
        if self.__compiled_path__ in __c_lib__.__compiled__:
            return self.__compiled_path__

        self.__create_compile_dir__()
        self.__append_to_compiled__()
        self.__run_compile_command__(compiler)
        
        return self.__compiled_path__