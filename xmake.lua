-- FIXME: rename main.cc to helix.cc
set_project("helix-lang")
set_version("0.0.1", {soname = true})
add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

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
        if is_plat("windows") then
            set_runtimes("$(use_runtime)d")
        end
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
