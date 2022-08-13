/*

Hierarchy     : EvtolSimulation
Model         : N/A
Class Name    : n/a
Class Type    : Common Header
 
Description   : Common header with constants and expressions for
                better code readability

*/

#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#define MIN2SEC 60.0
#define HR2MIN  60.0
#define HR2SEC  (HR2MIN * MIN2SEC)
#define SEC2HR  (1.0/HR2SEC)
#define SEC2MIN (1.0/MIN2SEC)
#define MIN2HR  (1.0/HR2MIN)

#define ITR iLSM.getIterationIndex()
#define DT  iLSM.getSimulationTimeStep()

enum VehicleState
{
    CRUISE   = 0,
    QUEUE    = 1,
    CHARGING = 2,
};

enum VehicleInitMode
{
    CRUISE_FULLBAT     = 0,
    QUEUE_EMPTYBATT    = 1,
    CHARGING_EMPTYBATT = 2,
};





#endif
