# Welcome to the Evtol Simulation! 
This repo contains a hypothetical simulation of a fleet of Evtol aircraft with limited battery capacity. The simulation spawns 20 evtols in the cloud(s), that fight for dominance over 3 charging stations. Their objective? Accumulate the maximum number of passengers-miles possible. To clarify this metric, 1 passenger mile is equal to 1 passenger travelling 1 mile.
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
- Open the CMakeLists.txt and mofify the following line to ensure that armadillo libs and include directories are correctly set. 
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

- Classes under the simulation support type are used to deploy the basic functions of the simulation. They include:
    - Local Shared Memory : This class manages the global simulation parameters like time step, iteration index, and options for seeding random initializations. It also sets global model specific parameters like number of vehicles and charging stations.
    - Sim Dispatcher: This class manages running the loops for dispatching each time step.
    - Sim Component: This class provides a base class (template) for each model class. This enables a very generic approach towards dispatching a simulation.
- Classes under the model type are used to simulate the individual components of the simulation. All the classes of the model type are derived from SimComponent class. With our problem definition we have have following classes:
    - Vehicle Class: Defines a vehicle which can be initialized with certian paramters. It can fly and charge based on the simulation conditions. It collects the data assoicated with the vehicle and writes to the generated folder at the end of the simulation.
    - Charging Queue: An object of this class manages the process of setting objects of the vehicle class in the appropriate states according to the simulation conditions and simulates an collection of charging stations. It monitors the number of vehicles charging across the simulation and writes the data to disk.
    - Observer: This component is used to monitor the different global metrics of the solution, like total number of passenger-hrs per vehicle type, or the average time spent in cruise. It also writes the collected data to disk.
- The SimulationMain function is used for the assebly of the simualtion and random initialization of the vehicles. 

## Running solution
## Running test cases
## Analyze results

