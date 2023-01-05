from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext

import sys
import subprocess

with open("README.md") as file:
    long_description = file.read()

REQUIREMENTS = []

CLASSIFIERS = [
'Development Status :: 2 - Pre-Alpha',
'Intended Audience :: Developers',
'Topic :: Internet',
'License :: OSI Approved :: MIT License',
'Programming Language :: Python :: 3.7',
'Programming Language :: Python :: 3.8',
'Programming Language :: Python :: 3.9',
'Programming Language :: Python :: 3.10',
]


setup(name='tecio',
version='0.3.2',
description='Wrapper for the C++ implementation of Tecio for interfacing with Tecplot SZL files',
long_description=long_description,
url='',
author='Shaun Pullin',
author_email='',
license='MIT',
classifiers=CLASSIFIERS,
install_requires=REQUIREMENTS,
packages=['tecio'],
package_data={'tecio': ['*.so']},
#include_package_data=True,
keywords='tecplot reader szl szplt'
)

