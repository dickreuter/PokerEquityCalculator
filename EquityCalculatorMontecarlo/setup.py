import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

ext_modules = [
    Extension(
    'wrap',
        ['Scoring.cpp'],
        include_dirs=['C:/Users/dickr/Anaconda3/include'],
    language='c++',
    extra_compile_args = cpp_args,
    ),
]

setup(
    name='wrap',
    version='0.0.1',
    author='Nicolas Dickreuter',
    author_email='dickreuter@gmail.com',
    description='Poker equity calculator',
    ext_modules=ext_modules,
)