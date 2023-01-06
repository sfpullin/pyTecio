#pragma once

#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <map>
#include <initializer_list>



class Zone{

    int id;
    int VERBOSE_LEVEL;
    void* inFile;
    double solutionTime;
    int32_t nVar;
    std::vector<std::string> varHeaders;
    std::map<std::string,int32_t> varMap;
    std::vector<std::vector<double>> variables; //This is memory inefficient, need to find a better way
    
    void read_solutionTime();
    void read_variableHeaders();
    void read_variable(std::string label, int *range);

    // Extraction routines

    int get_NearestNeighbour(std::vector<double> pos);

public:

    Zone(void* inFile, int id, int v);
    void read_variables(std::initializer_list<std::string> varNames = {});
    void read_variables(std::vector<std::string> , int *range);
    double get_solutionTime();
    std::vector<std::string> get_headers();
    std::vector<double> get_variable(std::string label);
    double* get_variable_ptr(std::string label, int *nNodes);

    // Extraction routines

    std::vector<int> get_NearestNeighbours(std::vector<std::vector<double>> points);
    std::vector<double> get_variableByIndex(std::vector<int> idx, std::string label);

};

class TecplotReaderSZL{

    int VERBOSE_LEVEL;
    void* inFile;
    int32_t nZones;
    std::vector<Zone*> zones;

    //void* get_inFile();

public:

    TecplotReaderSZL(char* inputFilename, int v);
    ~TecplotReaderSZL();

    void read_variables(std::initializer_list<std::string> varNames = {}, std::initializer_list<int> zones = {});
    void read_variables(char** varNames, int nVarNames, int* zones, int nZone, int *range);

    int32_t get_nZones();
    std::vector<std::string> get_headers(int zone);
    double get_solutionTime(int zone);
    std::vector<double> get_variable(std::string label, std::initializer_list<int> zones = {});
    double *get_variable_ptr(std::string label, int zone, int *nNodes);

    // Extraction routine

    std::vector<int> get_NearestNeighbours(std::vector<std::vector<double>> points, int zone);
    std::vector<double> get_variableByIndex(std::vector<int> idx, std::string label, int zone);
 
};