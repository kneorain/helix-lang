fn main() -> miette::Result<()> {
    // let _user = std::env::current_dir().unwrap();
    // let mut build = cc::Build::new();
    
    //let cpp_files: Vec<PathBuf> = fs::read_dir("src\\cpp").unwrap()
    //    .map(|entry| entry.unwrap().path())
    //    .filter(|path| path.extension().unwrap() == "cpp")
    //    .collect();


    cxx_build::bridge("src/cpp/mod.rs")
        .file("src/cpp/src/greeting.cpp")
        .file("src/cpp/src/file_stream.cpp")
        //.compiler("clang++")
        //.include("C:\\Programing Languages\\LLVM\\include")
        .std("c++17")
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
