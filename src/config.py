import os
import sys
import toml
import dataclasses
from typing import Any, Optional


# TODO: ADD PANIC's here

@dataclasses.dataclass
class HelixConfig:
    @dataclasses.dataclass
    class Core:
        core_location: str = ".helix"
        auto_update: bool = True

    @dataclasses.dataclass
    class Transpiler:
        target: str = "py"
        warnings: bool = True
        verbose: bool = False
        threads: int = 50
        optimization: int = 3
        regex_module: str = "re"

    @dataclasses.dataclass
    class Compiler:
        py: str = sys.executable
        c: str = "gcc"
        cpp: str = "g++"
        rust: str = "rustc"
        flags_py: str = "-OO"
        flags_cpp: str = "-std=c++17"
        flags_c: str = "-std=c18"
        flags_rust: str = "--edition=2021"

    @dataclasses.dataclass
    class Linker:
        c_cpp_include_dirs: list[str] = dataclasses.field(default_factory=list)
        rs_include_dirs: list[str] = dataclasses.field(default_factory=list)
        py_include_dirs: list[str] = dataclasses.field(default_factory=list)
        lib_dirs: list[str] = dataclasses.field(default_factory=list)
        link_static: bool = False

    @dataclasses.dataclass
    class Formatter:
        indent_size: int = 4
        formatter: str = "black"
        always_format: bool = False

    @dataclasses.dataclass
    class Environment:
        env_vars: dict[str, str] = dataclasses.field(default_factory=dict)

    core: Core = dataclasses.field(default_factory=Core)
    transpiler: Transpiler = dataclasses.field(default_factory=Transpiler)
    compiler: Compiler = dataclasses.field(default_factory=Compiler)
    linker: Linker = dataclasses.field(default_factory=Linker)
    formatter: Formatter = dataclasses.field(default_factory=Formatter)
    environment: Environment = dataclasses.field(default_factory=Environment)
        
class ConfigFactory:
    @staticmethod
    def create_default_config() -> HelixConfig:
        return HelixConfig()

    @staticmethod
    def create_project_config() -> HelixConfig:
        return HelixConfig(
            core=None,# type: ignore
            transpiler=HelixConfig.Transpiler(
                threads=None, # type: ignore
                optimization=None, # type: ignore
                regex_module=None # type: ignore
            ),
            compiler=HelixConfig.Compiler(
                flags_py=None, # type: ignore
                flags_cpp=None, # type: ignore
                flags_c=None, # type: ignore
                flags_rust=None, # type: ignore
            ),
            linker=HelixConfig.Linker(
                link_static=None, # type: ignore
            ),
            formatter=None, # type: ignore
            environment=None # type: ignore
        )

class CustomTomlEncoder:
    def __init__(self) -> None:
        self.comments: dict[str, str] = {}
        self.indent: str = "    "

    def add_comment(self, section: str, comment: str) -> None:
        self.comments[section] = comment

    def encode(self, config: dict[str, Optional[dict[str, Any]]]) -> str:
        output_lines: list[str] = []
        for section, values in config.items():
            # Skip sections with None values
            if values is None:
                continue

            # Add section comment
            comment: str = self.comments.get(section, "")
            if comment:
                output_lines.append(comment)

            # Add section content
            output_lines.append(f"[{section}]")
            for key, value in values.items():
                value_str: str = toml.dumps({key: value}).strip()
                output_lines.append(self.indent + value_str)
            output_lines.append("")  # Newline after each section

        return "\n".join(output_lines)

encoder: CustomTomlEncoder = CustomTomlEncoder()
encoder.add_comment('core', """
# --- Core Configurations ---
# core_location: Path to the core directory. It's where essential files are stored.
# auto_update: Enables automatic updates for the core components.
#     Note: Disabling this might cause compatibility issues with future versions.""")

encoder.add_comment('transpiler', """
# --- Transpiler Configurations ---
# Detailed settings for the code transpiler.
# target: Specifies the target language for transpilation. Options: 'py', 'c++', etc.
# warnings: Toggles the display of warnings during transpilation.
# verbose: Enables verbose output for detailed logs.
# threads: Defines the number of threads to use for transpilation.
# optimization: Sets the level of optimization. Ranges from 0 (none) to 3 (maximum).
# regex_module: Chooses the regex module to be used. Options: 're', 're2'.""")

