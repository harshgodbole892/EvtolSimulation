/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Vehicle
Class Type    : Model
 
Description   : Generic Vehicle class that defines a general evtol
                The memeber variables of this class are the performance parameters

*/

// Imports
#include "Vehicle.hpp"
#include "SimComponent.hpp"
#include "LocalSharedMemory.hpp"

Vehicle::Vehicle(string iName): SimComponent(iName)
{
    setCruiseSpeed(0.0);        // Cruise speed (mph)
    setBatteryCapacity(0.0);    // Battery Capacity (kWh)
    setTimeToCharge(0.0);       // Time to full charge (hrs)
    setEnergyUseAtCruise(0.0);  // Energy consumption at cruise (kWh/mile)
    setPassengerCount(0);       // Passenger Count
    setFaultProbPerHr(0.0);     // Fault probability (faults / hr)
}

/*
 Initialize Global Simulation parameters
*/
void Vehicle::update(LocalSharedMemory &LSM)
{
    cout<<"This is Vehicle Class, Name : "<<getComponentName()<<endl;
    //cout<<"From local shared memory - Simulation duration is "<<LSM.getSimulationDuration()<<endl;
}

