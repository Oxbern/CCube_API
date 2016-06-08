from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
           "control",                                # the extesion name
           sources=["control.pyx", "Controller.cpp"],
           include_dirs=['../include/'],
           language="c++",
           extra_compile_args=['-std=c++11']
      )))
