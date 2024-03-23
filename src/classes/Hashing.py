from __future__ import annotations
import src.core.base as base
from src.core.imports import (
    os,
    sys,
    hashlib,
    Optional,
    TextIOWrapper,
    framework,
)


class Hashing(framework.Hashing):
    """
    Provides functionality for hashing and comparing hashes of code files.

    Attributes
    ----------
    file_path : str
        The path to the file to be hashed.
    output_path : str
        The path where the hash output should be stored.

    Methods
    -------
    __init__(self, file_path: str, output_path: str)
        Initializes the Hashing object with file paths.
    compute_hash(code: str) -> bytes
        Computes and returns the hash of the given code.
    create_hash_only(self)
        Creates a hash of the file at file_path and stores it at output_path.
    get_mount(path)
        Retrieves the mount point for the given path.
    create_file(self, code: str)
        Creates a file with the given code and hashes it.
    is_code_altered(self) -> bool
        Checks if the code has been altered compared to its stored hash.
    get_hash(self) -> bytes | None
        Retrieves the hash of the file if it exists.
    """
    def __init__(self, file_path: str, output_path: str):
        file: TextIOWrapper = open(file_path, "r")
        self.__hash = Hashing.compute_hash(file.read())

        file.close()
        del file

        self.__output_path = output_path

    def __str__(self) -> str:
        try:
            return f"Hashing(hash={self.__hash.decode()}, output_path={self.__output_path})"
        except UnicodeDecodeError:
            return f"Hashing(hash={repr(self.__hash)}, output_path={self.__output_path})"

    def __repr__(self) -> str:
        return self.__str__()

    def __int__(self) -> int:
        return int.from_bytes(self.__hash, "big")

    @staticmethod
    def compute_hash(code: str) -> bytes:
        return hashlib.md5(code.encode("utf-8")).digest()

    def create_hash_only(self) -> None:
        open(self.__output_path + ":hash", "wb").write(
            self.__hash
        )

    @staticmethod
    def get_mount(path):
        path = os.path.realpath(os.path.abspath(path))
        while path != os.path.sep:
            if os.path.ismount(path):
                return path
            path = os.path.abspath(
                os.path.join(path, os.pardir)
            )

        return path

    def __windows_io(
        self, writeable: str = ""
    ) -> Optional[bytes]:
        if writeable:
            with open(
                self.__output_path, "wb"
            ) as file, open(
                self.__output_path + ":hash", "wb"
            ) as ads:
                file.write(writeable.encode("utf-8"))
                ads.write(self.__hash)
        return open(
            self.__output_path + ":hash", "rb"
        ).read()

    def __linux_io(
        self, writeable: str = ""
    ) -> Optional[bytes]:
        if sys.platform in ["linux", "linux2", "darwin"]:
            import xattr  # type: ignore

            if writeable:
                with open(self.__output_path, "wb") as file:
                    file.write(writeable.encode("utf-8"))

                attr = xattr.xattr(self.__output_path)
                attr.set("user.hash", self.__hash)

            attr = xattr.xattr(self.__output_path)
            return attr.get("user.hash")
        return None

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
            raise PermissionError(
                "You do not have permission to write to the file."
            )

        except FileNotFoundError:
            raise FileNotFoundError(
                "The file does not exist."
            )

    def is_code_altered(self) -> bool:
        if not base.USE_CACHE:
            return True

        if not os.path.exists(self.__output_path) or (
            os.path.exists(self.__output_path + ":hash")
            if sys.platform in ["linux", "linux2", "darwin"]
            else False
        ):
            return (
                True  # Hash file doesn't exist or is empty
            )

        existing_hash = self.get_hash()
        if self.__hash != existing_hash:
            return True

        return False

    def get_hash(self) -> bytes | None:
        try:
            return self.__io()
        except FileNotFoundError:
            open(self.__output_path + ":hash", "wb").write(
                self.__hash
            )
        return None