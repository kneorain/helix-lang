set_project("helix-lang")

--set_toolchains("clang")
add_rules("mode.debug", "mode.release")

-------------------------------------------- helix --------------------------------------------

local llvm_include_dir = os.getenv("LLVM_INCLUDE") or ""
local llvm_lib_dir     = os.getenv("LLVM_LIB") or ""
local llvm_bin_dir     = os.getenv("LLVM_BIN") or ""
local llvm_dir         = os.getenv("LLVM_PATH") or ""

-- Detect OS and set LLVM paths if not defined
if llvm_include_dir == "" or llvm_lib_dir == "" or llvm_bin_dir == "" then
    if is_plat("windows") then
        llvm_include_dir = "c:\\PROGRA~1/LLVM/include"
        llvm_lib_dir     = "c:\\PROGRA~1/LLVM/lib"
        llvm_bin_dir     = "c:\\PROGRA~1/LLVM/bin"
        llvm_dir         = "c:\\PROGRA~1/LLVM"
    elseif is_plat("macosx") then
        llvm_include_dir = "/opt/llvm-aarch64/include"
        llvm_lib_dir     = "/opt/llvm-aarch64/lib"
        llvm_bin_dir     = "/opt/llvm-aarch64/bin"
        llvm_dir         = "/opt/llvm-aarch64"
    else
        -- Add other platforms as needed
        llvm_include_dir = "/opt/llvm/include"
        llvm_lib_dir     = "/opt/llvm/lib"
        llvm_bin_dir     = "/opt/llvm/bin"
        llvm_dir         = "/opt/llvm"
    end
end

set_config("sdk", llvm_dir)

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
    
    add_includedirs(llvm_include_dir)
    add_linkdirs(llvm_lib_dir)

    local lib_cpp = "libc++"
    local lip_abi = "libc++abi"

    if is_plat("macosx") then
        lib_cpp = "c++"
        lip_abi = "c++abi"
    end
    
    add_links("clang", "clang-cpp", lib_cpp, lip_abi) -- explicitly add LLVM libraries
    
    if is_plat("windows") then
        add_cxxflags("-stdlib=libc++", "-I" .. llvm_include_dir, "-Xclang", "-nostdinc++", {force = true})
        add_ldflags("-stdlib=libc++", "-L" .. llvm_lib_dir, "-lc++", "-lc++abi", {force = true})
        add_defines("_CRT_SECURE_NO_WARNINGS")
    else
        add_cxxflags("-stdlib=libc++", "-fno-rtti", "-I" .. llvm_include_dir, {force = true})
        add_ldflags("-stdlib=libc++", "-L" .. llvm_lib_dir, "-lc++abi", "-Wl,-rpath," .. llvm_lib_dir, {force = true})
    end

----------------------------------------------- llvm -----------------------------------------------

