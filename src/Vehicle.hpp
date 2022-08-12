/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Vehicle
Class Type    : Model
 
Description   : Generic Vehicle class that defines a general evtol
                The memeber variables of this class are the performance parameters

*/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <armadillo>

using namespace std;
#ifndef VEHICLE_H
#define VEHICLE_H
#include "SimComponent.hpp"

class LocalSharedMemory;
// ------ //
class Vehicle : public SimComponent
{
public:
    // setters:
    void setCruiseSpeed(double iInput)      { cCruiseSpeed       = iInput;}
    void setBatteryCapacity(double iInput)  { cBatteryCapacity   = iInput;}
    void setTimeToCharge(double iInput)     { cTimeToCharge      = iInput;}
    void setEnergyUseAtCruise(double iInput){ cEnergyUseAtCruise = iInput;}
    void setPassengerCount(int    iInput)   { cPassengerCount    = iInput;}
    void setFaultProbPerHr(double iInput)   { cFaultProbPerHr    = iInput;}
    
    // getters:
    double getCruiseSpeed()      { return cCruiseSpeed      ;}
    double getBatteryCapacity()  { return cBatteryCapacity  ;}
    double getTimeToCharge()     { return cTimeToCharge     ;}
    double getEnergyUseAtCruise(){ return cEnergyUseAtCruise;}
    int    getPassengerCount()   { return cPassengerCount   ;}
    double getFaultProbPerHr()   { return cFaultProbPerHr   ;}
    
    // Constructor:
    Vehicle(string iName);
    void update(LocalSharedMemory &LSM);
    
private:
    double cCruiseSpeed;        // Cruise speed (mph)
    double cBatteryCapacity;    // Battery Capacity (kWh)
    double cTimeToCharge;       // Time to full charge (hrs)
    double cEnergyUseAtCruise;  // Energy consumption at cruise (kWh/mile)
    int    cPassengerCount;     // Passenger Count
    double cFaultProbPerHr;     // Fault probability (faults / hr)
    
    // Collectable variables:
    arma::mat sVehicleState;
    
};

#endif
