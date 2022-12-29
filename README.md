# pyTecIO
A Python wrapper for Tecio to read and analyze Tecplot SZL files.

## Requirements
Python 3.7 or greater, may be compatible with previous versions. CMake is required.

## Installation
First the TecIO library and C/C++ interface must be compiled. To do this, in the root directory run
```
make
```
Once complete the Python module can be installed using pip
```
pip install .
```
## Usage
The module can be imported into python using
```python
include tecio
```
## TecIO
The TecIo source code is included in the repository. It is also available [here](https://www.tecplot.com/products/tecio-library/).
