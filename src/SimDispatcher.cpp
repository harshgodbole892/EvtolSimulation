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
#include "LocalSharedMemory.hpp"
#include "SimComponent.hpp"
#include "SimDispatcher.hpp"

/*
*/
SimDispatcher::SimDispatcher(LocalSharedMemory &iLSM)
{
    cSimEndTime     = iLSM.getSimulationDuration();
    cSimTimeStep    = iLSM.getSimulationTimeStep();
    cSimStartTime   = 0.0;
    initializeSimulation();
}

/*
*/
void SimDispatcher::initializeSimulation()
{
    mCollectSize = static_cast<int> (cSimEndTime - cSimStartTime) / cSimTimeStep + 1;
    cout << "Dispatcher: Number of Iterations Estimated "<<mCollectSize<<endl;
    mSimulationTime.set_size(mCollectSize);
    mSimulationTime.zeros(mCollectSize);
}

/*
*/
void SimDispatcher::addComponent(SimComponent &iSimComponent)
{
    mSimComponents.push_back(&iSimComponent);
    cout<<"Component size :"<<mSimComponents.size()<<endl;
}

/*
*/
void SimDispatcher::dispatchSimComponents(LocalSharedMemory &iLSM)
{
    // For each component added to list, dispatch
    // components in the same order as the the addition occurs
    // by calling their update function
    
    for(int i = 0; i < mSimComponents.size(); i++)
    {
        cout << "executing "<< i<< "/" <<mSimComponents.size() << endl;
        // Check if any component is Null by accident
        if (mSimComponents[i] == NULL)
        {
            cout<< "SimComponent at index "<< i <<" is NULL"<<endl;
            continue;
        }
        else
        {
            mSimComponents[i]->update(iLSM);
        }
    }
}

/*
*/
void SimDispatcher::saveCollects(LocalSharedMemory &iLSM)
{
    mSimulationTime.save(iLSM.getGenDir() + "mSimulationTime.txt", arma::raw_ascii);
}


/*
*/
void SimDispatcher::startSimulation(LocalSharedMemory &iLSM)
{
    
    // For each time step, dispatch the entry point once
    for(long long int i=0; i<mCollectSize; i++)
    {
        // Synchronize the time step and update time variables:
        iLSM.setIterationIndex(i);
        
        // Initialize time counters
        if (i != 0)
        {
            mSimulationTime(i) = cSimTimeStep + mSimulationTime(i-1);
        } else
        {
            mSimulationTime(0) = cSimStartTime;
        }
        
        //cout<<"\r"<< " Sim Time is :"<< mSimulationTime(i)<<"/"<< cSimEndTime;
        // Dispatch component list
        dispatchSimComponents(iLSM);
        
        // Save Collects to disk:
        saveCollects(iLSM);
    }
}


