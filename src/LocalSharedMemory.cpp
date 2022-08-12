/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variabels across objects in the simulation.
*/

#include "LocalSharedMemory.hpp"

LocalSharedMemory::LocalSharedMemory(string iProjectHomeDir)
{
    // Assign Environment Parameters:
    initializeEnvironmentVariables(iProjectHomeDir);
    
    // Assign
    initializeSimulationParameters();
    initializeModelParameters();
}

/*
 Initialize Environment variables
*/
void LocalSharedMemory::initializeEnvironmentVariables(string iProjectHomeDir)
{
    cProjectHomeDir = iProjectHomeDir;
    cGenDir = iProjectHomeDir + "/Generated/";
    cParametersDir = iProjectHomeDir + "/Parameters/";
}

/*
 Initialize Global Simulation parameters
*/
void LocalSharedMemory::initializeSimulationParameters()
{
    setSimulationDuration(10.0);
    setSimulationTimeStep(1);
}

/*
Initialize model specific shared parameters
*/
void LocalSharedMemory::initializeModelParameters()
{
  // Pass
}
