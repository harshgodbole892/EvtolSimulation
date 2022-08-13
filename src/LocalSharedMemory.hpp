/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variables across objects in the simulation.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;
#ifndef LOCALSHAREDMEMORY_H
#define LOCALSHAREDMEMORY_H

class LocalSharedMemory
{
public:
    
    // Getters for private variables:
    double getSimulationDuration(){ return cSimulationDuration; }
    double getSimulationTimeStep(){ return cSimulationTimeStep; }
    int getIterationIndex(){return mIterationIndex; }
    string getProjectHomeDir(){return cProjectHomeDir; }
    string getGenDir(){return cGenDir;}
    string getParametersDir(){return cParametersDir;}
    
    // Setters for private variables:
    void setSimulationDuration(double iInput){  cSimulationDuration = iInput; }
    void setSimulationTimeStep(double iInput){  cSimulationTimeStep = iInput; }
    void setIterationIndex(int iInput){  mIterationIndex = iInput; }

    
    // Constructor:
    LocalSharedMemory(string iProjectHomeDir);
    
    // Internal functions:
    void initializeSimulationParameters();
    void initializeModelParameters();
    void initializeEnvironmentVariables(string iProjectHomeDir);

private:
    double cSimulationDuration{10.0};        // Simulation total duration (sec)
    double cSimulationTimeStep{1.0};         // Simulation iteration rate (sec)
    int mIterationIndex{0};                  // Simulation Iteration index
    long long int mCollectSize{0};           // Collect size for all collected variabels
    
    // Env Vars:
    string cProjectHomeDir{""};
    string cGenDir{"/generated/"};
    string cParametersDir{"/parameters/"};
};

#endif
