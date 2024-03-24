use serde::{de::Error, Deserialize, Serialize};
use serde_repr::*;
use std::fs;
use std::path::Path;
use std::{collections::HashMap, path::PathBuf};
use toml;

// TODO: Make this into a proc macro and move the trait to another file.
trait Merge {
    fn merge(&mut self, other: Self);
}


// TODO: Add a phantom generic to the HelixConfig struct that stipulates what mode is being used, e.g. Debug, Release, etc.

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct HelixConfig {
    core: Core,
    transpiler: Transpiler,
    compiler: Compiler,
    linker: Linker,
    formatter: Formatter,
    environment: Environment,
}

impl Merge for HelixConfig {
    fn merge(&mut self, other: Self) {
        self.core.merge(other.core);
        self.transpiler.merge(other.transpiler);
        self.compiler.merge(other.compiler);
        self.linker.merge(other.linker);
        self.formatter.merge(other.formatter);
        self.environment.merge(other.environment);
    }
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Core {
    core_location: String,
    auto_update: bool,
}

impl Default for Core {
    fn default() -> Self {
        Self {
            core_location: ".helix".to_string(),
            auto_update: true,
        }
    }
}

impl Merge for Core {
    fn merge(&mut self, other: Self) {
        self.core_location = other.core_location;
        self.auto_update = other.auto_update;
    }
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Transpiler {
    target: Target,
    warnings: bool,
    verbose: bool,
    threads: u8,
    optimization: OptimizationLevel,
    regex_module: String,
}


impl Default for Transpiler {
    fn default() -> Self {
        Self {
            target: Target::Python,
            warnings: true,
            verbose: false,
            threads: 8,
            optimization: OptimizationLevel::Three,
            regex_module: "re".to_string(),
        }
    }
}

impl Merge for Transpiler {
    fn merge(&mut self, other: Self) {
        self.target = other.target;
        self.warnings = other.warnings;
        self.verbose = other.verbose;
        self.threads = other.threads;
        self.optimization = other.optimization;
        self.regex_module = other.regex_module;
    }
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub enum Target {
    #[serde(rename = "python", alias = "py")]
    Python,
}


// This is input validation
#[derive(Debug, Deserialize_repr, Serialize_repr, PartialEq)]
#[repr(u8)]
#[serde(rename_all = "snake_case")]
enum OptimizationLevel {
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Compiler {
    py: String,
    c: String,
    cpp: String,
    rust: String,
    // Should these be in a vector?
    flags_py: String,
    flags_cpp: String,
    flags_c: String,
    flags_rust: String,
}

impl Merge for Compiler {
    fn merge(&mut self, other: Self) {
        self.py = other.py;
        self.c = other.c;
        self.cpp = other.cpp;
        self.rust = other.rust;
        // Should we extend or replace the flags?
        self.flags_py = other.flags_py;
        self.flags_cpp = other.flags_cpp;
        self.flags_c = other.flags_c;
        self.flags_rust = other.flags_rust;
    }
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Linker {
    c_cpp_include_dirs: Vec<PathBuf>,
    rs_include_dirs: Vec<PathBuf>,
    py_include_dirs: Vec<PathBuf>,
    lib_dirs: Vec<PathBuf>,
    link_static: bool,
}

impl Merge for Linker {
    fn merge(&mut self, other: Self) {
        self.c_cpp_include_dirs.extend(other.c_cpp_include_dirs);
        self.rs_include_dirs.extend(other.rs_include_dirs);
        self.py_include_dirs.extend(other.py_include_dirs);
        self.lib_dirs.extend(other.lib_dirs);

        // dedup
        self.c_cpp_include_dirs.dedup();
        self.rs_include_dirs.dedup();
        self.py_include_dirs.dedup();
        self.lib_dirs.dedup();

        self.link_static = other.link_static;
    }
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Formatter {
    indent_size: u16,
    formatter: FormatterType,
    always_format: bool,
}

impl Merge for Formatter {
    fn merge(&mut self, other: Self) {
        self.indent_size = other.indent_size;
        self.formatter = other.formatter;
        self.always_format = other.always_format;
    }
}

// TODO: Add more formatters here,
#[derive(Debug, Deserialize, Serialize, PartialEq)]
#[serde(rename_all = "snake_case")]
enum FormatterType {
    Black,
}

#[derive(Debug, Deserialize, Serialize, PartialEq)]
struct Environment {
    env_vars: HashMap<String, String>,
}

impl Merge for Environment {
    fn merge(&mut self, other: Self) {
        self.env_vars.extend(other.env_vars)
    }
}

impl HelixConfig {
    const DEFAULT_FILE_NAME: &'static str = "helix.toml";

    pub fn load_from_file(path: &Path) -> Result<Self, ConfigError> {
        let contents = fs::read_to_string(path).map_err(ConfigError::FailedToLoadFile)?;

        toml::from_str(&contents).map_err(ConfigError::ParseError)
    }

    pub fn save_to_file(&self, path: &Path) -> Result<(), ConfigError> {
        let toml_string = toml::to_string_pretty(self).map_err(ConfigError::SerializationError)?;

        fs::write(path, toml_string).map_err(ConfigError::FailedToSave)
    }

