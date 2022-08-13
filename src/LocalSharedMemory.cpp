/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variables across objects in the simulation.
*/

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
    setSimulationDuration(3 * HR2SEC);
    // Simulation time step (sec)
    setSimulationTimeStep(1);
}

/*
Initialize model specific shared parameters if any
*/
void LocalSharedMemory::initializeModelParameters()
{
  // Pass
    return;
}
