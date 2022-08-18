# Welcome to the Evtol Simulation! 
This repo contains a hypothetical simulation of a fleet of Evtol aircraft with limited battery capacity. The simulation spawns 20 evtols, that fight for dominance over 3 charging stations. Their objective? Accumulate the maximum number of passengers-miles possible. To clarify this metric, 1 passenger mile is equal to 1 passenger travelling 1 mile.

## Project installation
This project requires the following external libraries to work. 
- Armadillo : https://gitlab.com/conradsnicta/armadillo-code
- GoogleTest: https://github.com/google/googletest
- CMake : https://cmake.org

Please clone the git repos and follow the installation directions in the readme of the repositories for standard installation.


## Building the solution

CMake is used to configure the cross platform build. Clone this repository and open a terminal at its root folder that includes the CMakeLists.txt file. Open the CMakeLists.txt and mofify the following line to ensure that armadillo libs and include directories are correctly set. Also set the project home directory to be at the clone location of this repository
'''
set(ARMADILLO_INCLUDE_DIR /Users/username/Documents/Github/armadillo-code/include)
set(ARMADILLO_LIBRARIES /Users/username/Documents/Github/armadillo-code)
set(PROJECT_HOME_DIR "/Users/username/Documents/Github/EvtolSimulation" Global)
'''

Next, use the following commands to build.
'''
cmake -S . -B build
cmake --build build
'''

Once built successfully, to run the exe and unit tests, the correct environment variable needs to be present and the generated directory needs to be created or cleaned. Use RunEvtolSimulaiton.sh and RunEvtolSimulationTests.sh to execute this operation.
'''
./RunEvtolSimulation.sh
./RunEvtolSimulationTests.sh
'''

Finally, once the tests pass and the simulation is run, you can use python to run AnalyzeData.py to generate results in the results folder. Results of a randomized simulation are already provided in an html format, but are overwritten with every run of AnalyzeData.py

## Solution Structure

## Running solution
## Running test cases
## Analyze results

