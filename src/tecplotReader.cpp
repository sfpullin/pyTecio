#include "tecplotReader.h"
#include "TECIO.h"

#include <initializer_list>


TecplotReaderSZL::TecplotReaderSZL(char* inputFilename, int v){

    this->VERBOSE_LEVEL = v;

    tecFileReaderOpen(inputFilename, &this->inFile);

    tecDataSetGetNumZones(this->inFile, &this->nZones);
    if (this->VERBOSE_LEVEL > 0){
        std::cout << "Found " << this->nZones << " Zones" << std::endl;
    }

    double solTime;
    int32_t nVar;
    int64_t nNodes, nNodesTest;

    for (int32_t ii = 0; ii < this->nZones; ii++){

        if (this->VERBOSE_LEVEL > 0){
            std::cout << "\tZone " << ii + 1 << std::endl; 
        }
        this->zones.push_back( new Zone(inFile, ii + 1, v) );

    }


}

TecplotReaderSZL::~TecplotReaderSZL(){

    for (auto p : zones){
        delete p;
    }
    zones.clear();

    tecFileReaderClose(&inFile);

}

void TecplotReaderSZL::read_variables(std::initializer_list<std::string> varNames, std::initializer_list<int> zones){

    if (zones.size() == 0){
        for(int ii = 0; ii < this->zones.size(); ii++){
            this->zones[ii]->read_variables(varNames);
        }
    } else {
        for (auto z: zones){
            this->zones[z-1]->read_variables(varNames);
        }
    }

}


void TecplotReaderSZL::read_variables(char **varNames, int nVarNames, int * zones, int nZone, int *range){

    std::vector<std::string> strVec;
    for (int ii = 0; ii < nVarNames; ii++){
        strVec.push_back(varNames[ii]);
    }

    for (int ii = 0; ii < nZone; ii++){
        this->zones[ii]->read_variables(strVec, range);
    }
}

int32_t TecplotReaderSZL::get_nZones(){
        return this->nZones;
    }


std::vector<double> TecplotReaderSZL::get_variable(std::string label, std::initializer_list<int> zones ){

    std::vector<double> outputVar(0);
    std::vector<double> tmp;

    if (zones.size() == 0){
        for(int ii = 0; ii < this->zones.size(); ii++){
            tmp = this->zones[ii]->get_variable(label);
            outputVar.insert(outputVar.end(), tmp.begin(), tmp.end());
        }
    } else {
        for (auto z: zones){
            tmp = this->zones[z-1]->get_variable(label);
            outputVar.insert(outputVar.end(), tmp.begin(), tmp.end());
        }        
    }

    return outputVar;

}




double* TecplotReaderSZL::get_variable_ptr(std::string label, int zone, int * nNodes ){

    return this->zones[zone-1]->get_variable_ptr(label, nNodes);

}


std::vector<std::string> TecplotReaderSZL::get_headers(int zone){

    return this->zones[zone - 1]->get_headers();

}

double TecplotReaderSZL::get_solutionTime(int zone){

    return this->zones[zone-1]->get_solutionTime();

}

// ===============================================================================================

// ===============================================================================================


Zone::Zone(void *inFile, int id, int v){

    this->id = id;
    this->VERBOSE_LEVEL = v;
    this->inFile = inFile;
    this->read_solutionTime();
    this->read_variableHeaders();

}

void Zone::read_solutionTime(){

    tecZoneGetSolutionTime(inFile, 1, &this->solutionTime);
    if (this->VERBOSE_LEVEL > 0){
        std::cout << "\tSolution Physical Time: " << solutionTime << " seconds" << std::endl;
    }

}

void Zone::read_variableHeaders(){

    tecDataSetGetNumVars(inFile, &this->nVar);
    if (this->VERBOSE_LEVEL > 0){
        std::cout << "There are " << nVar << " Variables" << std::endl;
        std::cout << "Variable Names:" << std::endl;
    }

    for (int32_t ii = 1; ii <= nVar; ii++){

        char* varName = NULL;
        tecVarGetName(inFile, ii, &varName);

        this->varHeaders.push_back(varName);
        this->varMap[varName] = ii;

        this->variables.push_back(std::vector <double>(0));

        if (this->VERBOSE_LEVEL > 0){
            std::cout << std::setfill(' ') << std::setw(5) << ii; 
            std::cout << " : " << varName << std::endl;
        }

    }

}

void Zone::read_variables(std::initializer_list<std::string> varNames){

    int range[] = {-1, -1}; //tmp

    if (varNames.size() == 0){
        for ( int ii = 0; ii < this->varHeaders.size(); ii++){
            this->read_variable(this->varHeaders[ii], range);
            if (this->VERBOSE_LEVEL > 0){
                std::cout << "Variable: " << this->varHeaders[ii] << " read from Zone " << this->id << std::endl;
            }
        }
    } else{
        for (auto name : varNames) {
            this->read_variable(name, range);
            if (this->VERBOSE_LEVEL > 0){
                std::cout << "Variable: " << name << " read from Zone " << this->id << std::endl;
            }
        }
    }

}


void Zone::read_variables(std::vector<std::string> varNames, int *range){

    if (varNames.size() == 0){
        for ( int ii = 0; ii < this->varHeaders.size(); ii++){
            this->read_variable(this->varHeaders[ii], range);
            if (this->VERBOSE_LEVEL > 0){
                std::cout << "Variable: " << this->varHeaders[ii] << " read from Zone " << this->id << std::endl;
            }
        }
    } else{
        for (auto name : varNames) {
            this->read_variable(name, range);
            if (this->VERBOSE_LEVEL > 0){
                std::cout << "Variable: " << name << " read from Zone " << this->id << std::endl;
            }
        }
    }

}


void Zone::read_variable(std::string label, int *range){

    int64_t nodes;
    int32_t idx = this->varMap[label];

    tecZoneVarGetNumValues(inFile, this->id, idx, &nodes);

    if (range[0] == -1 || range[1] == -1){
        
        range[0] = 1;
        range[1] = nodes;
    }

    std::vector<double> var(nodes);
    tecZoneVarGetDoubleValues(inFile, this->id, idx, range[0], range[1], &var[0]);

    this->variables[idx - 1] = var;

    return;

}


std::vector<double> Zone::get_variable(std::string label){

    int32_t idx = this->varMap[label];

    if (idx == 0){
        std::cerr << "Error: variable with label " << label << " not recognised." << std::endl;
    } else if (this->variables[idx - 1].size() == 0){
        std::cerr << "Error: variable " << label << " is empty. Read data into variable using the read_variables() method." << std::endl;
    }

    return this->variables[idx - 1];

}

double* Zone::get_variable_ptr(std::string label, int *nNodes){

    int32_t idx = this->varMap[label];

    if (idx == 0){
        std::cerr << "Error: variable with label " << label << " not recognised." << std::endl;
    } else if (this->variables[idx - 1].size() == 0){
        std::cerr << "Error: variable " << label << " is empty. Read data into variable using the read_variables() method." << std::endl;
    }

    *nNodes = this->variables[idx - 1].size();

    return &this->variables[idx - 1][0];

}

std::vector<std::string> Zone::get_headers(){

    return this->varHeaders;

}


double Zone::get_solutionTime(){

    return this->solutionTime;

}