encoder.add_comment('compiler', """
# --- Compiler Configurations ---
# Configurations for various compilers used in the project.
# py: Python layer options: 'py' (default), 'bin', 'vile'.
#     'py' is typical for development and testing.
#     'bin' compiles to a binary executable for production.
#     'vile' generates an ABI for use with other languages and as a Helix library.
# c, cpp, rust: Specify the compilers for C, C++, and Rust respectively.
#     Defaults: 'gcc' for C, 'g++' for C++, 'rustc' for Rust.
# flags_py, flags_cpp, flags_c, flags_rust: Custom flags for compiling Python, C++, C, and Rust.""")

encoder.add_comment('linker', """
# --- Linker Configurations ---
# Settings for linking binaries and libraries.
# c_cpp_include_dirs: Include directories for C/C++ source files.
# rs_include_dirs: Include directories for Rust source files.
# py_include_dirs: Include directories for Python source files.
# lib_dirs: Directories where libraries are located.""")

encoder.add_comment('formatter', """
# --- Formatter Configurations ---
# Configurations for code formatting.
# indent_size: The size of indentation in number of spaces.
# formatter: The tool used for formatting (e.g., 'black' for Python).
# always_format: When set to true, always formats the generated code.
#     Note: Enabling this might break certain code structures, recommended for debugging only.""")

#encoder.add_comment('environment', """# --- Environment Configurations ---
## Custom environment variables to be set during execution.
## 'env_vars' is a dictionary of environment variables to be set.
## Example of 'env_vars':
##     env_vars = {
##         "SOME_NUM": "1",
##         "WOAH_PATH": "/point/to/somewhere"
##     }
## You can access these variables in your code using `helix::env['var']`.""")
# TODO : make env vars work

class ConfigLoader:
    @staticmethod
    def load_config_file(path: str) -> dict[str, Any]:
        with open(path, 'r') as file:
            return toml.load(file)

    @staticmethod
    def save_config(path: str, config: dict[str, Any]):
        with open(path, 'w') as file:
            file.write(encoder.encode(config))

    @staticmethod
    def merge_dicts(base: dict[str, Any], override: dict[str, Any]) -> dict[str, Any]:
        for key, value in override.items():
            if isinstance(value, dict) and key in base:
                base[key] = ConfigLoader.merge_dicts(base[key], value)
            else:
                base[key] = value
        return base

    @staticmethod
    def load_config(init_proj: bool = False) -> HelixConfig:
        project_config_path = os.path.join(os.getcwd(), 'helix.toml')
        default_config_path = os.path.expanduser(HelixConfig.Core().core_location) + '/helix.toml'
        env_config_path = os.getenv('HELIX_CONFIG')

        project_config = {}
        if os.path.exists(project_config_path):
            project_config = ConfigLoader.load_config_file(project_config_path)

        env_config = {}
        if env_config_path and os.path.exists(env_config_path):
            env_config = ConfigLoader.load_config_file(env_config_path)

        default_config = {}
        if os.path.exists(default_config_path):
            default_config = ConfigLoader.load_config_file(default_config_path)
        else:
            default_config = dataclasses.asdict(ConfigFactory.create_default_config())
            os.makedirs(os.path.dirname(default_config_path), exist_ok=True)
            ConfigLoader.save_config(default_config_path, default_config)

        if init_proj and not os.path.exists(project_config_path):
            minimal_project_config = dataclasses.asdict(ConfigFactory.create_project_config())
            ConfigLoader.save_config(project_config_path, minimal_project_config)

        # Merge configurations: project -> env -> default
        merged_config = ConfigLoader.merge_dicts(default_config, env_config)
        merged_config = ConfigLoader.merge_dicts(merged_config, project_config)
        
        # Convert the merged dictionary back into a HelixConfig instance
        return ConfigLoader.dict_to_helix_config(merged_config)

    @staticmethod
    def create_project_config() -> None:
        ConfigLoader.load_config(True)
    
    @staticmethod
    def dict_to_helix_config(data: dict[str, Any]) -> HelixConfig:
        # For simplicity, we will create default instances and then override with data
        helix_config = HelixConfig()

        for section_name, section_data in data.items():
            if hasattr(helix_config, section_name):
                section_instance = getattr(helix_config, section_name)
                for key, value in section_data.items():
                    if hasattr(section_instance, key):
                        setattr(section_instance, key, value)

        return helix_config
    
CONFIG = ConfigLoader.load_config()