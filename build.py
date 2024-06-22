import os
import sys
import subprocess
import platform
import argparse
import json
import shutil

# Constants
LLVM_REPO = "https://github.com/llvm/llvm-project.git"
BUILD_DIR = os.path.abspath("./build")
LLVM_SRC_DIR = f"{BUILD_DIR}/llvm/llvm-latest-src"
BUILD_CONFIG_FILE = f"{BUILD_DIR}/build_config.json"
REQUIRED_TOOLS = ["git", "cmake", "ninja", "clang" if platform.system() != "Windows" else "cl"]

CORE_TIER_TARGETS = {
    "AArch64", "AMDGPU", "ARM", "AVR", "BPF", "Hexagon", "Lanai", "LoongArch", "Mips",
    "MSP430", "NVPTX", "PowerPC", "RISCV", "Sparc", "SystemZ", "VE", "WebAssembly", "X86", "XCore"
}
EXPERIMENTAL_TARGETS = {"ARC", "CSKY", "DirectX", "M68k", "SPIRV", "Xtensa"}

class Colors:
    red = "\u001b[91m"
    yellow = "\u001b[92m"
    green = "\u001b[93m"
    reset = "\u001b[0m"

# Utility functions
def check_prerequisites():
    missing_tools = []
    for tool in REQUIRED_TOOLS:
        if not shutil.which(tool):
            missing_tools.append(tool)
    if missing_tools:
        print(f"{Colors.red}error:{Colors.reset} The following required tools are not installed: {', '.join(missing_tools)}")
        sys.exit(1)

def clone_llvm_source():
    if not os.path.exists(LLVM_SRC_DIR):
        os.makedirs(os.path.dirname(LLVM_SRC_DIR), exist_ok=True)
        run_command(f"git clone --depth 1 {LLVM_REPO} {LLVM_SRC_DIR}")
        run_command(f"git config --add remote.origin.fetch '^refs/heads/users/*'", cwd=LLVM_SRC_DIR)
        run_command(f"git config --add remote.origin.fetch '^refs/heads/revert-*'", cwd=LLVM_SRC_DIR)

def run_command(command, cwd=None, check=True):
    result = subprocess.run(command, shell=True, cwd=cwd, check=check)
    return result.returncode

def save_config(config):
    with open(BUILD_CONFIG_FILE, "w") as f:
        json.dump(config, f)

def load_config():
    if os.path.exists(BUILD_CONFIG_FILE):
        with open(BUILD_CONFIG_FILE, "r") as f:
            return json.load(f)
    return {}

def build_llvm(target):
    llvm_build_dir = f"{BUILD_DIR}/llvm/llvm-build-{target}"

    if target in CORE_TIER_TARGETS:
        target_flag = f"-DLLVM_TARGETS_TO_BUILD={target}"
    elif target in EXPERIMENTAL_TARGETS:
        target_flag = f"-DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD={target}"
    else:
        print(f"{Colors.red}error:{Colors.reset} The target '{target}' is not recognized as a target. Choose from the following: \n" +
               ', '.join(CORE_TIER_TARGETS) + ', ' +
               ', '.join(EXPERIMENTAL_TARGETS))
        sys.exit(1)

    if not os.path.exists(llvm_build_dir):
        os.makedirs(llvm_build_dir, exist_ok=True)
        cmake_command = (
            f"cmake -S {os.path.abspath(LLVM_SRC_DIR)}/llvm -B {llvm_build_dir} -G Ninja "
            f"{target_flag} "
            f"-DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=clang "
            f"-DLLVM_ENABLE_LIBCXX=ON -DLLVM_ENABLE_LIBCXXABI=ON"
        )
        run_command(cmake_command, cwd=llvm_build_dir)
        run_command("ninja", cwd=llvm_build_dir)
    return llvm_build_dir

def generate_cmake(target, build_type, llvm_build_dir):
    build_dir = f"{BUILD_DIR}/build-{target}-{build_type}"
    if not os.path.exists(build_dir):
        os.makedirs(build_dir, exist_ok=True)
        cmake_command = (
            f"cmake ../.. -DCMAKE_BUILD_TYPE={build_type} "
            f"-DLLVM_DIR={os.path.abspath(llvm_build_dir)}/lib/cmake/llvm"
        )
        run_command(cmake_command, cwd=build_dir)
    return build_dir

def compile_project(build_dir):
    run_command("cmake --build .", cwd=build_dir)

def main():
    check_prerequisites()

    parser = argparse.ArgumentParser(description="Build script for Helix project")
    parser.add_argument("build_type", choices=["debug", "release"], help="Build type")
    parser.add_argument("--target", required=True, help="Target triple")
    parser.add_argument("action", choices=["build", "run"], help="Action to perform")

    args = parser.parse_args()
    build_type = args.build_type
    target = args.target
    action = args.action

    config = load_config()
    if target not in config:
        clone_llvm_source()
        llvm_build_dir = build_llvm(target)
        config[target] = {"llvm_build_dir": llvm_build_dir}
        save_config(config)
    else:
        llvm_build_dir = config[target]["llvm_build_dir"]

    # Set the environment variable for LLVM_DIR
    os.environ["LLVM_DIR"] = llvm_build_dir

    build_dir = generate_cmake(target, build_type, llvm_build_dir)

    if action == "build":
        compile_project(build_dir)
    elif action == "run":
        executable = os.path.join(build_dir, "helix")
        if platform.system() == "Windows":
            executable += ".exe"
        run_command(executable, check=False)

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(e)
