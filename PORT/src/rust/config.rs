use std::collections::HashMap;
use std::fs;
use serde::{de::Error, Deserialize, Serialize};
use toml;

#[derive(Debug, Deserialize, Serialize)]
pub struct HelixConfig {
    core: Core,
    transpiler: Transpiler,
    compiler: Compiler,
    linker: Linker,
    formatter: Formatter,
    environment: Environment,
}

#[derive(Debug, Deserialize, Serialize)]
struct Core {
    core_location: String,
    auto_update: bool,
}

#[derive(Debug, Deserialize, Serialize)]
struct Transpiler {
    target: String,
    warnings: bool,
    verbose: bool,
    threads: i32,
    optimization: i32,
    regex_module: String,
}

#[derive(Debug, Deserialize, Serialize)]
struct Compiler {
    py: String,
    c: String,
    cpp: String,
    rust: String,
    flags_py: String,
    flags_cpp: String,
    flags_c: String,
    flags_rust: String,
}

#[derive(Debug, Deserialize, Serialize)]
struct Linker {
    c_cpp_include_dirs: Vec<String>,
    rs_include_dirs: Vec<String>,
    py_include_dirs: Vec<String>,
    lib_dirs: Vec<String>,
    link_static: bool,
}

#[derive(Debug, Deserialize, Serialize)]
struct Formatter {
    indent_size: i32,
    formatter: String,
    always_format: bool,
}

#[derive(Debug, Deserialize, Serialize)]
struct Environment {
    env_vars: HashMap<String, String>,
}

impl HelixConfig {
    fn default() -> Self {
        Self {
            core: Core {
                core_location: ".helix".to_string(),
                auto_update: true,
            },
            transpiler: Transpiler {
                target: "py".to_string(),
                warnings: true,
                verbose: false,
                threads: 50,
                optimization: 3,
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
                formatter: "black".to_string(),
                always_format: false,
            },
            environment: Environment {
                env_vars: HashMap::new(),
            },
        }
    }

    fn merge(mut self, override_config: Self) -> Self {
        self.core = override_config.core;
        self.transpiler = override_config.transpiler;
        self.compiler = override_config.compiler;
        self.linker = override_config.linker;
        self.formatter = override_config.formatter;
        self.environment = override_config.environment;
        self
    }

    fn load_from_file(path: &str) -> Result<Self, toml::de::Error> {
        let contents = fs::read_to_string(path).map_err(|err| toml::de::Error::custom(err.to_string()))?;
        Ok(toml::from_str(&contents)?)
    }

    fn save_to_file(&self, path: &str) -> Result<(), toml::ser::Error> {
        let toml_string = toml::to_string_pretty(self)?;
        match fs::write(path, toml_string) {
            Ok(_) => Ok(()),
            Err(err) => panic!("Failed to write to file: {}", err),
        }
    }
}

pub fn get_config() -> HelixConfig {
    let default_config = HelixConfig::default();

    let project_config_path = std::env::current_dir().unwrap().join("helix.toml");
    let project_config = match HelixConfig::load_from_file(project_config_path.to_str().unwrap()) {
        Ok(config) => config,
        Err(_) => {
            let minimal_project_config = HelixConfig::default();
            minimal_project_config.save_to_file(project_config_path.to_str().unwrap()).unwrap();
            minimal_project_config
        }
    };

    impl Default for HelixConfig {
        fn default() -> Self {
            Self::default()
        }
    }

    let env_config_path = std::env::var("HELIX_CONFIG").ok();
    let env_config = match env_config_path {
        Some(path) => HelixConfig::load_from_file(&path).unwrap_or_default(),
        None => HelixConfig::default(),
    };

    let merged_config = default_config.merge(env_config).merge(project_config);
    return merged_config;
}