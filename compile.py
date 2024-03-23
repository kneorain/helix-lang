#from Cython.Build import cythonize
#from setuptools import setup
#
#MODE = 1
#
## distutils: language=c++
#
#with open("start.py", "r", encoding="utf-8") as file:
#    code = file.read()
#
#with open("start.pyx", "w", encoding="utf-8") as file:
#    file.write("# distutils: language=c++\n\n" + code)
#
#input("Press any key to continue...")
#
#setup(
#    ext_modules=cythonize(
#        "start.pyx",
#        compiler_directives={"language_level": "3"},
#        nthreads=10,
#    )
#)

import subprocess
import os
import sys

COMPILER_PATH = r"c:\Programing Languages\LLVM\bin\gcc.exe"

def compile_file(file_name):
    # Determine if the path is absolute or relative
    if os.path.isabs(file_name):
        # It's an absolute path
        full_path = file_name
    else:
        # It's a relative path, prepend the standard path
        full_path = os.path.join("src", "lib", "src", file_name)

    # set the path to the relative path
    full_path = os.path.relpath(full_path)

    # Extract the file name without extension from the full path
    file_name_no_extension = os.path.splitext(os.path.basename(full_path))[0]

    # Compile the file using GCC
    command = [
        f"\"{COMPILER_PATH}\"",
        "-std=gnu18",
        "-shared",
        "-o", f"\"{os.path.join('src', 'lib', f'{file_name_no_extension}.dll')}\"",
        "-fPIC",
        f"\"{full_path}\""
    ]
    print(" ".join(command))
    compile_status = subprocess.call(" ".join(command), shell=True)

    # Check if compilation was successful
    if compile_status != 0:
        print("\u001b[91mCompilation failed.\u001b[0m")
        sys.exit(1)
    else:
        print("\u001b[92mCompilation successful.\u001b[0m")

if __name__ == "__main__":
    # Check if file name argument is provided
    if len(sys.argv) < 2:
        print("No file name provided.")
        sys.exit(1)

    file_name = sys.argv[1]
    compile_file(file_name)

#"c:\Programing Languages\LLVM\bin\gcc.exe" -std=gnu18 -c "src\lib\src\remove_blank_lines.c"
#"c:\Programing Languages\LLVM\bin\gcc.exe" -std=gnu18 -shared -o "src\lib\remove_blank_lines.dll" -fPIC "remove_blank_lines.o"