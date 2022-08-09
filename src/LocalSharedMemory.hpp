/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Local Shared Memory
Class Type    : Simluation Support
 
Description   : Used to share variabels across objects in the simulation.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;
#ifndef LOCALSHAREDMEMORY_H
#define LOCALSHAREDMEMORY_H

//1. Structure of Constants
class LocalSharedMemory
{
public:
    
    // Getters for private variables:
    double getSimulationDuration(){ return cSimulationDuration; }
    double getSimulationIteration(){ return cSimulationIterationRate; }
    
    // Setters for private variables:
    void setSimulationDuration(double iInput){  cSimulationDuration = iInput; }
    void setSimulationIterationRate(double iInput){  cSimulationIterationRate = iInput; }
    
    // Public variables (if exceptionally required):
    
    
    // Constructor:
    LocalSharedMemory();
    
    // Internal functions:
    void initializeSimulationParameters();
    void initializeModelParameters();

private:
    double cSimulationDuration;        // Simulation total duration (sec)
    double cSimulationIterationRate;   // Simulation iteration rate (sec)
};

#endif
