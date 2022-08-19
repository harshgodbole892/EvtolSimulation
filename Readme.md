# Welcome to the Evtol Simulation! 
This repo contains a hypothetical simulation of a fleet of Evtol aircraft with limited battery capacity. The simulation spawns 20 Evtols in the cloud(s), that fight for dominance over 3 charging stations. Their objective? Accumulate the maximum number of passengers-miles possible. To clarify this metric, 1 passenger mile is equal to 1 passenger travelling 1 mile.
Kudos to the engineers at *Undisclosed Evtol Manufacturer* for this problem statement! 

## Project installation
This project requires the following external libraries to work. 
- Armadillo : https://gitlab.com/conradsnicta/armadillo-code
- GoogleTest: https://github.com/google/googletest
- CMake : https://cmake.org

Please clone the git repos and follow the installation directions in the readme of the repositories for standard installation.


## Building the solution

CMake is used to configure the cross platform build. 
- Clone this repository and open a terminal at its root folder that includes the CMakeLists.txt file.
- Open the CMakeLists.txt and modify the following line to ensure that armadillo libs and include directories are correctly set. 
- Also set the project home directory to be at the clone location of this repository like the following example:
```
set(ARMADILLO_INCLUDE_DIR /Users/username/Documents/Github/armadillo-code/include)
set(ARMADILLO_LIBRARIES /Users/username/Documents/Github/armadillo-code)
set(PROJECT_HOME_DIR "/Users/username/Documents/Github/EvtolSimulation" Global)
```

- Next, use the following commands to build.
```
cmake -S . -B build
cmake --build build
```

- Once built successfully, to run the exe and unit tests. The correct environment variable needs to be present and the generated directory needs to be created or cleaned before execution. Use RunEvtolSimulaiton.sh and RunEvtolSimulationTests.sh to execute this operation. (For linux, this script may need to be modified slightly.)
```
./RunEvtolSimulation.sh
./RunEvtolSimulationTests.sh
```

- Finally, once the tests pass and the simulation is run, you can use python to run AnalyzeData.py to generate results in the results folder. Results of a randomized simulation are already provided in an html format, but are overwritten with every run of AnalyzeData.py

## Solution Structure
The two main types of classes included in the solution are **Simulation Support** and **Model**. 

1. Classes under the simulation support type are used to deploy the basic functions of the simulation. They include:
    - **Local Shared Memory:** This class manages the global simulation parameters like time step, iteration index, and options for seeding random initializations. It also sets global model specific parameters like number of vehicles and charging stations.
    - **Sim Dispatcher:** This class manages running the loops for dispatching each time step.
    - **Sim Component:** This class provides a base class (template) for each model class. This enables a very generic approach towards dispatching a simulation.
2. Classes under the model type are used to simulate the individual components of the simulation. All the classes of the model type are derived from SimComponent class. With our problem definition, we have following classes:
    - **Vehicle Class**: It defines a vehicle which can be initialized with certain parameters. It can fly and charge based on the simulation conditions. It collects the data associated with the vehicle and writes to the generated folder at the end of the simulation.
    - **Charging Queue:** An object of this class manages the process of setting objects of the vehicle class in the appropriate states according to the simulation conditions and simulates an collection of charging stations. It monitors the number of vehicles charging across the simulation and writes the data to disk.
    - **Observer:** This component is used to monitor the different global metrics of the solution, like total number of passenger-hrs per vehicle type, or the average time spent in cruise. It also writes the collected data to disk.
3. The SimulationMain function is used for the assembly of the simulation and random initialization of the vehicles. 
4. The CommonDefines file defines enums and preprocessor definitions that improve code readability.

![Simulation Flow Diagram](/docs/DataFlowDiagram.svg)

## Class Descriptions: 

### General naming convention for functions and variable:
- functionName : camelCase convention 
- wVariable : Working Variable, local to function.
- mVariable : Member variable.
- oVariable : Simulation Option.
- sVariable : State variable for collects, parametrized by arma::vec or arma::mat.
 
### Local Shared Memory: 
An object of this class is used to pass data to different objects. If sufficient guarded by a mutex, it also provides an ability to act as writable shared memory. The following parameters are defined in an object of the class to be used across the solution:
- initializeSimulationParameters: Sets
    - Simulation Duration
    - Simulation Time step
- initializeModelParameters: Sets
    - Vehicle Type Names    
    - Number of vehicles 
    - Number of charging stations
- setIterationIndex: The iteration index variable keeps a track of the simulation time using an int index. The index is incremented once a simulation time step has completed. This is the only variable the this class which can be written to by 2 different threads at the same time, and hence is guarded by a mutex. However, this safety is redundant as this condition will never occur as per the current implementation of the solution.