before_build(function(target)
    import("lib.detect.find_tool")
    
    local llvm_config = find_tool("llvm-config", {paths = llvm_bin_dir})
    
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

----------------------------------------------- test -----------------------------------------------

-- target("tests")
--     set_kind("binary")
--     set_warnings("all")
--     set_toolchains("clang")
    
--     add_files("tests/*.cc") -- add all files in the tests directory
    
--     if os.isdir("tests/*") then
--         add_files("tests/**/*.cc") -- add all files in the tests directory's subdirectories
--     end
    
--     set_languages("c++2b") -- set the standard C++ version to C++2b
--     set_optimize ("fastest")
    
--     add_includedirs(llvm_include_dir)
--     add_linkdirs(llvm_lib_dir)
    
--     add_links("clang", "clang-cpp", "c++", "c++abi", "Catch2", "Catch2Main") -- add LLVM libs
    
--     if is_plat("windows") then
--         add_cxxflags("-stdlib=libc++", "-I" .. llvm_include_dir, {force = true})
--         add_ldflags("-stdlib=libc++", "-L" .. llvm_lib_dir, {force = true})
--     else
--         add_cxxflags("-stdlib=libc++", "-fno-rtti", "-I" .. llvm_include_dir, {force = true})
--         add_ldflags("-stdlib=libc++", "-L" .. llvm_lib_dir, "-lc++abi", "-Wl,-rpath," .. llvm_lib_dir, {force = true})
--     end

--     add_packages("catch2")

-- -------------------------------------------- xmake.lua ---------------------------------------------

-- set_project("helix-lang")
-- add_rules("mode.debug", "mode.release")

-- ------------------------------------------- dependencies -------------------------------------------

-- add_requires("catch2 3", { system = false, configs = {components = {"main"}, }})

-- -- for clanged support run "xmake project -k compile_commands" to generate compile_commands.json

-- -------------------------------------------- helix --------------------------------------------

-- target("helix")
--     set_kind("binary")
--     set_warnings("all")
    
--     add_files("source/*.cc")    -- add all files in the source directory
--     add_files("source/**/*.cc") -- add all files in the source directory's subdirectories
    
--     set_languages("c++2b")      -- set the standard C++ version to C++2b
    
--     if is_mode("debug") then
--         set_symbols("debug")       -- Generate debug symbols
--         set_optimize("none")       -- Disable optimization
--         add_defines("DEBUG")       -- Define DEBUG macro
--         set_runtimes("MDd")        -- Use the debug version of the runtime library
--     else
--         set_symbols("hidden")      -- Hide symbols
--         set_optimize("fastest")    -- Enable maximum optimization
--         add_defines("NDEBUG")      -- Define NDEBUG macro
--         set_runtimes("MD")         -- Use the release version of the runtime library
--     end
    
--     add_includedirs("/opt/llvm-aarch64/include")
--     add_linkdirs   ("/opt/llvm-aarch64/lib")
    
--     add_links("clang", "clang-cpp", "c++", "c++abi") -- explicitly add LLVM libraries
--     -- "LLVM-18" removed
    
--     add_cxxflags("-stdlib=libc++", "-fno-rtti", "-I/opt/llvm-aarch64/include")
--     add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi", "-Wl,-rpath,/opt/llvm-aarch64/lib")

-- ----------------------------------------------- test -----------------------------------------------

-- target("tests")
--     set_kind("binary")
--     set_warnings("all")
    
--     add_files("tests/*.cc") -- add all files in the tests directory
    
--     if os.isdir("tests/*") then
--         add_files("tests/**/*.cc") -- add all files in the tests directory's subdirectories
--     end
    
--     set_languages("c++2b") -- set the standard C++ version to C++2b
--     set_optimize ("fastest")
    
--     add_includedirs("/opt/llvm-aarch64/include")
        
--     add_linkdirs   ("/opt/llvm-aarch64/lib")
    
--     add_links("clang", "clang-cpp", "c++", "c++abi", "Catch2", "Catch2Main") -- add LLVM libs
--     -- "LLVM-18" removed
    
--     add_cxxflags("-stdlib=libc++"         , "-fno-rtti", "-I/opt/llvm-aarch64/include")
--     add_ldflags ("-L/opt/llvm-aarch64/lib", "-lc++abi" , "-Wl,-rpath,/opt/llvm-aarch64/lib")

--     add_packages("catch2")

-- ----------------------------------------------- llvm -----------------------------------------------

-- before_build(function(target)
--     import("lib.detect.find_tool")
    
--     local llvm_config = find_tool("llvm-config", {paths = "/opt/llvm-aarch64/bin"})
    
--     if llvm_config then
--         local llvm_includedir = os.iorunv(llvm_config.program, {"--includedir"}):trim()
--         local llvm_libdir     = os.iorunv(llvm_config.program, {"--libdir"}):trim()
        
--         target:add("includedirs", llvm_includedir)
--         target:add("linkdirs", llvm_libdir)
--     else
--         raise("llvm-config not found!")
--     end
-- end)

-- -------------------------------------------- build modes -------------------------------------------

-- if is_mode("debug") then
--     set_runtimes("MDd")
-- else
--     set_runtimes("MD")
-- end

-- ----------------------------------------------------------------------------------------------------

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