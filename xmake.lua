-------------------------------------------- xmake.lua ---------------------------------------------

set_project("helix-lang")
add_rules("mode.debug", "mode.release")

------------------------------------------- dependencies -------------------------------------------

add_requires("catch2 3", { system = false, configs = {components = {"main"}, }})

-- for clanged support run "xmake project -k compile_commands" to generate compile_commands.json

-------------------------------------------- helix --------------------------------------------

target("helix")
    set_kind("binary")
    set_warnings("all")
    
    add_files("source/*.cc")    -- add all files in the source directory
    add_files("source/**/*.cc") -- add all files in the source directory's subdirectories
    
    set_languages("c++2b")      -- set the standard C++ version to C++2b
    
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
    
    add_includedirs("/opt/llvm-aarch64/include")
    add_linkdirs   ("/opt/llvm-aarch64/lib")
    
    add_links("clang", "clang-cpp", "c++", "c++abi") -- explicitly add LLVM libraries
    -- "LLVM-18" removed
    
    add_cxxflags("-stdlib=libc++", "-fno-rtti", "-I/opt/llvm-aarch64/include")
    add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi", "-Wl,-rpath,/opt/llvm-aarch64/lib")

----------------------------------------------- test -----------------------------------------------

target("tests")
    set_kind("binary")
    set_warnings("all")
    
    add_files("tests/*.cc") -- add all files in the tests directory
    
    if os.isdir("tests/*") then
        add_files("tests/**/*.cc") -- add all files in the tests directory's subdirectories
    end
    
    set_languages("c++2b") -- set the standard C++ version to C++2b
    set_optimize ("fastest")
    
    add_includedirs("/opt/llvm-aarch64/include")
        
    add_linkdirs   ("/opt/llvm-aarch64/lib")
    
    add_links("clang", "clang-cpp", "c++", "c++abi", "Catch2", "Catch2Main") -- add LLVM libs
    -- "LLVM-18" removed
    
    add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include")
    add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi" , "-Wl,-rpath,/opt/llvm-aarch64/lib")

    add_packages("catch2")

----------------------------------------------- llvm -----------------------------------------------

before_build(function(target)
    import("lib.detect.find_tool")
    
    local llvm_config = find_tool("llvm-config", {paths = "/opt/llvm-aarch64/bin"})
    
    if llvm_config then
        local llvm_includedir = os.iorunv(llvm_config.program, {"--includedir"}):trim()
        local llvm_libdir     = os.iorunv(llvm_config.program, {"--libdir"}):trim()
        
        target:add("includedirs", llvm_includedir)
        target:add("linkdirs", llvm_libdir)
    else
        raise("llvm-config not found!")
    end
end)

-------------------------------------------- build modes -------------------------------------------

if is_mode("debug") then
    set_runtimes("MDd")
else
    set_runtimes("MD")
end

----------------------------------------------------------------------------------------------------

-- -------------------------------------------- xmake.lua ---------------------------------------------
--
-- set_project("helix-lang")
-- add_rules("mode.debug", "mode.release")
--
-- ------------------------------------------- dependencies -------------------------------------------
--
-- add_requires("catch2 3", { system = false, configs = {components = {"main"}, }})
--
-- -- for clanged support run "xmake project -k compile_commands" to generate compile_commands.json
--
-- -------------------------------------------- fucntions ---------------------------------------------
--
-- ----------------------------------------- target_setup.lua -----------------------------------------
--
-- local target_setup = function(target)
--     if os.isdir(target) then
--         set_kind("binary")
--         set_warnings("all")
--
--         add_files(target .. "/*.cc") -- add all files in the tests directory
--
--         if os.isdir(target .. "/*") then
--             add_files(target .. "/**/*.cc") -- add all files in the tests directory's subdirectories
--         end
--
--         set_languages("c++2b") -- set the standard C++ version to C++2b
--         set_optimize ("fastest")
--     end
-- end
--
-- ------------------------------------------ links_setup.lua -----------------------------------------
--
-- local links_setup = function(...)
--     add_linkdirs   ("/opt/llvm-aarch64/lib")
--     add_links(...)
-- end
--
-- ---------------------------------------- includes_setup.lua ----------------------------------------
--
-- local includes_setup = function(...)
--     add_includedirs(...)
-- end
--
-- ------------------------------------------ base_setup.lua ------------------------------------------
--
-- local base_setup = function(target, ...)
--     target_setup(target)
--     links_setup("LLVM-18", "clang", "clang-cpp", "c++", "c++abi", ...)
--     includes_setup("/opt/llvm-aarch64/include")
-- end
--
-- -------------------------------------------- helix-lang --------------------------------------------
--
-- target("helix-lang")
--     base_setup("source")
--     add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include")
--     add_ldflags ("-L/opt/llvm-aarch64/lib" , "-Wl,-rpath,/opt/llvm-aarch64/lib")
--
-- ----------------------------------------------- test -----------------------------------------------
--
-- target("test")
--     base_setup("tests", "Catch2", "Catch2Main")
--     add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include")
--     add_ldflags ("-L/opt/llvm-aarch64/lib" , "-Wl,-rpath,/opt/llvm-aarch64/lib")
--     add_packages("catch2")
--
-- ------------------------------------------- before_build -------------------------------------------
--
-- before_build(function(target)
--     import("lib.detect.find_tool")
--
--     local llvm_config = find_tool("llvm-config", {paths = "/opt/llvm-aarch64/bin"})
--
--     if llvm_config then
--         local llvm_includedir = os.iorunv(llvm_config.program, {"--includedir"}):trim()
--         local llvm_libdir     = os.iorunv(llvm_config.program, {"--libdir"}):trim()
--
--         target:add("includedirs", llvm_includedir)
--         target:add("linkdirs", llvm_libdir)
--     else
--         raise("llvm-config not found!")
--     end
-- end)
--
-- -------------------------------------------- build modes -------------------------------------------
--
-- if is_mode("debug") then
--     set_runtimes("MDd")
-- else
--     set_runtimes("MD")
-- end
--
-- ----------------------------------------------- run ------------------------------------------------
--
-- on_load(function (target)
--     import("core.base.task")
--     task.run("require")
-- end)
--
-- ----------------------------------------------------------------------------------------------------