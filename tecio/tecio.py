from ctypes import cdll, cast
from ctypes import c_void_p, c_int, c_double, c_char_p, byref
from ctypes import POINTER


from pkg_resources import resource_filename

pth = resource_filename(__name__, "libtecplotreader.so")

lib = cdll.LoadLibrary(pth)

class SZLreader(object):

    def __init__(self, filename, verbose=0):

        lib.SZL_new.argtypes = [c_char_p, c_int]
        lib.SZL_new.restype = c_void_p
        lib.SZL_delete.argtypes = [c_void_p]
        lib.SZL_delete.restype = c_void_p
        
        lib.SZL_get_nZones.argtypes = [c_void_p]
        lib.SZL_get_nZones.restype = c_int

        lib.SZL_get_solutionTime.argtypes = [c_void_p, c_int]
        lib.SZL_get_solutionTime.restype = c_double

        lib.SZL_read_variables.argtypes = [c_void_p, POINTER(c_char_p), c_int, POINTER(c_int), c_int, POINTER(c_int)]
        lib.SZL_read_variables.restype = c_void_p

        lib.SZL_get_variable.argtypes = [c_void_p, c_char_p, c_int, POINTER(c_int)]
        lib.SZL_get_variable.restype = POINTER(c_double)

        lib.SZL_is_var.argtypes = [c_void_p, c_char_p, c_int]
        lib.SZL_is_var.restype = c_int

        lib.SZL_get_NearestNeighbours.argtypes = [c_void_p, POINTER(c_double), POINTER(c_double), POINTER(c_double), c_int, c_int]
        lib.SZL_get_NearestNeighbours.restype = POINTER(c_int)

        lib.SZL_del_int.argtypes = [POINTER(c_int)]
        lib.SZL_del_int.restype = c_void_p

        lib.SZL_get_varByIndex.argtypes = [c_void_p, POINTER(c_int), c_int, c_char_p, c_int]
        lib.SZL_get_varByIndex.restype = POINTER(c_double)
        
        lib.SZL_del_double.argtypes = [POINTER(c_double)]
        lib.SZL_del_double.restype = c_void_p

        self.obj = lib.SZL_new(c_char_p(filename.encode('ascii')), verbose)


    def __del__(self):
        lib.SZL_delete(self.obj)

    def get_nZones(self):
        return lib.SZL_get_nZones(self.obj)

    def get_solutionTime(self, zone=1):
        return lib.SZL_get_solutionTime(self.obj, c_int(zone))

    def read_variables(self, varNames, zones, range=[-1,-1]):
        
        varNames = [v.encode('utf-8') for v in varNames]

        charArr = (c_char_p * len(varNames))()
        charArr[:] = varNames

        zoneArr = c_int * len(zones)
        zoneArr = zoneArr(*zones)

        rangeArr = c_int * len(range)
        rangeArr = rangeArr(*range)

        return lib.SZL_read_variables(self.obj, charArr, c_int(len(varNames)), zoneArr, c_int(len(zones)), rangeArr)

    def get_variable(self, varName, zone):

        varSize = c_int()#pass this by reference in c code

        var = lib.SZL_get_variable(self.obj, c_char_p(varName.encode('utf-8')), c_int(zone), byref(varSize))
        return var[:varSize.value]

    def is_var(self, varName, zone):

        return lib.SZL_is_var(self.obj, c_char_p(varName.encode('utf-8')), c_int(zone))

    def check_var_exist(self, varNames, zone):

        out = []
        for name in varNames:
            out.append( self.is_var(name, zone) )
        return out

    def get_NearestNeighbours(self, points, zone):

        x = [p[0] for p in points]
        y = [p[1] for p in points]
        z = [p[2] for p in points]

        np = len(x)

        x = (c_double * np) (*x)
        y = (c_double * np) (*y)
        z = (c_double * np) (*z)

        idx = lib.SZL_get_NearestNeighbours(self.obj, x, y, z, c_int(np), c_int(zone))
        out = idx[:np]
        lib.SZL_del_int(idx)

        return out

    def get_varByIndex(self, idx, varName, zone):

        n = len(idx)

        idx = (c_int * n) (*idx)

        var = lib.SZL_get_varByIndex(self.obj, idx, c_int(n), c_char_p(varName.encode('utf-8')), c_int(zone))
        out = var[:n]
        lib.SZL_del_double(var)

        return out
