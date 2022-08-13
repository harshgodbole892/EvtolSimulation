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
#include "CommonDefines.hpp"

#define VEHICLE_DEBUG 0

class LocalSharedMemory;
// ------ //
class Vehicle : public SimComponent
{
public:
    
    // setters:
    void setCruiseSpeed(double iInput)      { cCruiseSpeed(0)       = iInput;}
    void setBatteryCapacity(double iInput)  { cBatteryCapacity(0)   = iInput;}
    void setTimeToCharge(double iInput)     { cTimeToCharge(0)      = iInput;}
    void setEnergyUseAtCruise(double iInput){ cEnergyUseAtCruise(0) = iInput;}
    void setPassengerCount(int    iInput)   { cPassengerCount(0)    = static_cast<double>(iInput);}
    void setFaultProbPerHr(double iInput)   { cFaultProbPerHr(0)    = iInput;}
    void setVehicleState(int iState, LocalSharedMemory &LSM);
    
    // getters:
    double getCruiseSpeed()      { return cCruiseSpeed(0)      ;}
    double getBatteryCapacity()  { return cBatteryCapacity(0)  ;}
    double getTimeToCharge()     { return cTimeToCharge(0)     ;}
    double getEnergyUseAtCruise(){ return cEnergyUseAtCruise(0);}
    double getPassengerCount()   { return cPassengerCount(0)   ;}
    double getFaultProbPerHr()   { return cFaultProbPerHr(0)   ;}
    int    getVehicleState(LocalSharedMemory &LSM);
    
    // Constructor:
    Vehicle(string iName, LocalSharedMemory &LSM);
    
    // Member functions:
    void initializeStateSize();
    void initializeVehicle();
    void loadParameters(string iName, LocalSharedMemory &iLSM);
    void update(LocalSharedMemory &LSM);
    void computeCruiseState(LocalSharedMemory &LSM);
    void computeQueueState(LocalSharedMemory &LSM);
    void computeChargingState(LocalSharedMemory &LSM);
    void saveCollect(LocalSharedMemory &LSM);
    
private:
    
    /*
     Vehicle Parameters:
     
     These need not be Vectors but since we have the api for easy
     disk IO available, I will treat them as vectors. It allows
     the parameters to be changed at load time so that the program
     does not have to be recompiled if they change. It also allows
     quick modular parameterization when creating the objects of the
     class.
    */
    
    // Cruise speed (mph)
    arma::vec cCruiseSpeed = arma::zeros<arma::vec>(1);
    // Battery Capacity (kWh)
    arma::vec cBatteryCapacity = arma::zeros<arma::vec>(1);
    // Time to full charge (hrs)
    arma::vec cTimeToCharge = arma::zeros<arma::vec>(1);
    // Energy consumption at cruise (kWh/mile)
    arma::vec cEnergyUseAtCruise = arma::zeros<arma::vec>(1);
    // Passenger Count
    arma::vec cPassengerCount = arma::zeros<arma::vec>(1);
    // Fault probability (faults / hr)
    arma::vec cFaultProbPerHr = arma::zeros<arma::vec>(1);
    
    // State Variables:
    double mChargeTime{0.0};
    
    // Collectable state variables:
    arma::vec sVehicleState;       // Vehicle State: 0 - in flight
                                   // 1 - in queue for charging
                                   // 2 - charging
    
    arma::vec sBatteryCharge;      // (kWh)
    arma::vec sTimeInFlightTotal;  // (sec)
    arma::vec sTimeInQueueTotal;   // (sec)
    arma::vec sTimeChargingTotal;  // (sec)
    arma::vec sTimePassengerHrs;   // (sec)
    arma::vec sDistanceTravelled;  // (sec)
    arma::vec sMaxNumOfFaults;     // (sec)
    
    // Build Options:
    int oVehicleInitMode{VehicleInitMode::CHARGING_EMPTYBATT};
                                   // Enum Vehicle Init Mode,
                                   // 0 - fully Charged
                                   // 1 - discharged in queue
                                   // 2 - discharged in charging state
    
};


#endif
