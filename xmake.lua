set_project("helix-lang")

add_rules("mode.debug", "mode.release")

target("helix-lang")
    set_kind("binary")
    add_files("src/*.cc")
    -- set the standard c++ version to c++2b
    set_languages("c++2b")
    set_optimize("fastest")
    -- enable multi-thread compilation
    add_includedirs("/opt/llvm-aarch64/include")
    add_linkdirs("/opt/llvm-aarch64/lib")
    add_cxxflags("-stdlib=libc++", "-fno-rtti", "-I/opt/llvm-aarch64/include")
    add_ldflags("-L/opt/llvm-aarch64/lib", "-lc++abi", "-Wl,-rpath,/opt/llvm-aarch64/lib")
    -- explicitly add the LLVM libraries
    add_links("LLVM-18", "clang", "clang-cpp", "c++", "c++abi")

before_build(function (target)
    import("lib.detect.find_tool")
    local llvm_config = find_tool("llvm-config", {paths = "/opt/llvm-aarch64/bin"})
    if llvm_config then
        local llvm_includedir = os.iorunv(llvm_config.program, {"--includedir"}):trim()
        local llvm_libdir = os.iorunv(llvm_config.program, {"--libdir"}):trim()
        target:add("includedirs", llvm_includedir)
        target:add("linkdirs", llvm_libdir)
    else
        raise("llvm-config not found!")
    end
end)
        

-- llvm install instructions for macos (arm64)
-- brew install cmake ninja wget
-- cd ~
-- mkdir -p ~/built-includes/llvm-install
-- cd ~/built-includes/llvm-install
-- wget https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.6/llvm-project-18.1.6.src.tar.xz
-- tar -xvf llvm-project-18.1.6.src.tar.xz
-- cd llvm-project-18.1.6.src
-- mkdir build
-- cd build
-- cmake -G "Ninja" -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD="AArch64" -DCMAKE_INSTALL_PREFIX=/opt/llvm-aarch64 ../llvm
-- ninja
-- sudo ninja install
