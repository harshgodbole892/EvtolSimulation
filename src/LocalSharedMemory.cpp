/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variables across objects in the simulation.
*/

#include <stdlib.h>
#include <mutex>
#include "LocalSharedMemory.hpp"
#include "CommonDefines.hpp"

LocalSharedMemory::LocalSharedMemory(string iProjectHomeDir)
{
    // Assign Environment Parameters
    initializeEnvironmentVariables(iProjectHomeDir);
    
    // Assign Simuation Specific parameters
    initializeSimulationParameters();
    initializeModelParameters();
}

/*
 Initializes the environemnt varaibles used across components to initialize data
 or write results
*/
void LocalSharedMemory::initializeEnvironmentVariables(string iProjectHomeDir)
{
    cProjectHomeDir = iProjectHomeDir;
    cGenDir = iProjectHomeDir + "/Generated/";
    cParametersDir = iProjectHomeDir + "/Parameters/";
}

/*
 Initializes simulation parameters used across all components
*/
void LocalSharedMemory::initializeSimulationParameters()
{
    // Total simulation duration (sec)
    cSimulationDuration = 3 * HR2SEC;
    // Simulation time step (sec)
    cSimulationTimeStep = 60;  // 1 min time step
    
    // Note that smallest possible time step
    // is 0.001s with RT dispatcher
    // Time step is also limited depending on the type of C++
    // distrubution used. Limit to 1 sec for effective random
    // number generation.
}

/*
Initialize model specific shared parameters if any
*/
void LocalSharedMemory::initializeModelParameters()
{
    // Ensure that mapping is 1 to 1!!
    mVehicleTypeMap.insert(pair<int, string>(1, "Alpha"));
    mVehicleTypeMap.insert(pair<int, string>(2, "Beta"));
    mVehicleTypeMap.insert(pair<int, string>(3, "Charlie"));
    mVehicleTypeMap.insert(pair<int, string>(4, "Delta"));
    mVehicleTypeMap.insert(pair<int, string>(5, "Echo"));
    
    // Reverse map fails if mapping is not 1 to 1
    for (const auto& key : mVehicleTypeMap) {
        mVehicleTypeRevMap.insert(pair<string, int>(key.second, key.first));
    }
    
    cNumOfVehicles = 20;
    cMaxChargingStations = 3;
}

/*
 This is the only function that can possibly be called by 2 threads at the same time.
 With the structure of the simulation as is, this will never happen.
 
 Mutex is included in here only as a demonstator.
*/
void LocalSharedMemory::setIterationIndex(int iInput)
{
    mCommonMutex.lock();

    mIterationIndex = iInput;

    mCommonMutex.unlock();
}
