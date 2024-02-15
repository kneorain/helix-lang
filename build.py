from cx_Freeze import setup, Executable
import sys, subprocess, os
# Dependencies are automatically detected, but it might need fine tuning.

if "build_exe" not in sys.argv:
    # c:/Users/dhruv/Documents/Projects/helix/venv/Scripts/python312.exe c:/Users/dhruv/Documents/Projects/helix/build.py build_exe
    subprocess.run([sys.executable, os.path.abspath(__file__), "build_exe"])
    sys.exit(0)

build_exe_options = {
    "zip_include_packages": ["encodings", "PySide6", "shiboken6"],
}

setup(
    name="helix",
    version="0.1",
    description="Helix is a programming language that is designed to be simple and easy to use",
    options={"build_exe": build_exe_options},
    executables=[Executable("start.py")],
)