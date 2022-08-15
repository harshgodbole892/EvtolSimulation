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
#include "CommonDefines.hpp"


/*
 Constructor
*/
Vehicle::Vehicle(int iComponentId, string iName, LocalSharedMemory &iLSM): SimComponent(iComponentId, iName)
{
    loadParameters(iName,iLSM);
}

/*
 Simulate the vehicle specific functions at every time step
*/
void Vehicle::update(LocalSharedMemory &iLSM)
{
    // Remain initialized for 1 iteration to initialize states.
    if(ITR == 0)
    {
        initializeStateSize();
        initializeVehicle();
        return;
    }
    
    // Start State machine:
    computeCruiseState(iLSM);
    computeQueueState(iLSM);
    computeChargingState(iLSM);
    computeMaxFaultsPerHr(iLSM);
}

/*
 Initialize simulation specific components in the vehicle class
*/
void Vehicle::initializeVehicle()
{
  
    if(oVehicleInitMode == VehicleInitMode::CRUISE_FULLBAT)
    {
        sBatteryCharge(0) = cBatteryCapacity(0);
        sVehicleState(0)  = VehicleState::CRUISE;
    }
    else if(oVehicleInitMode == VehicleInitMode::DISCHARGED_EMPTYBATT)
    {
        sBatteryCharge(0) = 0.0;
        sVehicleState(0)  = VehicleState::DISCHARGED;
    }
    else if(oVehicleInitMode == VehicleInitMode::QUEUE_EMPTYBATT)
    {
        sBatteryCharge(0) = 0.0;
        sVehicleState(0)  = VehicleState::QUEUE;
    }
    else if(oVehicleInitMode == VehicleInitMode::CHARGING_EMPTYBATT)
    {
        sBatteryCharge(0) = 0.0;
        sVehicleState(0)  = VehicleState::CHARGING;
    }
    else
    {
        sBatteryCharge(0) = cBatteryCapacity(0);
        sVehicleState(0)  = VehicleState::CRUISE;
    }
}

/*
 Initialize the collects for state variables
*/
void Vehicle::initializeStateSize()
{
    // Vehicle State
    sVehicleState.set_size(getCollectSize());
    sVehicleState.zeros(getCollectSize());
    
    // Battery Charge
    sBatteryCharge.set_size(getCollectSize());
    sBatteryCharge.zeros(getCollectSize());
    
    // Time in Flight
    sTimeInFlightTotal.set_size(getCollectSize());
    sTimeInFlightTotal.zeros(getCollectSize());
    
    // Time in queue
    sTimeInQueueTotal.set_size(getCollectSize());
    sTimeInQueueTotal.zeros(getCollectSize());
    
    // Time Charging
    sTimeChargingTotal.set_size(getCollectSize());
    sTimeChargingTotal.zeros(getCollectSize());
    
    // Passenger Hours
    sTimePassengerHrs.set_size(getCollectSize());
    sTimePassengerHrs.zeros(getCollectSize());
    
    // Distance Travelled
    sDistanceTravelled.set_size(getCollectSize());
    sDistanceTravelled.zeros(getCollectSize());
    
    // Max Number of faults
    sMaxNumOfFaults.set_size(getCollectSize());
    sMaxNumOfFaults.zeros(getCollectSize());
    
}

/*
 Compute vehicle states when in cruise
*/
void Vehicle::computeCruiseState(LocalSharedMemory &iLSM)
{
    // Exit function if not in cruise state
    if (sVehicleState(ITR-1) != VehicleState::CRUISE)
    {
        sBatteryCharge(ITR)     = sBatteryCharge(ITR - 1);
        sTimeInFlightTotal(ITR) = sTimeInFlightTotal(ITR - 1);
        sTimePassengerHrs(ITR) = sTimePassengerHrs(ITR - 1);
        sDistanceTravelled(ITR) = sDistanceTravelled(ITR - 1);
        
        return;
    }
    
    double wBatteryChargeLoss = -1.0 * cEnergyUseAtCruise(0) * cCruiseSpeed(0) * (DT * SEC2HR);
    
    sBatteryCharge(ITR)     = sBatteryCharge(ITR - 1)      + wBatteryChargeLoss;
    sTimeInFlightTotal(ITR) = sTimeInFlightTotal(ITR - 1)  + (DT * SEC2HR);
    sTimePassengerHrs(ITR)  = sTimePassengerHrs(ITR - 1)   + ((DT * SEC2HR) * cPassengerCount(0));
    sDistanceTravelled(ITR) = sDistanceTravelled(ITR - 1)  + ((DT * SEC2HR) * cCruiseSpeed(0));
    
    if (sBatteryCharge(ITR) < 0.0)
    {
        sVehicleState(ITR) = VehicleState::DISCHARGED;
        return;
    }
    
    sVehicleState(ITR) =  VehicleState::CRUISE;
    //cout<<"Vehicle "<< getComponentName() <<" in Cruise"<<endl;
}

