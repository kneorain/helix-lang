//.compiler("clang++")
//.include("C:\\Programing Languages\\LLVM\\include")
// dont show -Wignored-attributes
//.flag("-Wno-ignored-attributes")
//.cpp_set_stdlib("libc++")

fn main() -> miette::Result<()> {
    let mut bridge = cxx_build::bridge("src/cpp/mod.rs");

    // Set up the compiler
    bridge.std("c++17").flag("-MD").opt_level(3);

    // Watch the the mod.rs file
    println!("cargo:rerun-if-changed=./src/cpp/mod.rs");

    // TODO: Make this cleaner...

    // Include the files and set the to be watched by cargo
    std::fs::read_dir("./src/cpp")
        .expect("Could not read the c++ directory")
        // Map the paths to the pathbufs
        .map(|entry| entry.unwrap().path())
        // Filter out invalid paths
        .filter(|path| match path.extension() {
            Some(os_str) if matches!(os_str.to_str().unwrap(), "cpp" | "cc" | "cxx" | "C" | "CPP" | "c++" | "cp") => true,
            _ => false,
        })
        // For each path, print the path and set it to be watched by cargo
        // and include it in the bridge
        .for_each(|path| {
            println!("cargo:rerun-if-changed={}", path.as_path().display());
            bridge.file(path);
        });

    // Compile

    bridge.compile("helix-compiler");

    Ok(())
}
