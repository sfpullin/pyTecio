#include "tecplotReader.h"
#include <iostream>
#include <vector>

extern "C"
{

    TecplotReaderSZL *SZL_new(char* filename, int verbose) {return new TecplotReaderSZL(filename, verbose);}

    void SZL_delete(TecplotReaderSZL* reader ){ delete reader; }

    int SZL_get_nZones(TecplotReaderSZL * reader){ return reader->get_nZones();}

    double SZL_get_solutionTime(TecplotReaderSZL * reader, int zone){ return reader->get_solutionTime(zone); }

    void SZL_read_variables(TecplotReaderSZL * reader, char ** varNames, int nVarNames, int* zones, int nZone, int range[2]){

        return reader->read_variables(varNames, nVarNames, zones, nZone, range);

    }

    double* SZL_get_variable(TecplotReaderSZL * reader, char* label, int zone, int *nNodes){ 
        
        return reader->get_variable_ptr(label, zone, nNodes);
        
        }

}

/*
int main(){


    char filename[] = "../surface_flow.szplt";
    TecplotReaderSZL *reader = SZL_new(filename);

    std::cout << SZL_get_nZones(reader) << std::endl; 

    int zones[] = {1};
    int nZone = 1;
    char *varNames[] = {"Pressure", "x", "y", "z"};
    int nVarNames = 4;

    SZL_read_variables(reader, varNames, nVarNames, zones, nZone);

    double *a;
    char label[] = "z";

    a = SZL_get_variable(reader, label, 1);

    for (int ii = 10; ii < 30; ii++){

        std::cout << a[ii] << std::endl;

    }

    return 0;
}
*/