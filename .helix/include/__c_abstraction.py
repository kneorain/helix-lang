from abc import ABC, abstractmethod

class c_interop_abstraction(ABC):
    @abstractmethod
    def __import__(path: str, attr: str = ""):
        pass
    
    @abstractmethod
    def __create_compile_dir__():
        """
        Creates the directory where compiled files will be stored.
        """
        pass
    @abstractmethod
    def __remove_compiled_files__():
        """
        Removes all compiled files from the directory.
        """
        pass
    @abstractmethod
    def __append_to_compiled__(path: str):
        """
        Adds a file to the list of compiled files.
        This is used to prevent the same file from being compiled multiple times.

        Args:
            path (str): The path to the file to be added.
        """
        pass
    @abstractmethod
    def __run_compile_command__(compiler: str, compiled_path: str, path: str):
        """
        Runs the compilation command.

        Args:
            compiler (str): The compiler to be used. Defaults to "gcc".
            compiled_path (str): The path to the compiled file.
            path (str): The path to the file to be compiled.
        """
        pass
    @abstractmethod
    def __compile_c_cpp__(path: str, compiler: str = "gcc"):
        """
        Compiles a C or C++ file.

        Args:
            path (str): The path to the file to be compiled.
            compiler (str, optional): The compiler to be used. Defaults to "gcc".
        """
        pass