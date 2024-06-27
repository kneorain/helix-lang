set_project("helix-lang")
add_rules("mode.debug", "mode.release")

target("helix")
    set_kind("binary")
    set_warnings("all")
    
    add_files("source/**.cc")    -- add all files in the source directory
    
    add_headerfiles("source/**.hh")    -- add all headers in the source directory
    add_includedirs("source")
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

target("tests")
    set_kind("binary")
    set_warnings("all")

    add_files("tests/**.cc")    -- add all files in the tests directory
    add_files("source/**.cc")   -- add all .cc files in the source directory and its subdirectories
    remove_files("source/main.cc")  -- exclude main.cc from the source directory

    add_headerfiles("source/**.hh")    -- add all headers in the source directory
    add_headerfiles("tests/**.hh")    -- add all headers in the tests directory
    
    add_includedirs("source")
    add_includedirs("tests/lib")
    set_languages("c++latest")      -- set the standard C++ version to C++23

    set_symbols("debug")       -- Generate debug symbols
    set_optimize("none")       -- Disable optimization
    add_defines("DEBUG")       -- Define DEBUG macro
    set_runtimes("MDd")        -- Use the debug version of the runtime library

if is_mode("debug") then
    set_runtimes("MDd")
else
    set_runtimes("MD")
end
