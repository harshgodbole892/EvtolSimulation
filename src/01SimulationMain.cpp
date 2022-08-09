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

using namespace std;
using namespace arma;


//17. Main Function
int main(int argc, char** argv) {
    
    /*
     
     This is the main disptcher file which dispatches the simulation.
     All objects of a particular class are created inside this simulation.
     
     The Local shared memory object is used as container for inter-object communication.
     
    */
    cout<<"The Evtols are now in the Metaverse!!"<<endl;
    
    // Load shared memory
    cout<<"Loading Shared Memory"<<endl;
    LocalSharedMemory wSharedMemory;
    
    //wDispatcher = SimulationDispatcher();
    //wDispatcher.addComponent()
    
    
	return 0;
}
// End of Main
