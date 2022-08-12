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
#include "SimComponent.hpp"
#include "Vehicle.hpp"
#include "SimDispatcher.hpp"

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
    
    cout<<"Creating Components"<<endl;
    SimComponent wSimComponent("TestSimComponent");
    Vehicle wV1("TestVehicle1");
    Vehicle wV2("TestVehicle2");
    
    cout<<"Creating Dispatcher"<<endl;
    SimDispatcher wDispatcher(wSharedMemory);
    
    cout<<"Adding Components to dispatcher"<<endl;
    wDispatcher.addComponent(wSimComponent);
    wDispatcher.addComponent(wV1);
    wDispatcher.addComponent(wV2);
    
    cout<<"Starting Simulation"<<endl;
    wDispatcher.startSimulation(wSharedMemory);
    
    
	return 0;
}
// End of Main
