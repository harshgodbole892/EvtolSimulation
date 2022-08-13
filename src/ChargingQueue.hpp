/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Charging Queue
Class Type    : Model
 
Description   : Generic Charging queue class, simulates a queue of vehicles
                waiting in line to be set to charging state.
 
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <armadillo>
#include <queue>

using namespace std;
#ifndef CHARGINGQUEUE_H
#define CHARGINGQUEUE_H

#include "SimComponent.hpp"

#define CHARGINGQUEUE_DEBUG 0

class LocalSharedMemory;
class Vehicle;

// ------ //
class ChargingQueue : public SimComponent
{
public:
    // setters:

    
    // getters:

    
    // Constructor:
    ChargingQueue(vector<Vehicle> &iVehicleVector, string iName, LocalSharedMemory &iLSM);
    
    // Member functions:
    void update(LocalSharedMemory &iLSM);

    
private:
    
    // Constants:
    int cMaxChargingStations{3};
    
    // Member variables:
    vector<Vehicle*> mVehicleVectorPtr;
    queue<Vehicle*> mChargingQueuePtr;
    
    // State Variables:
    
    // Collectable state variables:
    
};


#endif