/*
 Compute vehicle states when waiting in queue
*/
void Vehicle::computeQueueState(LocalSharedMemory &iLSM)
{
    // Exit function if not in Queue state
    if (sVehicleState(ITR-1) != VehicleState::QUEUE)
    {
        sTimeInQueueTotal(ITR) = sTimeInQueueTotal(ITR - 1);
        return;
    }
    
    sTimeInQueueTotal(ITR) = sTimeInQueueTotal(ITR - 1) + (DT * SEC2HR);
    sVehicleState(ITR)     = VehicleState::QUEUE;
    
    //cout<<"Vehicle "<< getComponentName() <<" in Queue"<<endl;
}

/*
 Compute vehicle states when charging
*/
void Vehicle::computeChargingState(LocalSharedMemory &iLSM)
{
    // Exit function if not in charging state
    if (sVehicleState(ITR-1) != VehicleState::CHARGING)
    {
        sTimeChargingTotal(ITR) = sTimeChargingTotal(ITR - 1);
        return;
    }
    
    // Increment charge time for current cycle;
    mChargeTime += (DT * SEC2HR);
    
    sTimeChargingTotal(ITR) = sTimeChargingTotal(ITR - 1) + (DT * SEC2HR);
    
    if ((mChargeTime) > cTimeToCharge(0))
    {
        sBatteryCharge(ITR)     = cBatteryCapacity(0);
        sVehicleState(ITR)      = VehicleState::CRUISE;
        mChargeTime = 0;
        return;
    }
    
    sVehicleState(ITR) = VehicleState::CHARGING;
    //cout<<"Vehicle "<< getComponentName() <<" in Charging"<<endl;
}

/*
 The function generates max faults per hr with a given fault probability.
 The maximum resolution of the fault probability is attempting by using the
 entire scale of RAND_MAX when computing the probability.
*/

void Vehicle::computeMaxFaultsPerHr(LocalSharedMemory &iLSM)
{
    long long t1 = 0;
    
    // Random Seed for initialization;
    // If unique seed option is used, new seed is not generated at runtime.
    // this is useful for debugging purposes
    if(iLSM.getOptUniqueSeedForRand() != 1)
    {
        // Use High resolution clock to ensure that the seed is changed
        // at every iteration of the for loop.
        t1 = chrono::high_resolution_clock::now().time_since_epoch().count();
        srand(static_cast<unsigned int>(t1));
    }

    // Since rand() returns a number between (0,RAND_MAX), the chance that
    // to get the maximum resolution, we multiply iFaultProbability with RAND_MAX
    // eg. if rand() % 100 < 75 has 75% probability of being true. Since
    // rand() % RAND_MAX = rand(), the funciton follows.
    
    double wFaultProbability = cFaultProbPerHr(0) * SEC2HR * DT;
    
    if((wFaultProbability * RAND_MAX) < 1.0 && ITR == 1)
    {
        cout<<"Fault probab issue, Increase time step, probability of simulating faults is too low"<< endl;
    }
    //cout<<"rand is "<<rand()<<" Fault probab is "<<(int)(wFaultProbability * RAND_MAX)<<endl;
    //cout<<"Truth value is "<< (rand() < (wFaultProbability * RAND_MAX))<<endl;
    //cout<<"rand max is " << RAND_MAX<<endl;
    
    bool wFaultOccured = (rand()) < (wFaultProbability * RAND_MAX);
    
    if (wFaultOccured != 0)
    {
        sMaxNumOfFaults[ITR] = sMaxNumOfFaults[ITR-1] + 1;
        cout<<endl<<"Fault Occured on "<<getComponentName()<<endl;
    }
    else
    {
        sMaxNumOfFaults[ITR] = sMaxNumOfFaults[ITR-1];
    }
}

