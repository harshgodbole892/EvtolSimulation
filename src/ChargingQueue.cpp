/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Charging Queue
Class Type    : Model
 
Description   : Generic Charging queue class, simulates a queue of vehicles
                waiting in line to be set to charging state.
*/

// Imports
#include "ChargingQueue.hpp"
#include "SimComponent.hpp"
#include "LocalSharedMemory.hpp"
#include "CommonDefines.hpp"


ChargingQueue::ChargingQueue(string iName, LocalSharedMemory &iLSM): SimComponent(iName)
{
}
/*
 Initialize Global Simulation parameters
*/
void ChargingQueue::update(LocalSharedMemory &iLSM)
{
    // Remain initialized for 1 iteration to initialize states.
    if(ITR == 0) return;
    
}
