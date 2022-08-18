/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Simulation Dispatcher
Class Type    : Simulation Support
 
Description   : Generically dispatches objects defined in the simulation.
 
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <armadillo>

using namespace std;
#ifndef SIMDISPATCHER_H
#define SIMDISPATCHER_H
#include "SimComponent.hpp"

class SimComponent;
class LocalSharedMemory;

// ------ //
class SimDispatcher
{
public:
    
    // Constructor:
    SimDispatcher(LocalSharedMemory &iLSMmake);
    
    // Internal functions:
    void addComponent(SimComponent &iSimComponent);
    void initializeSimulation();
    void startSimulation(LocalSharedMemory &iLSM);
    void saveCollects(LocalSharedMemory &iLSM);
    void dispatchSimComponents(LocalSharedMemory &iLSM);
    
private:
    
    // Member variables:
    double cSimTimeStep{0.1};   // Simulation iteration rate (sec)
    double cSimStartTime{0.0};
    double cSimEndTime{0.1};
    long long int mCollectSize{0};
    
    int oRealTimeExecution{1};    // Real time execution option: 1 - Real time
                                  // 2 - Faster than real time
    
    // Member objects:
    arma::vec mSimulationTime = arma::zeros<arma::vec>(1);
    vector<SimComponent*> mSimComponents;
};

#endif
