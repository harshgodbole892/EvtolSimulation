/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variables across objects in the simulation.
                This class is called Local shared memory so as not to confuse
                it with process shared memory.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <map>
#include <mutex>

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
    int getNumOfVehicles(){return cNumOfVehicles; }
    int getMaxChargingStations(){return cMaxChargingStations; }
    int getOptUniqueSeedForRand(){return oUseUniqueSeedForRand;}
    
    string getProjectHomeDir(){return cProjectHomeDir; }
    string getGenDir(){return cGenDir; }
    string getParametersDir(){return cParametersDir; }
    
    map<int, string> getVehicleTypeMap(){return mVehicleTypeMap; }
    map<string, int> getVehicleTypeRevMap(){return mVehicleTypeRevMap; }
    
    // Setters for private variables:
    void setIterationIndex(int iInput);
    
    
    // Constructor:
    LocalSharedMemory(string iProjectHomeDir);
    
    // Internal functions:
    void initializeSimulationParameters();
    void initializeModelParameters();
    void initializeEnvironmentVariables(string iProjectHomeDir);

private:
    
    // Simulation Parameters, Constants
    double cSimulationDuration{10.0};        // Simulation total duration (sec)
    double cSimulationTimeStep{1.0};         // Simulation iteration rate (sec)
    int mIterationIndex{0};                  // Simulation Iteration index
    long long int mCollectSize{0};           // Collect size for all collected variabels
    
    // Env Vars: Constants
    string cProjectHomeDir{""};
    string cGenDir{"/generated/"};
    string cParametersDir{"/parameters/"};
    
    // Model Parameters:
    
    // Constants:
    int cNumOfVehicles{20};
    int cMaxChargingStations{3};
    
    // Members:
    map<int, string> mVehicleTypeMap;     // Vehicle Type map: From int key to String
    map<string, int> mVehicleTypeRevMap;  // Vehicle Type reverse map: from string to type
    
    // Mutex for public write functions:
    mutex mCommonMutex;
    
    // Simulation Options:
    int oUseUniqueSeedForRand{0};
    
    // Private functions for setters for precautions for thread safety:
    void setSimulationDuration(double iInput){  cSimulationDuration = iInput; }
    void setSimulationTimeStep(double iInput){  cSimulationTimeStep = iInput; }
    void setNumberOfVehicles(int iInput){ cNumOfVehicles = iInput; }
    void setMaxChargingStations(int iInput){ cMaxChargingStations = iInput; }

};

#endif

