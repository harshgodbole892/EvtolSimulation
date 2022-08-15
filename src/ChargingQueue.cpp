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
#include "Vehicle.hpp"
#include "LocalSharedMemory.hpp"
#include "CommonDefines.hpp"


/*
 Constructor
*/
ChargingQueue::ChargingQueue(vector<Vehicle> &iVehicleVector, int iComponentId, string iName, LocalSharedMemory &iLSM): SimComponent(iComponentId, iName)
{
    // Set Max charging stations:
    
    cMaxChargingStations = iLSM.getMaxChargingStations();
    
    for(int i = 0; i<iVehicleVector.size(); i++)
    {
        mVehicleVectorPtr.push_back(&iVehicleVector[i]);
    }
}

/*
 Initialize Global Simulation parameters
*/
void ChargingQueue::update(LocalSharedMemory &iLSM)
{
    // Remain initialized for 1 iteration to initialize states.
    
    int wVehiclesInCharging = 0;
    
    // Check how many vehicles are in charging state:
    for(int i=0 ; i < mVehicleVectorPtr.size(); i++)
    {
        // If charging, increment counter for charging
        if(mVehicleVectorPtr[i]->getVehicleState(iLSM) == VehicleState::CHARGING)
        {
            wVehiclesInCharging = wVehiclesInCharging + 1;
        }
        // If vehicle is discharged, add it to the queue
        else if(mVehicleVectorPtr[i]->getVehicleState(iLSM) == VehicleState::DISCHARGED)
        {
            mChargingQueuePtr.push(mVehicleVectorPtr[i]);
            mVehicleVectorPtr[i]->setVehicleState(VehicleState::QUEUE, iLSM);
        }
    }
    
    // If any chargers are free, add the elements from the queue into charging state
    while (wVehiclesInCharging < cMaxChargingStations)
    {
        if(mChargingQueuePtr.size()!= 0)
        {
            mChargingQueuePtr.front()->setVehicleState(VehicleState::CHARGING, iLSM);
            mChargingQueuePtr.pop();
        }
        wVehiclesInCharging++;
    }
}

