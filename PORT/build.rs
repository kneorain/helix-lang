fn main() -> miette::Result<()> {
    // let _user = std::env::current_dir().unwrap();
    // let mut build = cc::Build::new();
    
    //let cpp_files: Vec<PathBuf> = fs::read_dir("src\\cpp").unwrap()
    //    .map(|entry| entry.unwrap().path())
    //    .filter(|path| path.extension().unwrap() == "cpp")
    //    .collect();


    cxx_build::bridge("src/cpp/mod.rs")
        .file("src/cpp/src/greeting.cpp")
        //.compiler("clang++")
        //.include("C:\\Programing Languages\\LLVM\\include")
        .std("c++20")
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
    
    //let path = std::path::PathBuf::from("src\\cpp"); // include path
    //let mut build = autocxx_build::Builder::new("src\\cpp\\mod.rs", &[&path]).build()?;
    //
    //build.compiler("c:\\Users\\dhruv\\Downloads\\llvm-mingw-20240320-msvcrt-x86_64\\bin\\clang++.exe");
    //build.files(cpp_files);
    //build.flag_if_supported("-w");
    //build.flag_if_supported("-v");

    //// This assumes all your C++ bindings are in main.rs
    //build.flag_if_supported("-std=c++21").compile("helix-cpp"); // arbitrary library name, pick anything
    //println!("cargo:rerun-if-changed=src/main.rs");
    //// Add instructions to link to any C++ libraries you need.
    Ok(())
}
