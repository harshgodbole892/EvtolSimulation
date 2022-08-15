/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : SimComponent
Class Type    : Simluation Support
 
Description   : Generic simulation component class which provides a template for any
                simulation object. All simulation objects need to derive from this class
                when used in a simulation, so that the dispactcher is able to dispatch
                these components generically.
*/

// Imports
#include "SimComponent.hpp"
#include "LocalSharedMemory.hpp"

/*
 Constructor
*/
SimComponent::SimComponent(int iComponentId, string iComponentName)
{
    cComponentName = iComponentName;
    cComponentId   = iComponentId;
}

/*
*/
void SimComponent::update(LocalSharedMemory &iLSM)
{
    //cout<<"This is SimComponent Class, Timestep : "<<cTimeStep<<endl;
    //cout<<"From local shared memory - Simulation duration is "<<iLSM.getSimulationDuration()<<endl;
}

/*
  Collect function, used to save any simulation variables
*/
void SimComponent::saveCollect(LocalSharedMemory &iLSM)
{
    return;
}


