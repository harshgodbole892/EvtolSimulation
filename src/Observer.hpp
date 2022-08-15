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
    
    // setters:
    //void setVariable(int iInput){ = iInput;}
    
    // getters:
    //int getVariable() {return ;}
    
    // Constructor:
    Observer(vector<Vehicle> &iVehicleVector, int iComponentId, string iName, LocalSharedMemory &iLSM);
    
    // Member functions:
    void update(LocalSharedMemory &iLSM);
    void initializeStateSize();
    void saveCollect(LocalSharedMemory &iLSM);
    
    
private:
    
    // Constants:
    
    // Member variables:
    vector<Vehicle*> mVehicleVectorPtr;
    vector<int> mNumOfVehicleType;
    
    map<int, string> mVehicleTypeMap;
    map<string, int> mVehicleTypeRevMap;
    
    int mNumOfTypes{0};
    
    // State Variables:
    
    arma::mat sAvgTimeInFlight;
    arma::mat sAvgTimeInCharging;
    arma::mat sAvgTimeInQueue;
    arma::mat sMaxNumOfFaults;
    arma::mat sTotalPassengerMiles;
    
    // Collectable state variables:
    
};


#endif
