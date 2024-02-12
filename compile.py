MODE = 1

from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize(
        "start.pyx",
        compiler_directives = {
            "language_level": "3"
        },
        nthreads = 10,
    )
)