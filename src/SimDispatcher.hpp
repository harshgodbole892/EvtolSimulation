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
    
    // Getters for private variables:
    
    // Setters for private variables:
    
    // Constructor:
    SimDispatcher(LocalSharedMemory &iLSMmake);
    
    // Internal functions:
    void addComponent(SimComponent &iSimComponent);
    void initializeSimulation();
    void startSimulation(LocalSharedMemory &iLSM);
    void saveCollects(LocalSharedMemory &iLSM);
    void dispatchSimComponents(LocalSharedMemory &iLSM);
    
private:
    double cSimTimeStep{0.1};   // Simulation iteration rate (sec)
    double cSimStartTime{0.0};
    double cSimEndTime{0.1};
    long long int mCollectSize{0};
    //arma::vec mSimulationTime;
    arma::vec mSimulationTime = arma::zeros<arma::vec>(1000);
    vector<SimComponent*> mSimComponents;
};

#endif
