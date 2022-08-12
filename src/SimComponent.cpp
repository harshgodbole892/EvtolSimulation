/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : SimComponent
Class Type    : Simluation Support
 
Description   : Generic simulation component class which provides a template for any
                simulation objects. All simulation objects need to derive from this class
                when used in a simulation.
*/

// Imports
#include "SimComponent.hpp"
#include "LocalSharedMemory.hpp"

/*
*/
SimComponent::SimComponent(string iName)
{
    cName = iName;
    cTimeStep = 0.1;
}

/*
*/
void SimComponent::update(LocalSharedMemory &iLSM)
{
    cout<<"This is SimComponent Class, Timestep : "<<cTimeStep<<endl;
    //cout<<"From local shared memory - Simulation duration is "<<iLSM.getSimulationDuration()<<endl;
}

/*
*/
void SimComponent::collect(LocalSharedMemory &iLSM)
{
    return;
}

/*
*/
void SimComponent::saveCollect(LocalSharedMemory &iLSM)
{
    return;
}


