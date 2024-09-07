function install_llvm_clang(package)
	-- Set the number of Cores to use for parallel compilation
	local threads_avaliable = os.cpuinfo("ncpu") - 3

	local configs = {}

	table.insert(configs, "-DLLVM_ENABLE_PROJECTS=clang")
	table.insert(configs, "-DCMAKE_BUILD_TYPE=Release")                   -- always build in release mode

	table.insert(configs, "-DLLVM_ENABLE_ZSTD=ON")                        -- disable ZSTD support
	table.insert(configs, "-DLLVM_ENABLE_ZLIB=ON")                        -- disable ZLIB support

	table.insert(configs, "-DLLVM_ENABLE_RTTI=ON")                        -- enable RTTI for dynamic_cast and typeid
	table.insert(configs, "-DLLVM_ENABLE_BENCHMARKS=OFF")                 -- turn off benchmarks
	table.insert(configs, "-DLLVM_INCLUDE_BENCHMARKS=OFF")                -- exclude benchmarks
	table.insert(configs, "-DLLVM_INCLUDE_TESTS=OFF")                     -- exclude tests
	table.insert(configs, "-DLLVM_INCLUDE_DOCS=ON")                       -- include documentation
	table.insert(configs, "-DLLVM_INCLUDE_EXAMPLES=ON")                   -- exclude examples
	table.insert(configs, "-DLLVM_PARALLEL_LINK_JOBS=" .. threads_avaliable) -- parallelize

	import("package.tools.cmake").install(package, configs, { cmake_generator = "Ninja" })
end

-- Define the LLVM and Clang package
package("llvm-clang")

add_deps("cmake", "ninja") -- , "zlib", "zstd" , "perl"
set_sourcedir(path.join(os.scriptdir(), "libs", "llvm-18.1.9-src", "llvm"))
on_install(install_llvm_clang)

package_end()



-- FIXME: rename main.cc to helix.cc
set_project("helix-lang")
add_rules("mode.debug", "mode.release")


-- add_rules("plugin.compile_commands.autoupdate")
set_version("0.0.1", { soname = true })
set_description("The Helix Compiler. Python's Simplicity, Rust inspired Syntax, and C++'s Power")

-- Requires
add_requires("zlib")
add_requires("zstd")
add_requires("llvm-clang")

-- Packages
add_packages("llvm-clang") -- link against the LLVM-Clang package
add_packages("zlib")
add_packages("zstd")

-- Global Links
add_links("zstd")


function get_abi()
	-- if is_tool("cc", "cl") or is_tool("cxx", "cl")
	-- then
	-- 	return "msvc"
	-- elseif is_tool("cc", "clang") or is_tool("cxx", "clang") then
	-- 	return "llvm"
	-- elseif is_tool("cc", "gcc") or is_tool("cxx", "g++") then
	-- 	return "gcc"
	-- end

	return "" -- error?
end

function get_runtime(abi)
	if abi == "llvm"
	then
		return "c++_static"
	elseif abi == "gcc"
	then
		return "stdc++_static"
	elseif abi == "msvc"
	then
		if is_mode("debug")
		then
			return "MTd"
		else
			return "MT"
		end
	end
	return "" -- error?
end

function setup_windows()
	add_syslinks("ntdll", "version")

	add_rules("plugin.vsxmake.autoupdate")

	add_includedirs(".\\libs\\llvm-18.1.9-src\\llvm\\include")
	add_linkdirs(".\\libs\\llvm-18.1.9-src\\llvm\\lib")
	add_includedirs(".\\libs\\llvm-18.1.9-src\\clang\\include")
	add_linkdirs(".\\libs\\llvm-18.1.9-src\\clang\\lib")
end

function setup_linux()
	if os.exists("/home/linuxbrew/.linuxbrew/include") and os.exists("/home/linuxbrew/.linuxbrew/lib") then
		add_includedirs("/home/linuxbrew/.linuxbrew/include")
		add_linkdirs("/home/linuxbrew/.linuxbrew/lib")
	end

	-- check if perl is is installed

	-- it only works with set alternatives
	-- local ld = os.getenv("LD");

	-- if ld == nil then
	-- 	print("The `LD` environment variable must contain the path to the lld executable")
	-- elseif not (path.filename(ld) == "ld.lld") then
	-- 	print("The `LD` environment variable must contain the path to the lld executable, it contains: ", ld)
	-- end
	-- use with lld os.runv("echo", {"hello", "xmake!"})
	--setenv({ LD = os.getenv("HELIX_LLD") })
