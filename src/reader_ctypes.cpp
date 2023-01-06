#include "tecplotReader.h"
#include <iostream>
#include <vector>
#include <string>

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

    int SZL_is_var(TecplotReaderSZL * reader, char* label, int zone){

        std::string l = label;
        std::vector<std::string> headers = reader->get_headers(zone);
        int is_found = 0;
        for (auto & h : headers) {
            if (h == l){
                is_found++;
            }
        }

        return is_found;

    }

    int* SZL_get_NearestNeighbours(TecplotReaderSZL * reader, double *x, double *y, double *z, int np, int zone){

        std::vector<std::vector<double>> p;
        std::vector<double> row;

        for (int ii = 0; ii < np; ii++){
            row.push_back(x[ii]);
            row.push_back(y[ii]);
            row.push_back(z[ii]);
            p.push_back(row);
            row.clear();
        }

        std::vector<int> NN = reader->get_NearestNeighbours(p, zone);
        int* out = new int[np];

        for (int ii = 0; ii < np; ii++){
            out[ii] = NN[ii];
        }
        return out;

    }

    void SZL_del_int(int * var){
        delete var;
    }

    double* SZL_get_varByIndex(TecplotReaderSZL * reader, int* idx, int nidx, char* label, int zone){

        std::vector<int> index;

        for (int ii = 0; ii < nidx; ii++){
            index.push_back(idx[ii]);
        }

        std::vector<double> var = reader->get_variableByIndex(index, std::string(label), zone );
        double* out = new double[nidx];

        for (int ii = 0; ii < nidx; ii++){
            out[ii] = var[ii];
        }
        return out;

    }

    void SZL_del_double(double * var){
        delete var;
    }

}

