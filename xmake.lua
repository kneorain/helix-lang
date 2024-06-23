set_project("helix-lang")
add_rules("mode.debug", "mode.release")

target("helix")
    set_kind("binary")
    set_warnings("all")
    
    add_files("source/*.cc")    -- add all files in the source directory
    add_files("source/**/*.cc") -- add all files in the source directory's subdirectories
    
    set_languages("c++latest")      -- set the standard C++ version to C++23
    
    if is_mode("debug") then
        set_symbols("debug")       -- Generate debug symbols
        set_optimize("none")       -- Disable optimization
        add_defines("DEBUG")       -- Define DEBUG macro
        set_runtimes("MDd")        -- Use the debug version of the runtime library
    else
        set_symbols("hidden")      -- Hide symbols
        set_optimize("fastest")    -- Enable maximum optimization
        add_defines("NDEBUG")      -- Define NDEBUG macro
        set_runtimes("MD")         -- Use the release version of the runtime library
    end

    if is_plat("macosx") then
        lib_cpp = "c++"
        lip_abi = "c++abi"
    end

if is_mode("debug") then
    set_runtimes("MDd")
else
    set_runtimes("MD")
end