### Sim Dispatcher: 
An object of the sim dispatcher type dispatches all the SimComponents in the solution. At the setup stage of the simulation, each sim component is added to the simulation using addComponent function and the simulation is dispatched using startSimulation function.
- initializeSimulation: Computes the collect size and options for real time execution of dispatcher.
- addComponent: adds a component of the type SimComponent to the vector of dispatchable components
- dispatchComponents: The dispatch components function calls the update function (refer SimComponent class), which represents running the computations for 1 time step in the simulation. Thread-safe objects (of class vehicle in our problem) are dispatched in multiple threads. To ensure synchronization, we wait until all the threads are complete and move on to the components that need to be executed sequentially.
- saveCollects: Calls the saveCollects function of the SimComponents objects, saving the simulation data to disk.
- startSimulation: This function uses the system clock to initialize a pseudo-real time counter to propagate in time using a for loop. Setting the iteration index at each time step allows each object to synchronously compute the data for that time step. The clock computes the elapsed time and waits until the DT amount of time has passed before beginning the next iteration. If time more than dt has already passed, it outputs an error saying the dispatcher is jittering. It also saves the collects at the end of the for loop

### SimComponent:
This class provides a template for other model objects to inherit from. 
- constructor: This initialized the Name and component id, used in saving collects.
- update: This function called at every time step of the solution, representing the behavior of a component in that time step.
- saveCollect: This function saves collected data at the end of the simulation.

### Vehicle:
An object of this class contains the simulation of one Evtol vehicle. The vehicle can potentially be placed in 4 states.

1. Cruise
2. Discharged
3. Queue
4. Charging

*Note: The inclusion of 4 states does not counter the objective of the problem statement. The discharged state is used for intermediate calculations, and a vehicle can never be in the discharged state at the end of a simulation time step. However, adding this state greatly simplifies the state transition between charging, queue and cruise. This is clarified with the implementation of the charge queue.*

Initialization: 
- constructor/loadParameters: The constructor calls the loadParameters function, which in turn loads the necessary parameters of a vehicle based on ComponentName string. This string can be initialized to any of the vehicle types from Alpha to Echo. Each parameter is configured using an Armadillo vector for easy file IO.
- initializeVehicle/initializeStates: Initializes the size of state variable collects, vehicle battery and vehicle state.
- At iteration 0, the initialize state and vehicle vector functions are called by the update function.

Propagation: 
- The update function calls the computation for each state. The computeCruiseState computes current battery charge, total time in flight, total passenger-hours, and distance travelled. The computeDischargedState computes nothing but updates the vehicle state variable to Discharged. The computeQueueState computes time in queue. The computeChargingState computes time spent in charging and sets the battery charge to full when charging time has elapsed.
- The getVehicleState and setVehicleState functions are used by the charging queue to transfer the states of the vehicle from discharged to queue or from queue to charging.
- computeMaxFaultsPerHr uses the RAND_MAX to compute the fault probability with maximum resolution.

### Charging Queue: 
The charging queue checks the checks the number of vehicles currently in charging state and the number of vehicles in discharged state. If any vehicle is discharged, it immediately puts it in the queue state and adds its reference to the queue. If the vehicles in charging state are less than the max number of charging stations, it set the difference in number of vehicles to the charging state.

### Observer:
The observer computes the following metrics for each type of vehicle spawned by the simulation. It stores this information in a matrix format in its state variables.
- Average time in flight per vehicle for each vehicle type.
- Average time in charging per vehicle for each vehicle type.
- Average time in queue per vehicle for each vehicle type.
- Total cumulative passenger miles per vehicle type.
- Max number of faults per vehicle type.

## Running solution and test cases
The running of the tests require the PROJECT_HOME_DIR environment variable set to the project root folder. To run the executable, open a command prompt at the project root directory and run:

```
./RunEvtolSimulation.sh
```

Monitor the console, you should see the output as follows: 

```
 **** **** ******* **** **** ******  ** *
 ********  *****     **** *   ****   *** ****
 The Evtols are now in the cloud(s)!!
 **** **** ******* **** **** ******  ** *
 ********  *****     **** *   ****   *** ****

Loading Shared Memory
Creating Dispatcher
Dispatcher: Number of Iterations Estimated 181
Creating Vehicles
Creating 20 Vehicles
Creating Charging Queue with ID 21
Max Charging Stations set to 3
Creating the observer station with ID 22
Adding Components to dispatcher
Starting Simulation
Sim Time is :6660 sec / 10800 sec
```

To run the google tests: 

```
./RunEvtolSimulationTests.sh
```

Note that the tests only cover the Vehicle class at the moment, they don’t look at the other classes, however this is something that I intend to add given time in the future.

## Analyze results

Simulation results are generated by the AnalyzeData.py python script, which plots the results in an .html format using the plotly library. Some results have been checked in for analysis.
- Simulation Collect.html contains all the variables collected throughout the simulation
- Each of the other file represents a metric required by the problem statement. The graph shows the evolution of the metric over time, while the numeric values at the top show the final metrics at the end of the simulation.



