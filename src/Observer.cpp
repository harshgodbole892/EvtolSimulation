/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Observer
Class Type    : Model
 
Description   : Generic class implemented to observe metrics across
                vehicle types
*/

// Imports
#include "Observer.hpp"
#include "SimComponent.hpp"
#include "Vehicle.hpp"
#include "LocalSharedMemory.hpp"
#include "CommonDefines.hpp"


/*
 Constructor
*/
Observer::Observer(vector<Vehicle> &iVehicleVector, int iComponentId, string iName, LocalSharedMemory &iLSM): SimComponent(iComponentId, iName)
{
    mVehicleTypeMap    = iLSM.getVehicleTypeMap();
    mVehicleTypeRevMap = iLSM.getVehicleTypeRevMap();
    mNumOfTypes        = mVehicleTypeMap.size();
    
    // Initialize the number of vehicle type array
    mNumOfVehicleType.resize(mNumOfTypes);
    std::fill(mNumOfVehicleType.begin(), mNumOfVehicleType.end(), 0);
    
    int wVehicleTypeInt = 0;
    
    // Iterate through the vectors:
    for(int i = 0; i < iVehicleVector.size(); i++)
    {
        // Get vehicle type:
        wVehicleTypeInt = mVehicleTypeRevMap.find(iVehicleVector[i].getComponentName())->second;
        wVehicleTypeInt = wVehicleTypeInt - 1 ;
        
        // Get vehicle type int:
        mNumOfVehicleType[wVehicleTypeInt]++;
        
        // Add to the vector class
        mVehicleVectorPtr.push_back(&iVehicleVector[i]);
    }
    
}

/*
    Initialize size of all collected variables:
*/

void Observer::initializeStateSize()
{
    // Average time in flight
    sAvgTimeInFlight.set_size(getCollectSize(), mNumOfTypes);
    sAvgTimeInFlight.zeros(getCollectSize(), mNumOfTypes);
    
    // Average time charging
    sAvgTimeInCharging.set_size(getCollectSize(), mNumOfTypes);
    sAvgTimeInCharging.zeros(getCollectSize(), mNumOfTypes);
    
    // Average time in queue
    sAvgTimeInQueue.set_size(getCollectSize(), mNumOfTypes);
    sAvgTimeInQueue.zeros(getCollectSize(), mNumOfTypes);
    
    // Average Number of Faults
    sMaxNumOfFaults.set_size(getCollectSize(), mNumOfTypes);
    sMaxNumOfFaults.zeros(getCollectSize(), mNumOfTypes);
    
    // Average Passenger Miles
    sTotalPassengerMiles.set_size(getCollectSize(), mNumOfTypes);
    sTotalPassengerMiles.zeros(getCollectSize(), mNumOfTypes);
        
}

/*
 Defines metrics to observe across vehicles
*/
void Observer::update(LocalSharedMemory &iLSM)
{
    if(ITR == 0)
    {
        initializeStateSize();
        return;
    }
    
    int wVehicleTypeInt = 0;
    
    // Average time in flight
    for(int i = 0; i < mVehicleVectorPtr.size(); i++)
    {
        // Get vehicle type int and decrement by 1 for c style array indexing
        wVehicleTypeInt = mVehicleTypeRevMap.find(mVehicleVectorPtr[i]->getComponentName())->second;
        wVehicleTypeInt = wVehicleTypeInt - 1;
        
        if(ITR==1)
        {
            //cout<<"Vehicle count "<<mVehicleVectorPtr[i]->getComponentName()<<" is "<<mNumOfVehicleType[wVehicleTypeInt]<<endl;
        }
        
        // Break if any type has no vehicles spawned
        if(mNumOfVehicleType[wVehicleTypeInt] == 0)
        {
            cout<<"No Vehicles of type wVehicleTypeInt are spawned for "<<mVehicleVectorPtr[i]->getComponentName();
            continue;
        }

        // Compute metrics
        sAvgTimeInFlight(ITR, wVehicleTypeInt)     += mVehicleVectorPtr[i]->getTimeInFlightTotal(iLSM)  / mNumOfVehicleType[wVehicleTypeInt];
        sAvgTimeInCharging(ITR, wVehicleTypeInt)   += mVehicleVectorPtr[i]->getTimeChargingTotal(iLSM)  / mNumOfVehicleType[wVehicleTypeInt];
        sAvgTimeInQueue(ITR, wVehicleTypeInt)      += mVehicleVectorPtr[i]->getTimeInQueueTotal(iLSM)   / mNumOfVehicleType[wVehicleTypeInt];
        sTotalPassengerMiles(ITR, wVehicleTypeInt) += mVehicleVectorPtr[i]->getTimePassengerHrs(iLSM);
        sMaxNumOfFaults(ITR, wVehicleTypeInt)      += mVehicleVectorPtr[i]->getMaxNumOfFaults(iLSM);
    }
}

/*
 Defines metrics to observe across vehicles
*/

void Observer::saveCollect(LocalSharedMemory &iLSM)
{
    string wPrintName = to_string(getComponentId()) + "_" + getComponentName();
    
    sAvgTimeInFlight.save(iLSM.getGenDir()      + wPrintName +  "_sAvgTimeInFlight.txt",     arma::csv_ascii);
    sAvgTimeInCharging.save(iLSM.getGenDir()    + wPrintName +  "_sAvgTimeInCharging.txt",   arma::csv_ascii);
    sAvgTimeInQueue.save(iLSM.getGenDir()       + wPrintName +  "_sAvgTimeInQueue.txt",      arma::csv_ascii);
    sTotalPassengerMiles.save(iLSM.getGenDir()  + wPrintName +  "_sTotalPassengerMiles.txt", arma::csv_ascii);
    sMaxNumOfFaults.save(iLSM.getGenDir()       + wPrintName +  "_sMaxNumOfFaults.txt",      arma::csv_ascii);
}

