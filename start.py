import sys, helix, subprocess, os
BUILD: bool = True
AUTO_BUILD: bool = True

BUILD_REV = open("build_rev.txt", "r").readlines()[0].strip()
RUN_COUNT = int(open("build_rev.txt", "r").readlines()[1].strip())

try: terminal_width = os.get_terminal_size().columns
except: terminal_width = 100

if BUILD_REV != helix.__version__ or helix.PRODUCTION_BUILD or (RUN_COUNT % 25 == 0 and AUTO_BUILD):
    BUILD = True
else:
    # increment the run count and write it to the file
    open("build_rev.txt", "w").write(BUILD_REV + "\n" + str(RUN_COUNT + 1))

def center(chat: str, text: str, width: int) -> str:
    return chat * int((width - len(text)) / 2) + text + chat * int((width - len(text)) / 2)

def build():
    from cx_Freeze import setup, Executable
    # Dependencies are automatically detected, but it might need fine tuning.
    setup(
        name="helix",
        version="0.1",
        author="Dhruvan Kartik",
        author_email="ze7111@gmail.com",
        license="CC0 1.0 Universal",
        description="Helix is a programming language that is designed to be simple and easy to use",
        options={
            "build_exe": {
                "packages": ["os", "sys", "subprocess", "rich", "re", "threading", "shutil", "json", "time", "argparse", "multimethod"],
                "optimize": 2,
                "include_msvcr": True
            },
            
        },
        executables=[
            Executable(
                "helix.py",
                base='Console',
                icon="helix.ico",
                
            )
        ],
    )

if "build_exe" not in sys.argv and BUILD:
    sys.argv.append("build_exe")

if "build_exe" in sys.argv or "build" in sys.argv:
    # increment the build number and write it to the file 0.0.1-alpha.a -> 0.0.1-alpha.b, 0.0.1-alpha.z -> 0.0.2-alpha.a etc.
    if BUILD_REV[-1] == "z": # increment the third number
        BUILD_REV = BUILD_REV.split(".")
        BUILD_REV[2] = str(int(BUILD_REV[2][0]) + 1) + BUILD_REV[2][1:]
        BUILD_REV[3] = "a"
        BUILD_REV = ".".join(BUILD_REV)

    else:
        BUILD_REV = BUILD_REV[:-1] + chr(ord(BUILD_REV[-1]) + 1)
    
    # if Production build, write the build number to the file, so 0.0.1-alpha.a -> 0.1.0-alpha.a, 0.1.0-alpha.z -> 0.1.0-alpha.z etc.
    # so incerement the second number and set the third number to 0
    if helix.PRODUCTION_BUILD:
        BUILD_REV = BUILD_REV.split(".")
        BUILD_REV[1] = str(int(BUILD_REV[1]) + 1)
        BUILD_REV[2] = '0' + BUILD_REV[2][1:]
        BUILD_REV[3] = "a"
        BUILD_REV = ".".join(BUILD_REV)
    
    open("build_rev.txt", "w").write(BUILD_REV + "\n" + str(RUN_COUNT + 1))
    
    data = (
        open("helix.py", "r", encoding="utf-8").read()
            .replace(f"PRODUCTION_BUILD: bool = {helix.PRODUCTION_BUILD}", f"PRODUCTION_BUILD: bool = False")
            .replace(f"__version__: str = \"{helix.__version__}\"", f"__version__: str = \"{BUILD_REV}\"")
    )
    
    with open("helix.py", "w", encoding="utf-8") as file:
        file.write(data)
    
    
    
    try: build()
    except Exception as e:
        print("\u001b[92m" + center("─", f" Build '{BUILD_REV}' Failed", terminal_width) + "\u001b[0m")
        raise e
    
    if exit_code := subprocess.call(f"build{os.sep}exe.win-amd64-3.12{os.sep}helix.exe", shell=True):
        print("\u001b[91m" + center("─", f" Build Test Run '{BUILD_REV}' Failed, With Exit ({exit_code})", terminal_width) + "\u001b[0m")
    else:
        print("\u001b[92m" + center("─", f" Build Test Run '{BUILD_REV}' Succeeded ", terminal_width) + "\u001b[0m")
    
    
    # zip the f"build{os.sep}exe.win-amd64-3.12 folder
    import shutil
    shutil.make_archive(f"build{os.sep}helix-{BUILD_REV}", "zip", f"build{os.sep}exe.win-amd64-3.12")
    
    sys.exit(0)
