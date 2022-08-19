/*
 
 Hierarchy     : EvtolSimulation
 Model         : N/A
 Function Name : main
 Function Type : Dynamic Dispatcher
 */

//Tempelate by Harsh Godbole.

// Generic includes:
#include <iostream>
#include <armadillo>
#include <vector>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


// Project Specific includes:
#include "LocalSharedMemory.hpp"
#include "SimDispatcher.hpp"
#include "CommonDefines.hpp"
#include "SimComponent.hpp"
#include "Vehicle.hpp"
#include "ChargingQueue.hpp"
#include "Observer.hpp"

using namespace std;

#define SIMULATIONMAIN_DEBUG 0

// Randomly generate vector of 20 vehicles, one of each type
vector<Vehicle> createVehicleVector(LocalSharedMemory &iLSM)
{
    // Return vector
    vector<Vehicle>  wVehicleVector;
    
    // Working Variables:
    map<int, string> wVehicleTypeMap = iLSM.getVehicleTypeMap();
    
    string wRandVehicleType = "";
    
    int wNumOfVehicles = iLSM.getNumOfVehicles();
    int wRandInt = 0;
    int wNumOfTypes    = wVehicleTypeMap.size();
    
    long long t1 = 0;
    
    // Check if number of types are greater than number of vehicles,
    // If Yes, notify user that NumOfTypes is used as vehicles.
    
    if (wNumOfTypes > wNumOfVehicles )
    {
        cout<<"Creating "<<wNumOfTypes<<" Vehicles as it is greater than requested number of vehicles "<<wNumOfVehicles<<endl;
    }
    
    cout<<"Creating "<<wNumOfVehicles<<" Vehicles"<<endl;
    
    // Make 1 vehicle of each type
    for(int i = 1; i < (wNumOfTypes +1); i++)
    {
        wVehicleVector.push_back(Vehicle(i, wVehicleTypeMap.find(i)->second, iLSM));
        
        if (SIMULATIONMAIN_DEBUG)
        {
            cout<<"Making vehicle "<<i<<", Type "<<wVehicleTypeMap.find(i)->second<<endl;
        }
    }
    
    // Make rest of the vehicles randomly
    for(int i=(wNumOfTypes + 1); i < (wNumOfVehicles + 1) ; i++)
    {
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
        
        // Random int between 1 and NumOfTypes
        wRandInt = rand() % wNumOfTypes + 1;
        wRandVehicleType = wVehicleTypeMap.find(wRandInt)->second;
        
        if (SIMULATIONMAIN_DEBUG)
        {
            cout<<"Making vehicle "<<i<<", Type "<<wRandVehicleType<<endl;
        }
        
        wVehicleVector.push_back(Vehicle(i, wRandVehicleType, iLSM));
    }
    
    return wVehicleVector;
}

// Main Function
int main(int argc, char** argv) {
    
    /*
     
     This is the main disptcher file which dispatches the simulation.
     All objects of a particular class are created inside this simulation.
     
     The Local shared memory object is used as container for inter-object communication.
     
    */
    
    string wProjectHomeDir;
    
    // Check that getenv has not returned a NULL pointer:
    const char *wProjectHomeDirPtr = getenv("PROJECT_HOME_DIR");
    if (!wProjectHomeDirPtr)
    {
         wProjectHomeDir.assign("//");
         cout<<"Env Variable PROJECT_HOME_DIR is not set, Use RunFile to execute code"<<endl;
         return 1;
    }
    
    wProjectHomeDir.assign(wProjectHomeDirPtr);
    
    cout<<" **** **** ******* **** **** ******  ** *"<<endl;
    cout<<" ********  *****     **** *   ****   *** ****"<<endl;
    cout<<" The Evtols are now in the cloud(s)!!"<<endl;
    cout<<" **** **** ******* **** **** ******  ** *"<<endl;
    cout<<" ********  *****     **** *   ****   *** ****"<<endl<<endl;
    
    // Load shared memory
    cout<<"Loading Shared Memory"<<endl;
    LocalSharedMemory wSharedMemory(wProjectHomeDir);
    
    // Create the dispatcher
    cout<<"Creating Dispatcher"<<endl;
    SimDispatcher wDispatcher(wSharedMemory);
    
    // Spawn the vehicles
    cout<<"Creating Vehicles"<<endl;
    
    vector<Vehicle> wVehicleVector = createVehicleVector(wSharedMemory);
    
    int wChargingQueueId = (wSharedMemory.getNumOfVehicles() + 1);
    
    cout<<"Creating Charging Queue with ID "<<wChargingQueueId <<endl;
    ChargingQueue wChargingQueue(wVehicleVector,
                                 wChargingQueueId,
                                 "ChargingQueue",
                                 wSharedMemory);
    
    cout<<"Max Charging Stations set to "<<wChargingQueue.getMaxChargingStations()<<endl;
    
    int wObserverId = (wSharedMemory.getNumOfVehicles() + 2);
    
    cout<<"Creating the observer station with ID "<< wObserverId <<endl;
    Observer wObserver(wVehicleVector,
                       wObserverId,
                       "Observer",
                       wSharedMemory);
    
    // Spawn the Charging queue
    
    // Add references of generated sim components to the dispatcher
    cout<<"Adding Components to dispatcher"<<endl;
    for(int i=0; i< wVehicleVector.size(); i++)
        wDispatcher.addComponent(wVehicleVector[i]);
    wDispatcher.addComponent(wChargingQueue);
    wDispatcher.addComponent(wObserver);
    
    // Start the simulation:
    cout<<"Starting Simulation"<<endl;
    wDispatcher.startSimulation(wSharedMemory);
    
	return 0;
}
// End of Main
