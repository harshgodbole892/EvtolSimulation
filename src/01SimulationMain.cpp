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
#include <stdio.h>
#include <stdlib.h>

// Project Specific includes:
#include "LocalSharedMemory.hpp"
#include "SimDispatcher.hpp"
#include "CommonDefines.hpp"
#include "SimComponent.hpp"
#include "Vehicle.hpp"
#include "ChargingQueue.hpp"

using namespace std;
using namespace arma;


//17. Main Function
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
        
    cout<<"The Evtols are now in the Metaverse!!"<<endl;
    
    // Load shared memory
    cout<<"Loading Shared Memory"<<endl;
    LocalSharedMemory wSharedMemory(wProjectHomeDir);
    
    // Create the dispatcher
    cout<<"Creating Dispatcher"<<endl;
    SimDispatcher wDispatcher(wSharedMemory);
    
    // Spawn the vehicles
    cout<<"Creating Vehicles"<<endl;
    vector<Vehicle> wVehicleVector;
    
    wVehicleVector.push_back(Vehicle("Alpha", wSharedMemory));
    wVehicleVector.push_back(Vehicle("Beta", wSharedMemory));
    wVehicleVector.push_back(Vehicle("Charlie", wSharedMemory));
    wVehicleVector.push_back(Vehicle("Delta", wSharedMemory));
    wVehicleVector.push_back(Vehicle("Echo", wSharedMemory));
    
    cout<<"Creating Charging Queue"<<endl;
    ChargingQueue wChargingQueue(wVehicleVector, "ChargingQueue", wSharedMemory);
    
    cout<<wVehicleVector.size()<<endl;
    // Spawn the Charging queue
    
    // Add references of generated sim components to the dispatcher
    cout<<"Adding Components to dispatcher"<<endl;
    for(int i=0; i< wVehicleVector.size(); i++)
        wDispatcher.addComponent(wVehicleVector[i]);
    wDispatcher.addComponent(wChargingQueue);
    
    // Start the simulation:
    cout<<"Starting Simulation"<<endl;
    wDispatcher.startSimulation(wSharedMemory);
    
	return 0;
}
// End of Main
