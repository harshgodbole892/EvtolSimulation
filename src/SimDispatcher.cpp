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
#include <thread>
#include "LocalSharedMemory.hpp"
#include "SimComponent.hpp"
#include "SimDispatcher.hpp"
#include "CommonDefines.hpp"

/*
 Constructor
*/
SimDispatcher::SimDispatcher(LocalSharedMemory &iLSM)
{
    cSimEndTime     = iLSM.getSimulationDuration();
    cSimTimeStep    = iLSM.getSimulationTimeStep();
    cSimStartTime   = 0.0;
    initializeSimulation();
}

/*
 Initialize the collect size for the simulation.
*/
void SimDispatcher::initializeSimulation()
{
    mCollectSize = static_cast<int> (cSimEndTime - cSimStartTime) / cSimTimeStep + 1;
    cout << "Dispatcher: Number of Iterations Estimated "<<mCollectSize<<endl;
    mSimulationTime.set_size(mCollectSize);
    mSimulationTime.zeros(mCollectSize);
}

/*
 The addComponent function is used to correctly initialize a component and save its reference
 in mSimComponents.
*/
void SimDispatcher::addComponent(SimComponent &iSimComponent)
{
    iSimComponent.setCollectSize(mCollectSize);
    mSimComponents.push_back(&iSimComponent);
}

/*
 The dispatchSimComponents dispatches one iteration of the simulation.
*/
void SimDispatcher::dispatchSimComponents(LocalSharedMemory &iLSM)
{
    // For each component added to list, dispatch
    // components in the same order as the the addition occurs
    // by calling their update function
    
    // Get number of Thread safe components:
    int wNumOfThreadSafeComponents = iLSM.getNumOfVehicles();
    vector<thread> wThreads;
    
    // Dispatch each vehicle as its own thread
    for(int i = 0; i < wNumOfThreadSafeComponents; i++)
    {
        // Check if any component is Null by accident
        if (mSimComponents[i] == NULL)
        {
            cout<< "SimComponent at index "<< i <<" is NULL"<<endl;
            continue;
        }
        else
        {
            wThreads.push_back(thread(&SimComponent::update, mSimComponents[i], ref(iLSM)));
        }
    }
    
    // Wait for vehicle threads to complete before starting the dispatch of
    // other components
    for(int i = 0; i < wNumOfThreadSafeComponents ; i++)
    {
        wThreads[i].join();
    }
    
    
    // Charging queue and the observer cannot be dispathed before all the
    // vehicle threads have executed, otherwise we may have a race condition
    // on the pop method
    for (int i = wNumOfThreadSafeComponents; i < mSimComponents.size(); i++)
    {
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
 The SaveCollects function is used to save simulation data to disk.
 This is executed at the end of the simulation.
*/
void SimDispatcher::saveCollects(LocalSharedMemory &iLSM)
{
    mSimulationTime.save(iLSM.getGenDir() + "mSimulationTime.txt", arma::raw_ascii);
    // For each component added to list, save the simulation data
    
    for(int i = 0; i < mSimComponents.size(); i++)
    {
        // Check if any component is Null by accident
        if (mSimComponents[i] == NULL)
        {
            cout<< "SimComponent at index "<< i <<" is NULL"<<endl;
            continue;
        }
        else
        {
            mSimComponents[i]->saveCollect(iLSM);
        }
    }
}


/*
 The Sim Dispatcher function dipatches all the iterations of the simulation
 and saves the data at the end of the simulation using the saveCollects
 function.
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
        
        cout<<"\r"<< " Sim Time is :"<< (mSimulationTime(i))<<" sec / "<< (cSimEndTime) << " sec";
        // cout<< " Sim Time is :"<< mSimulationTime(i)<<"/"<< cSimEndTime<<endl;
        // Dispatch component list
        dispatchSimComponents(iLSM);
        
    }
    cout<<endl;
    
    // Save Collects to disk:
    saveCollects(iLSM);
    
}


