from Cython.Build import cythonize
from setuptools import setup

MODE = 1

# distutils: language=c++

with open("start.py", "r", encoding="utf-8") as file:
    code = file.read()

with open("start.pyx", "w", encoding="utf-8") as file:
    file.write("# distutils: language=c++\n\n" + code)

input("Press any key to continue...")

setup(
    ext_modules=cythonize(
        "start.pyx",
        compiler_directives={"language_level": "3"},
        nthreads=10,
    )
)
