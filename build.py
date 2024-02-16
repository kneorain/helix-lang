from cx_Freeze import setup, Executable
import sys, subprocess, os
# Dependencies are automatically detected, but it might need fine tuning.

if "build_exe" not in sys.argv:
    # c:/Users/dhruv/Documents/Projects/helix/venv/Scripts/python312.exe c:/Users/dhruv/Documents/Projects/helix/build.py build_exe
    subprocess.run([sys.executable, os.path.abspath(__file__), "build_exe"])
    sys.exit(0)

setup(
    name="helix",
    version="0.1",
    author="Dhruvan Kartik",
    author_email="ze7111@gmail.com",
    license="CC0 1.0 Universal",
    description="Helix is a programming language that is designed to be simple and easy to use",
    options={
        "build_exe": {
            "packages": ["os", "sys", "subprocess", "re", "threading", "shutil", "json", "time", "argparse"],
        },
        "optimize": 2,
        "include_msvcr": True
        
    },
    
    executables=[
        Executable(
            "start.py",
            icon="helix.ico",
            
        )
    ],
)