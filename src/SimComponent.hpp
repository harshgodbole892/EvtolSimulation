/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : Simulation Component
Class Type    : Simluation Support
 
 Description  : Generic simulation component class which provides a template for any
                simulation objects. All simulation objects need to derive from this class
                when used in a simulation.

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;
#ifndef SIMCOMPONENT_H
#define SIMCOMPONENT_H

class LocalSharedMemory;
// ------ //
class SimComponent
{
public:
    
    // Getters for private variables:
    string getComponentName(){ return cName; }
    
    // Setters for private variables:
    void setComponentName(string iInput){  cName = iInput; }
    
    // Constructor:
    SimComponent(string iName);
    
    // Internal functions:
    virtual void update(LocalSharedMemory &iLSM);
    virtual void collect(LocalSharedMemory &iLSM);
    virtual void saveCollect(LocalSharedMemory &iLSM);

private:
    string cName{""};
    double cTimeStep{1.0};   // Simulation iteration rate (sec)
    long long int mCollectSize{0};
};

#endif
