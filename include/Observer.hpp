/*

 Hierarchy     : EvtolSimulation
 Model         : N/A
 Class Name    : Observer
 Class Type    : Model
  
 Description   : Generic class implemented to observe metrics across
                 vehicle types
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <armadillo>
#include <queue>

using namespace std;
#ifndef OBSERVER_H
#define OBSERVER_H

#include "SimComponent.hpp"

#define CHARGINGQUEUE_DEBUG 0

class LocalSharedMemory;
class Vehicle;

// ------ //
class Observer : public SimComponent
{
public:
    
    // Constructor:
    Observer(vector<Vehicle> &iVehicleVector, int iComponentId, string iName, LocalSharedMemory &iLSM);
    
    // Member functions:
    void update(LocalSharedMemory &iLSM);
    void initializeStateSize();
    void saveCollect(LocalSharedMemory &iLSM);
    
    
private:
    
    // Constants:
    
    // Member variables:
    vector<Vehicle*> mVehicleVectorPtr;    // Pointer to spawned vehicle vector
    vector<int> mNumOfVehicleType;         // Total num of vehicles spawned for a given type
    
    map<int, string> mVehicleTypeMap;      // From vehicle type id to string
    map<string, int> mVehicleTypeRevMap;   // From string to vehicle type id
    
    int mNumOfTypes{0};
    
    // State Variables:
    
    arma::mat sAvgTimeInFlight;       // Avg time in flight per vehicle type (hrs)
    arma::mat sAvgTimeInCharging;     // Avg time charging per vehicle type (hrs)
    arma::mat sAvgTimeInQueue;        // Avg time in queue per vehicle type (hrs)
    arma::mat sMaxNumOfFaults;        // Max number of total faults per vehicle type
    arma::mat sTotalPassengerMiles;   // Total passenger miles per vehicle type (passenger-miles)
    arma::mat sVehicleCount;          // Number of vehicles of a given vehicle type
    
    // Collectable state variables:
    
};


#endif