/*
 Initialize Vehicle parameters based on vehicle name
*/
void Vehicle::loadParameters(string iName, LocalSharedMemory &iLSM)
{
    bool wLoaderSuccessful = 1;
    bool wTemp = 0;
    
    if(VEHICLE_DEBUG) cout<<"Loading: "<<getComponentName()<<endl;
    /*
     The constructor initializes the parameters of the vehicle class at load time from disk.
     The VEHICLE_DEBUG flag is used to verify the values of the loaded constants when debugging.
     */
    
    // Cruise speed (mph)
    wTemp = cCruiseSpeed.load(iLSM.getParametersDir() + getComponentName() + "_cCruiseSpeed.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG) cout<<"cCruiseSpeed: "<<cCruiseSpeed(0)<<", ";
    
    // Battery Capacity (kWh)
    wTemp = cBatteryCapacity.load(iLSM.getParametersDir() + getComponentName() + "_cBatteryCapacity.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG) cout<<"cBatteryCapacity: "<<cBatteryCapacity(0)<<", ";
    
    // Time to full charge (hrs)
    wTemp = cTimeToCharge.load(iLSM.getParametersDir() + getComponentName() + "_cTimeToCharge.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG) cout<<"cTimeToCharge: "<<cTimeToCharge(0)<<", ";
    
    // Energy consumption at cruise (kWh/mile)
    wTemp = cEnergyUseAtCruise.load(iLSM.getParametersDir() + getComponentName() + "_cEnergyUseAtCruise.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG) cout<<"cEnergyUseAtCruise: "<<cEnergyUseAtCruise(0)<<", ";
    
    // Passenger Count
    wTemp = cPassengerCount.load(iLSM.getParametersDir() + getComponentName() + "_cPassengerCount.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG) cout<<"cPassengerCount: "<<cPassengerCount(0)<<", ";
    
    // Fault probability (faults / hr)
    wTemp = cFaultProbPerHr.load(iLSM.getParametersDir() + getComponentName() + "_cFaultProbPerHr.txt" , arma::csv_ascii);
    wLoaderSuccessful = wLoaderSuccessful & wTemp;
    if(VEHICLE_DEBUG)
    {
        cout<<"cFaultProbPerHr: "<<cFaultProbPerHr(0)<<", ";
        cout<<endl;
    }
    
    if(wLoaderSuccessful == 0)
    {
        cout<<"Loading Vehicle " + getComponentName() + " Failed. Check Parameters Directory"<<endl;
    }
}

/*
 Change vehicle state for curret time step based on external input
*/
void Vehicle::setVehicleState(int iState, LocalSharedMemory &iLSM)
{
    sVehicleState(ITR) = static_cast<double>(iState);
}

/*
 Get vechicle state for current time step
*/

int Vehicle::getVehicleState(LocalSharedMemory &iLSM)
{
    return static_cast<int>(sVehicleState(ITR));
}

/*
 Save collected state variables to disk
*/

void Vehicle::saveCollect(LocalSharedMemory &iLSM)
{
    string wPrintName = to_string(getComponentId()) + "_" + getComponentName();
    
    sVehicleState.save(iLSM.getGenDir()      + wPrintName +  "_sVehicleState.txt",      arma::raw_ascii);
    sBatteryCharge.save(iLSM.getGenDir()     + wPrintName +  "_sBatteryCharge.txt",     arma::raw_ascii);
    sTimeInFlightTotal.save(iLSM.getGenDir() + wPrintName +  "_sTimeInFlightTotal.txt", arma::raw_ascii);
    sTimeInQueueTotal.save(iLSM.getGenDir()  + wPrintName +  "_sTimeInQueueTotal.txt",  arma::raw_ascii);
    sTimeChargingTotal.save(iLSM.getGenDir() + wPrintName +  "_sTimeChargingTotal.txt", arma::raw_ascii);
    sTimePassengerHrs.save(iLSM.getGenDir()  + wPrintName +  "_sTimePassengerHrs.txt",  arma::raw_ascii);
    sDistanceTravelled.save(iLSM.getGenDir() + wPrintName +  "_sDistanceTravelled.txt", arma::raw_ascii);
    sMaxNumOfFaults.save(iLSM.getGenDir()    + wPrintName +  "_sMaxNumOfFaults.txt",    arma::raw_ascii);
}

// Getters based of iterators
double Vehicle::getTimeInFlightTotal(LocalSharedMemory &iLSM) { return  sTimeInFlightTotal(ITR); }
double Vehicle::getTimeInQueueTotal(LocalSharedMemory &iLSM)  { return  sTimeInQueueTotal(ITR); }
double Vehicle::getTimeChargingTotal(LocalSharedMemory &iLSM) { return  sTimeChargingTotal(ITR); }
double Vehicle::getTimePassengerHrs(LocalSharedMemory &iLSM)  { return  sTimePassengerHrs(ITR); }
double Vehicle::getDistanceTravelled(LocalSharedMemory &iLSM) { return  sDistanceTravelled(ITR); }
double Vehicle::getMaxNumOfFaults(LocalSharedMemory &iLSM)    { return  sMaxNumOfFaults(ITR); }

