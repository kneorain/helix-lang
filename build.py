import os
import platform
import subprocess

def set_env_vars():
    if platform.system() == "Windows":
        os.environ["LLVM_INCLUDE"] = "C:/Program Files/LLVM/include"
        os.environ["LLVM_LIB"] = "C:/Program Files/LLVM/lib"
        os.environ["LLVM_BIN"] = "C:/Program Files/LLVM/bin"
    elif platform.system() == "Darwin":  # macOS
        os.environ["LLVM_INCLUDE"] = "/opt/llvm-aarch64/include"
        os.environ["LLVM_LIB"] = "/opt/llvm-aarch64/lib"
        os.environ["LLVM_BIN"] = "/opt/llvm-aarch64/bin"
    else:
        raise RuntimeError("Unsupported OS")

def build_project():
    set_env_vars()
    # xmake f -p windows --sdk="C:/Program Files/LLVM"
    if platform.system() == "Windows":
        subprocess.run(["xmake", "f" "-p" "windows" "--sdk=\"C:/Program Files/LLVM\""])
    subprocess.run(["xmake", "build", "helix"], check=True)
    subprocess.run(["xmake", "run", "helix"], check=True)

if __name__ == "__main__":
    build_project()
