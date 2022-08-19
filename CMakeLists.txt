cmake_minimum_required(VERSION 3.14)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(ARMADILLO_INCLUDE_DIR /Users/Harsh/Documents/Github/armadillo-code/include)
set(ARMADILLO_LIBRARIES /Users/Harsh/Documents/Github/armadillo-code)
set(PROJECT_HOME_DIR "/Users/Harsh/Documents/Github/EvtolSimulation" Global)

# Set the project name
project(EvtolSimulation VERSION 1.0)

# include google test framework
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)
# Bring the headers, library includes
include_directories(include)
include_directories(${ARMADILLO_INCLUDE_DIR})
link_directories(${ARMADILLO_LIBRARIES})

# Add sources
file(GLOB SOURCES src/Vehicle.cpp
                  src/ChargingQueue.cpp
                  src/LocalSharedMemory.cpp
                  src/Observer.cpp
                  src/SimComponent.cpp
                  src/SimDispatcher.cpp)

# Add executable
add_executable(EvtolSimulation ${SOURCES} src/SimulationMain.cpp)
target_link_libraries(
  EvtolSimulation
  Threads::Threads
)

# Testing Framework
file(GLOB TESTS "tests/*.cpp")
add_executable(EvtolSimulationTests ${SOURCES} ${TESTS})
target_link_libraries(
  EvtolSimulationTests
  GTest::gtest_main
  Threads::Threads
)
include(GoogleTest)

