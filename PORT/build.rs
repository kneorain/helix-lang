// //.compiler("clang++")
// //.include("C:\\Programing Languages\\LLVM\\include")
// // dont show -Wignored-attributes
// //.flag("-Wno-ignored-attributes")
// //.cpp_set_stdlib("libc++")
//TODO: FIX
// use std::{fs::canonicalize, path::Display};

// fn main() -> miette::Result<()> {
//     let mut bridge = cxx_build::bridge("src/cpp/mod.rs");

//     const CPP_OUT_DIR: &str = "./target/cpp";
//     const CPP_SRC_DIR: &str = "./src/cpp";
//     // check if the target/cpp directory exists
//     if !std::path::Path::new(CPP_OUT_DIR).exists() {
//         std::fs::create_dir(CPP_OUT_DIR).expect("Could not create the target/cpp directory");
//     }

//     // Watch the the mod.rs file
//     println!("cargo:rerun-if-changed=./src/cpp/mod.rs");

//     // TODO: Make this cleaner...
//     let current_dir = std::env::current_dir()
//     .expect("Could not get the current directory")
//     .display()
//     .to_string();

//     // Include the files and set the to be watched by cargo
//     std::fs::read_dir(CPP_SRC_DIR)
//         .expect("Could not read the c++ directory")
//         // Map the paths to the pathbufs
//         .map(|entry|  entry.expect("Entry not found").path().display().to_string())
//         // Filter out invalid paths
//         .filter(|path| {
//             matches!(
//                 path.split('.').last(),
//                 Some("cpp")
//                     | Some("cc")
//                     | Some("cxx")
//                     | Some("C")
//                     | Some("CPP")
//                     | Some("c++")
//                     | Some("cp")
//             )
//         })
//         .for_each(|mut path| {
            

//             path = path.replace(&current_dir, "./").split(std::path::MAIN_SEPARATOR)
//             .collect::<Vec<&str>>().join(std::path::MAIN_SEPARATOR.to_string().as_str());

            
//             println!("cargo:rerun-if-changed={}", path);
//             bridge.file(path);
//         });
//     // For each path, print the path and set it to be watched by cargo
//     // and include it in the bridge

//     // Set up the compiler
//     bridge.std("c++17").flag("-MD").opt_level(3); //.out_dir(CPP_OUT_DIR);
//                                                   // Compile
//     bridge.compile("helix-compiler");

//     Ok(())
// }
fn main() -> miette::Result<()> {
    // let _user = std::env::current_dir().unwrap();
    // let mut build = cc::Build::new();
    
    //let cpp_files: Vec<PathBuf> = fs::read_dir("src\\cpp").unwrap()
    //    .map(|entry| entry.unwrap().path())
    //    .filter(|path| path.extension().unwrap() == "cpp")
    //    .collect();


    cxx_build::bridge("src/cpp/mod.rs")
        .file("src/cpp/src/greeting.cpp")
        .file("src/cpp/src/file_reader.cpp")
        //.compiler("clang++")
        //.include("C:\\Programing Languages\\LLVM\\include")
        .std("c++20")
        // dont show -Wignored-attributes
        //.flag("-Wno-ignored-attributes")
        .flag("-MD")
        .opt_level(3)
        //.cpp_set_stdlib("libc++")
        .include("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\include")
        .include("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\ATLMFC\\include")
        .include("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\VS\\include")
        .include("C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22621.0\\ucrt")
        .include("C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22621.0\\um")
        .include("C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22621.0\\shared")
        .include("C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22621.0\\winrt")
        .include("C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22621.0\\cppwinrt")
        .include("C:\\Program Files (x86)\\Windows Kits\\NETFXSDK\\4.8\\include\\um")
        
        .compile("helix-compiler");
    
    println!("cargo:rerun-if-changed=src/cpp/mod.rs");
    println!("cargo:rerun-if-changed=src/rust/mod.rs");
    println!("cargo:rerun-if-changed=src/cpp/greeting.cpp");
    println!("cargo:rerun-if-changed=src/cpp/include/greeting.h");
    Ok(())
}