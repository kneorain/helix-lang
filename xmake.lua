set_project("helix-lang")
add_rules  ("mode.debug", "mode.release")

----------------------------------------------------------------------------------------------------

target("helix-lang")
    set_kind("binary")
    set_warnings("all")
    
    add_files("source/*.cc")    -- add all files in the source directory
    add_files("source/**/*.cc") -- add all files in the source directory's subdirectories
    
    set_languages("c++2b")      -- set the standard c++ version to c++2b
    set_optimize ("fastest")
    
    add_includedirs("/opt/llvm-aarch64/include")
    add_linkdirs   ("/opt/llvm-aarch64/lib")
    
    add_links("LLVM-18", "clang", "clang-cpp", "c++", "c++abi") -- explicitly add LLVM libraries
    
    add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include"     )
    add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi" , "-Wl,-rpath,/opt/llvm-aarch64/lib")

----------------------------------------------------------------------------------------------------

target("test")
    set_kind("binary")
    set_warnings("all")
    
    add_files("test/*.cc")
    add_files("test/**/*.cc")
    
    set_languages("c++2b")
    set_optimize ("fastest")
    
    add_includedirs("/opt/llvm-aarch64/include")
    add_linkdirs   ("/opt/llvm-aarch64/lib")
    
    add_links("LLVM-18", "clang", "clang-cpp", "c++", "c++abi")
    
    add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include"     )
    add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi" , "-Wl,-rpath,/opt/llvm-aarch64/lib")

----------------------------------------------------------------------------------------------------

before_build(
    function(target)
        import("lib.detect.find_tool")
        
        local llvm_config = find_tool("llvm-config", {paths = "/opt/llvm-aarch64/bin"})
        
        if llvm_config then
            local llvm_includedir = os.iorunv(llvm_config.program, {"--includedir"}):trim()
            local llvm_libdir     = os.iorunv(llvm_config.program, {"--libdir"}    ):trim()
            
            target:add("includedirs", llvm_includedir)
            target:add("linkdirs"   , llvm_libdir    )
        
        else
            raise("llvm-config not found!")
        
        end
    end
)

----------------------------------------------------------------------------------------------------