end

function setup_macos()
	if os.exists("/opt/homebrew/include") and os.exists("/opt/homebrew/lib") then
		add_includedirs("/opt/homebrew/include")
		add_linkdirs("/opt/homebrew/lib")
	end
end

function setup_debug()
	set_symbols("debug") -- Generate debug symbols
	set_optimize("none") -- Disable optimization
	add_defines("DEBUG") -- Define DEBUG macro
end

function setup_release()
	set_symbols("hidden") -- Hide symbols
	set_optimize("fastest") -- Enable maximum optimization
	add_defines("NDEBUG") -- Define NDEBUG macro
end

local function setup_build_folder()
	set_targetdir("$(buildir)/$(mode)/$(arch)-unknown-$(plat)/bin")
	set_objectdir("$(buildir)/.resolver")
	set_dependir("$(buildir)/.shared")
end

local function setup_env()
	-- Setup OS specific settings
	if os.host() == "windows"
	then
		print("OS Target: Win32")
		setup_windows()
	elseif os.host() == "macosx"
	then
		print("OS Target: Darwin")
		setup_macos()
	elseif os.host() == "linux"
	then
		print("OS Target: Linux")
		setup_linux()
	end

	-- Setup build mode specific settings
	if is_mode("debug")
	then
		print("Mode: Debug")
		setup_debug()
	else
		print("Mode: Release")
		setup_release()
	end

	print("Build Policy: parallel")
	set_policy("build.across_targets_in_parallel", true) -- optimization

	-- -Wall
	print("Warnings: All")
	set_warnings("all")

	-- Set Languages
	print("Language: C++ 23")
	set_languages("c++23")
end



local function helix_src_setup()
	-- Include dir
	add_includedirs("source")

	-- Add source fikes
	add_files("source/**.cc") -- add all files in the source directory

	-- Header files
	add_headerfiles("source/**.hh") -- add all headers in the source directory
	add_headerfiles("source/**.def")
	add_headerfiles("source/**.inc")
end

-- Set up build folder

setup_build_folder()
setup_env()


local abi     = get_abi()
local runtime = get_runtime(abi)

-- this does not work
print("ABI: " .. abi .. "\nRuntime: " .. runtime)

set_runtimes(runtime)


helix_src_setup()

target("tests")
set_kind("binary")
add_files("tests/**.cc")        -- add all files in the tests directory
add_includedirs("tests/lib")    -- add all libs in the tests dir

remove_files("source/helix.cc") -- exclude main from the source directory

target_end()

target("helix") -- target config defined in the config seciton
set_kind("binary")
set_languages("c++23")

target_end() -- empty target




target("helix-api")
set_kind("static")
set_targetdir("$(buildir)/$(mode)/$(arch)-unknown-$(plat)")
helix_src_setup()
after_build(function(target) -- make the helix library with all the appropriate header files
	-- determine the target output directory
	local target_dir = path.directory(target:targetfile())

	local api_path = path.join(target_dir, "api")
	local api_lib_path = path.join(api_path, "lib")
	local api_include_path = path.join(api_path, "include")
	local api_lib_target_file = path.join(api_lib_path, target:filename())
	local api_xmake_lua = path.join(api_path, "xmake.lua")

	-- create directories for library and headers
	os.mkdir(api_lib_path)
	os.mkdir(api_include_path)

	-- move the compiled library to the 'lib' folder and
	os.cp(target:targetfile(), api_lib_target_file)
	os.rm(target:targetfile())

	-- copy header files to the 'include' folder
	local headers = os.files("source/**.hh")

	for _, header in ipairs(headers) do
		local rel_path = path.relative(header, "source")
		os.mkdir(path.join(api_include_path, path.directory(rel_path)))
		os.cp(header, path.join(api_include_path, rel_path))
	end

	-- Write the xmake config file
	local file = io.open(api_xmake_lua, "w")

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
print("-----------------------------------------------------------------------------------------------")
