-- FIXME: rename main.cc to helix.cc
set_project("helix-lang")
set_version("0.0.1", {soname = true})
add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

-- Define the LLVM and Clang package
package("llvm-clang")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "libs", "llvm-18.1.9-src", "llvm"))
    on_install(function (package)
        local configs = {}

        table.insert(configs, "-DLLVM_ENABLE_PROJECTS=clang")

        table.insert(configs, "-DCMAKE_BUILD_TYPE=Release")  -- always build in release mode
        
        if is_tool("cc", "cl") or is_tool("cxx", "cl") then
            -- FIXME: add thing to do check thing windowws thing if msvc
            table.insert(configs, "-DLLVM_ENABLE_ZSTD=OFF")      -- disable ZSTD support
            table.insert(configs, "-DLLVM_ENABLE_ZLIB=OFF")      -- disable ZLIB support
            table.insert(configs, "-DLLVM_ENABLE_LIBXML2=OFF")   -- disable libxml2 support
        else
            table.insert(configs, "-DLLVM_ENABLE_ZSTD=FORCE_ON") -- enable ZSTD support
            table.insert(configs, "-DLLVM_ENABLE_ZLIB=FORCE_ON") -- enable ZLIB support
        end

        table.insert(configs, "-DLLVM_ENABLE_RTTI=ON")             -- enable RTTI for dynamic_cast and typeid
        table.insert(configs, "-DLLVM_ENABLE_BENCHMARKS=OFF")      -- turn off benchmarks
        table.insert(configs, "-DLLVM_INCLUDE_BENCHMARKS=OFF")     -- exclude benchmarks
        table.insert(configs, "-DLLVM_INCLUDE_TESTS=OFF")          -- exclude tests
        table.insert(configs, "-DLLVM_INCLUDE_DOCS=ON")            -- include documentation
        table.insert(configs, "-DLLVM_INCLUDE_EXAMPLES=ON")        -- exclude examples
        table.insert(configs, "-DLLVM_PARALLEL_LINK_JOBS=5")       -- parallelize
        
        import("package.tools.cmake").install(package, configs, {cmake_generator = "Ninja"})
    end)
package_end()

-- specify the use of the LLVM-Clang package
add_requires("llvm-clang")

-- TODO windows only oc
if os.host() == "windows" then 
    add_requires("zlib")
    add_requires("zstd")
end

-- platform-specific configuration for homebrew installed libs and includes
if os.host() == "macosx" then
    if os.exists("/opt/homebrew/include") and os.exists("/opt/homebrew/lib") then
        add_includedirs("/opt/homebrew/include")
        add_linkdirs("/opt/homebrew/lib")
    end
elseif os.host() == "linux" then
    if os.exists("/home/linuxbrew/.linuxbrew/include") and os.exists("/home/linuxbrew/.linuxbrew/lib") then
        add_includedirs("/home/linuxbrew/.linuxbrew/include")
        add_linkdirs("/home/linuxbrew/.linuxbrew/lib")
    end
elseif os.host() == "windows" then 
    add_includedirs(".\\libs\\llvm-18.1.9-src\\llvm\\include")
    add_linkdirs(".\\libs\\llvm-18.1.9-src\\llvm\\lib")
    add_includedirs(".\\libs\\llvm-18.1.9-src\\clang\\include")
    add_linkdirs(".\\libs\\llvm-18.1.9-src\\clang\\lib")
end

-- set up config
    local function configure_runtime()
        if is_kind("binary") then
            if is_tool("cc", "cl") or is_tool("cxx", "cl") then
                return "MT"
            elseif is_tool("cc", "clang") or is_tool("cxx", "clang") then
                return "c++_static"
            elseif is_tool("cc", "gcc") or is_tool("cxx", "g++") then
                return "stdc++_static"
            end
        end
        return ""
    end

    local use_runtime = configure_runtime()

    if is_mode("debug") then
        set_symbols("debug")       -- Generate debug symbols
        set_optimize("none")       -- Disable optimization
        add_defines("DEBUG")       -- Define DEBUG macro
    else
        set_runtimes("$(use_runtime)")
        set_symbols("hidden")      -- Hide symbols
        set_optimize("fastest")    -- Enable maximum optimization
        add_defines("NDEBUG")      -- Define NDEBUG macro
    end

    add_files("source/**.cc")    -- add all files in the source directory
    add_headerfiles("source/**.hh")    -- add all headers in the source directory
    add_includedirs("source")
    set_languages("c++23")      -- set the standard C++ version to C++23
    set_warnings("all")
    set_kind("binary")
    set_targetdir("$(buildir)/$(mode)/$(arch)-unknown-$(plat)/bin")
    set_objectdir("$(buildir)/.resolver")
    set_dependir("$(buildir)/.shared")
    set_policy("build.across_targets_in_parallel", true) -- optimization
    add_packages("llvm-clang")  -- link against the LLVM-Clang package
    if os.host() == "windows" then
        add_packages("zlib")
        add_packages("zstd")
        add_syslinks("ntdll", "version")
    end
    add_links("zstd")
    set_description("The Helix Compiler. Python's Simplicity, Rust inspired Syntax, and C++'s Power")
-- end config

target("tests")
    add_files("tests/**.cc")    -- add all files in the tests directory
    remove_files("source/main.cc")  -- exclude main.cc from the source directory

    add_headerfiles("tests/**.hh")    -- add all headers in the tests directory
    add_includedirs("tests/lib")
    set_symbols("debug")       -- Generate debug symbols
    set_optimize("none")       -- Disable optimization
    add_defines("DEBUG")       -- Define DEBUG macro
target_end()

target("helix")
target_end()

target("helix-api")
    set_kind("static")
    set_targetdir("$(buildir)/$(mode)/$(arch)-unknown-$(plat)")

    after_build(function (target)  -- make the helix library with all the appropriate header files
        import("core.project.task")

        -- Determine the target output directory
        local target_dir = path.directory(target:targetfile())

        -- Create directories for library and headers
        os.mkdir(path.join(target_dir, "api/lib"))
        os.mkdir(path.join(target_dir, "api/include"))

        -- Move the compiled library to the 'lib' folder
        os.cp(target:targetfile(), path.join(target_dir, "api/lib/"))
        os.rm(target:targetfile())

        -- Copy header files to the 'include' folder
        local headers = os.files("source/**.hh")
        for _, header in ipairs(headers) do
            local rel_path = path.relative(header, "source")
            os.mkdir(path.join(target_dir, "api/include", path.directory(rel_path)))
            os.cp(header, path.join(target_dir, "api/include", rel_path))
        end

        local file = io.open(path.join(target_dir, "api", "xmake.lua"), "w")
        file:write([[
target("helix-api")
    set_kind("static")
    add_files("lib/*.a")
    add_includedirs("include")
    add_headerfiles("include/**.hh")
]])
        file:close()
    end)
target_end()