    pub fn load() -> Result<Self, ConfigError> {
        let mut default_config = HelixConfig::default();

        let project_config_path = std::env::current_dir()
            .map_err(ConfigError::FailedToLoadFile)?
            .join(HelixConfig::DEFAULT_FILE_NAME);

        let project_config = HelixConfig::load_from_file(&project_config_path)?;

        default_config.merge(project_config);

        // Load the global config and merge it with the project config
        if let Ok(s) = std::env::var("HELIX_CONFIG") {
            let path = Path::new(&s);

            let global_config = HelixConfig::load_from_file(&path)?;

            default_config.merge(global_config);
        };

        return Ok(default_config);
    }
}

impl Default for HelixConfig {
    fn default() -> Self {
        Self {
            core: Core {
                core_location: ".helix".to_string(),
                auto_update: true,
            },
            transpiler: Transpiler {
                target: Target::Python,
                warnings: true,
                verbose: false,
                // This makes more sense for a default value
                threads: 8,
                optimization: OptimizationLevel::Three,
                regex_module: "re".to_string(),
            },
            compiler: Compiler {
                py: std::env::var("PYTHON").unwrap_or_else(|_| "python".to_string()),
                c: "gcc".to_string(),
                cpp: "g++".to_string(),
                rust: "rustc".to_string(),
                flags_py: "-OO".to_string(),
                flags_cpp: "-std=c++17".to_string(),
                flags_c: "-std=c18".to_string(),
                flags_rust: "--edition=2021".to_string(),
            },
            linker: Linker {
                c_cpp_include_dirs: Vec::new(),
                rs_include_dirs: Vec::new(),
                py_include_dirs: Vec::new(),
                lib_dirs: Vec::new(),
                link_static: false,
            },
            formatter: Formatter {
                indent_size: 4,
                formatter: FormatterType::Black,
                always_format: false,
            },
            environment: Environment {
                env_vars: HashMap::new(),
            },
        }
    }
}

#[derive(Debug)]
pub enum ConfigError {
    FailedToLoadFile(std::io::Error),
    ParseError(toml::de::Error),
    SerializationError(toml::ser::Error),
    FailedToSave(std::io::Error),
}

impl std::error::Error for ConfigError {}

impl std::fmt::Display for ConfigError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        use ConfigError::*;
        match self {
            FailedToLoadFile(p) => {
                write!(f, "Config was either not found or could not be read: {p}")
            }
            ParseError(e) => write!(f, "Failed to parse config file:\n{e}"),
            FailedToSave(e) => write!(f, "Failed to save config file:\n{e}"),
            SerializationError(e) => write!(f, "Failed to serialize config:\n{e}"),
        }
    }
}
// TODO: Add ignore when this file is done.
#[cfg(test)]
mod test {

    use super::*;
    #[test]
    fn test_parse() {
        // TODO: Use an include macro here
        const CONFIG: &'static str = r#"
    [core]
        core_location = ".helix"
        auto_update = true


    # --- Transpiler Configurations ---
    # Detailed settings for the code transpiler.
    # target: Specifies the target language for transpilation. Options: 'py', 'c++', etc.
    # warnings: Toggles the display of warnings during transpilation.
    # verbose: Enables verbose output for detailed logs.
    # threads: Defines the number of threads to use for transpilation.
    # optimization: Sets the level of optimization. Ranges from 0 (none) to 3 (maximum).
    # regex_module: Chooses the regex module to be used. Options: 're', 're2'.
    [transpiler]
        target = "py"
        warnings = true
        verbose = false
        threads = 44
        optimization = 2
        regex_module = "re"

        
        
        
    
    
    # --- Compiler Configurations ---
    # Configurations for various compilers used in the project.
    # py: Python layer options: 'py' (default), 'bin', 'vile'.
    #     'py' is typical for development and testing.
    #     'bin' compiles to a binary executable for production.
    #     'vile' generates an ABI for use with other languages and as a Helix library.
    # c, cpp, rust: Specify the compilers for C, C++, and Rust respectively.
    #     Defaults: 'gcc' for C, 'g++' for C++, 'rustc' for Rust.
    # flags_py, flags_cpp, flags_c, flags_rust: Custom flags for compiling Python, C++, C, and Rust.
    [compiler]
        py = "z:\\devolopment\\helix\\helix-lang\\.venv\\Scripts\\python.exe"
        c = "gcc"
        cpp = "cl"
        rust = "rustc"
        flags_py = "-OO"
        flags_cpp = "-std=c++17"
        flags_c = "-std=c18"
        flags_rust = "--edition=2021"
        
        
        
        
    
    
    # --- Linker Configurations ---
    # Settings for linking binaries and libraries.
    # c_cpp_include_dirs: Include directories for C/C++ source files.
    # rs_include_dirs: Include directories for Rust source files.
    # py_include_dirs: Include directories for Python source files.
    # lib_dirs: Directories where libraries are located.
    [linker]
        c_cpp_include_dirs = []
        rs_include_dirs = []
        py_include_dirs = []
        lib_dirs = []
        link_static = false
    
    [formatter]
        indent_size = 5
        formatter = "black"
        always_format = false
    
    [environment]
        env_vars = {}
        
    "#;

        let mut default_config = HelixConfig::default();

        let test_config: HelixConfig = match toml::from_str(CONFIG) {
            Ok(c) => c,
            Err(e) => {
                panic!("Failed to parse config: {}", e);
            }
        };

        default_config.merge(test_config);

        assert_ne!(default_config, HelixConfig::default());

        assert_eq!(default_config.core.core_location, ".helix");
        assert_eq!(default_config.transpiler.target, Target::Python);
    }
}
