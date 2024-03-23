from __future__ import annotations
from typing import Optional
from src.core.imports import (
    os,
    Hashing,
    color_print as print,
    framework,
    ctypes,
    shutil
)

# --- c imports --- #
c_remove_blank_lines = ctypes.CDLL(os.path.join("src", "lib", "remove_blank_lines.dll")).remove_blank_lines
c_remove_blank_lines.argtypes = [ctypes.c_char_p]
c_remove_blank_lines.restype  =  ctypes.c_int

class HelixLanguage(framework.HelixLanguage):
    """
    Represents the core functionality for managing and executing Helix language operations.

    This class encapsulates methods for various tasks like folder and file management,
    setting up the Helix environment, and handling installations and configurations.

    Methods
    -------
    __init__(self, *args: str, **kwargs: str)
        Initialize the HelixLanguage instance with given arguments.
    make_folder(directory: str) -> None
        Creates a folder at the specified directory path.
    make_file(file: str) -> None
        Creates a file at the specified file path.
    generate_folder_structure(directory: str = ...)
        Generates the necessary folder structure for a given directory.
    install_helix(config: dict) -> None
        Installs and configures the Helix environment based on the provided configuration.

    Examples
    --------
    >>> hl = HelixLanguage()
    >>> hl.make_folder('path/to/directory')
    >>> hl.install_helix({'option': 'value'})

    Notes
    -----
    The class is designed to be flexible and handle various aspects of the Helix language
    setup and management. More detailed methods and attributes can be added as per the
    development needs of the Helix language.
    """
    def __init__(self, *args: str, **kwargs: str):
        raise NotImplementedError(
            "Cannot instantiate HelixLanguage."
        )

    @staticmethod
    def make_folder(directory: str) -> None:
        if not os.path.isdir(directory):
            os.mkdir(directory)

    @staticmethod
    def make_file(file: str) -> None:
        if not os.path.exists(file):
            with open(file, "w", encoding="utf-8") as _:
                return

    @staticmethod
    def generate_folder_structure(
        directory: str = os.path.expanduser("~")
        + os.sep
        + ".helix",
    ):
        if (
            os.path.isdir(directory)
            and os.listdir(directory) != []
        ):
            return

        HelixLanguage.make_folder(directory)
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs", "helix")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs", "c++")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs", "c")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs", "python")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "intl_libs", "rust")
        )

        HelixLanguage.make_folder(
            os.path.join(directory, "logs")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "temp")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "cache")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "cache", "build_cache")
        )
        HelixLanguage.make_folder(
            os.path.join(directory, "include")
        )

        HelixLanguage.make_file(
            os.path.join(directory, "config.toml")
        )
        HelixLanguage.make_file(
            os.path.join(directory, "include", "core.py")
        )
        
    @staticmethod
    def install_helix(config: dict) -> None:
        if (
            config["core_location"]
            != os.path.expanduser("~") + os.sep + ".helix"
        ):
            HelixLanguage.generate_folder_structure(
                config["core_location"]
            )
        else:
            HelixLanguage.generate_folder_structure()

        if config["add_to_path"]:
            # permanently add to path
            print("Not yet implemented.")

        if config["add_to_desktop"]:
            # add to desktop
            print("Not yet implemented.")

    @staticmethod
    def remove_blank_lines(
        file: str, hash: Hashing | None
    ) -> None:
        with open(file, "r") as read_file, open(
            file + ".tmp", "w"
        ) as write_file:
            for line in read_file:
                if line.strip():
                    write_file.write(line)

        shutil.move(file + ".tmp", file)
        if hash:
            hash.create_hash_only()
