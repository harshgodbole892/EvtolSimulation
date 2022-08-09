/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variabels across objects in the simulation.
*/

#include "LocalSharedMemory.hpp"

//1. Structure of Constants
LocalSharedMemory::LocalSharedMemory()
{
    initializeSimulationParameters();
    initializeModelParameters();
}

/*
 Initialize Global Simulation parameters
*/
void LocalSharedMemory::initializeSimulationParameters()
{
    double cSimulationDuration      = 10.0;
    double cSimulationIterationRate = 0.1;
}

/*
Initialize model specific shared parameters
*/
void LocalSharedMemory::initializeModelParameters()
{
  // Pass
}
