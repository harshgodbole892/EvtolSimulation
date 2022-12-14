# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Harsh/Documents/Github/EvtolSimulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Harsh/Documents/Github/EvtolSimulation

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/opt/local/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/opt/local/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/opt/local/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/opt/local/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/opt/local/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/opt/local/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/Harsh/Documents/Github/EvtolSimulation/CMakeFiles /Users/Harsh/Documents/Github/EvtolSimulation/CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/Harsh/Documents/Github/EvtolSimulation/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named EvtolSimulationTests

# Build rule for target.
EvtolSimulationTests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 EvtolSimulationTests
.PHONY : EvtolSimulationTests

# fast build rule for target.
EvtolSimulationTests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/build
.PHONY : EvtolSimulationTests/fast

#=============================================================================
# Target rules for targets named EvtolSimulation

# Build rule for target.
EvtolSimulation: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 EvtolSimulation
.PHONY : EvtolSimulation

# fast build rule for target.
EvtolSimulation/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/build
.PHONY : EvtolSimulation/fast

#=============================================================================
# Target rules for targets named gmock

# Build rule for target.
gmock: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gmock
.PHONY : gmock

# fast build rule for target.
gmock/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build
.PHONY : gmock/fast

#=============================================================================
# Target rules for targets named gmock_main

# Build rule for target.
gmock_main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gmock_main
.PHONY : gmock_main

# fast build rule for target.
gmock_main/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/build
.PHONY : gmock_main/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) $(MAKESILENT) -f _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

src/ChargingQueue.o: src/ChargingQueue.cpp.o

.PHONY : src/ChargingQueue.o

# target to build an object file
src/ChargingQueue.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/ChargingQueue.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/ChargingQueue.cpp.o
.PHONY : src/ChargingQueue.cpp.o

src/ChargingQueue.i: src/ChargingQueue.cpp.i

.PHONY : src/ChargingQueue.i

# target to preprocess a source file
src/ChargingQueue.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/ChargingQueue.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/ChargingQueue.cpp.i
.PHONY : src/ChargingQueue.cpp.i

src/ChargingQueue.s: src/ChargingQueue.cpp.s

.PHONY : src/ChargingQueue.s

# target to generate assembly for a file
src/ChargingQueue.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/ChargingQueue.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/ChargingQueue.cpp.s
.PHONY : src/ChargingQueue.cpp.s

src/LocalSharedMemory.o: src/LocalSharedMemory.cpp.o

.PHONY : src/LocalSharedMemory.o

# target to build an object file
src/LocalSharedMemory.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/LocalSharedMemory.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/LocalSharedMemory.cpp.o
.PHONY : src/LocalSharedMemory.cpp.o

src/LocalSharedMemory.i: src/LocalSharedMemory.cpp.i

.PHONY : src/LocalSharedMemory.i

# target to preprocess a source file
src/LocalSharedMemory.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/LocalSharedMemory.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/LocalSharedMemory.cpp.i
.PHONY : src/LocalSharedMemory.cpp.i

src/LocalSharedMemory.s: src/LocalSharedMemory.cpp.s

.PHONY : src/LocalSharedMemory.s

# target to generate assembly for a file
src/LocalSharedMemory.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/LocalSharedMemory.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/LocalSharedMemory.cpp.s
.PHONY : src/LocalSharedMemory.cpp.s

src/Observer.o: src/Observer.cpp.o

.PHONY : src/Observer.o

# target to build an object file
src/Observer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Observer.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Observer.cpp.o
.PHONY : src/Observer.cpp.o

src/Observer.i: src/Observer.cpp.i

.PHONY : src/Observer.i

# target to preprocess a source file
src/Observer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Observer.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Observer.cpp.i
.PHONY : src/Observer.cpp.i

src/Observer.s: src/Observer.cpp.s

.PHONY : src/Observer.s

# target to generate assembly for a file
src/Observer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Observer.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Observer.cpp.s
.PHONY : src/Observer.cpp.s

src/SimComponent.o: src/SimComponent.cpp.o

.PHONY : src/SimComponent.o

# target to build an object file
src/SimComponent.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimComponent.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimComponent.cpp.o
.PHONY : src/SimComponent.cpp.o

src/SimComponent.i: src/SimComponent.cpp.i

.PHONY : src/SimComponent.i

# target to preprocess a source file
src/SimComponent.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimComponent.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimComponent.cpp.i
.PHONY : src/SimComponent.cpp.i

src/SimComponent.s: src/SimComponent.cpp.s

.PHONY : src/SimComponent.s

# target to generate assembly for a file
src/SimComponent.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimComponent.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimComponent.cpp.s
.PHONY : src/SimComponent.cpp.s

src/SimDispatcher.o: src/SimDispatcher.cpp.o

.PHONY : src/SimDispatcher.o

# target to build an object file
src/SimDispatcher.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimDispatcher.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimDispatcher.cpp.o
.PHONY : src/SimDispatcher.cpp.o

src/SimDispatcher.i: src/SimDispatcher.cpp.i

.PHONY : src/SimDispatcher.i

# target to preprocess a source file
src/SimDispatcher.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimDispatcher.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimDispatcher.cpp.i
.PHONY : src/SimDispatcher.cpp.i

src/SimDispatcher.s: src/SimDispatcher.cpp.s

.PHONY : src/SimDispatcher.s

# target to generate assembly for a file
src/SimDispatcher.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/SimDispatcher.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimDispatcher.cpp.s
.PHONY : src/SimDispatcher.cpp.s

src/SimulationMain.o: src/SimulationMain.cpp.o

.PHONY : src/SimulationMain.o

# target to build an object file
src/SimulationMain.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimulationMain.cpp.o
.PHONY : src/SimulationMain.cpp.o

src/SimulationMain.i: src/SimulationMain.cpp.i

.PHONY : src/SimulationMain.i

# target to preprocess a source file
src/SimulationMain.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimulationMain.cpp.i
.PHONY : src/SimulationMain.cpp.i

src/SimulationMain.s: src/SimulationMain.cpp.s

.PHONY : src/SimulationMain.s

# target to generate assembly for a file
src/SimulationMain.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/SimulationMain.cpp.s
.PHONY : src/SimulationMain.cpp.s

src/Vehicle.o: src/Vehicle.cpp.o

.PHONY : src/Vehicle.o

# target to build an object file
src/Vehicle.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Vehicle.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Vehicle.cpp.o
.PHONY : src/Vehicle.cpp.o

src/Vehicle.i: src/Vehicle.cpp.i

.PHONY : src/Vehicle.i

# target to preprocess a source file
src/Vehicle.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Vehicle.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Vehicle.cpp.i
.PHONY : src/Vehicle.cpp.i

src/Vehicle.s: src/Vehicle.cpp.s

.PHONY : src/Vehicle.s

# target to generate assembly for a file
src/Vehicle.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/src/Vehicle.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulation.dir/build.make CMakeFiles/EvtolSimulation.dir/src/Vehicle.cpp.s
.PHONY : src/Vehicle.cpp.s

tests/TestingMain.o: tests/TestingMain.cpp.o

.PHONY : tests/TestingMain.o

# target to build an object file
tests/TestingMain.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/tests/TestingMain.cpp.o
.PHONY : tests/TestingMain.cpp.o

tests/TestingMain.i: tests/TestingMain.cpp.i

.PHONY : tests/TestingMain.i

# target to preprocess a source file
tests/TestingMain.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/tests/TestingMain.cpp.i
.PHONY : tests/TestingMain.cpp.i

tests/TestingMain.s: tests/TestingMain.cpp.s

.PHONY : tests/TestingMain.s

# target to generate assembly for a file
tests/TestingMain.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/EvtolSimulationTests.dir/build.make CMakeFiles/EvtolSimulationTests.dir/tests/TestingMain.cpp.s
.PHONY : tests/TestingMain.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... EvtolSimulation"
	@echo "... EvtolSimulationTests"
	@echo "... gmock"
	@echo "... gmock_main"
	@echo "... gtest"
	@echo "... gtest_main"
	@echo "... src/ChargingQueue.o"
	@echo "... src/ChargingQueue.i"
	@echo "... src/ChargingQueue.s"
	@echo "... src/LocalSharedMemory.o"
	@echo "... src/LocalSharedMemory.i"
	@echo "... src/LocalSharedMemory.s"
	@echo "... src/Observer.o"
	@echo "... src/Observer.i"
	@echo "... src/Observer.s"
	@echo "... src/SimComponent.o"
	@echo "... src/SimComponent.i"
	@echo "... src/SimComponent.s"
	@echo "... src/SimDispatcher.o"
	@echo "... src/SimDispatcher.i"
	@echo "... src/SimDispatcher.s"
	@echo "... src/SimulationMain.o"
	@echo "... src/SimulationMain.i"
	@echo "... src/SimulationMain.s"
	@echo "... src/Vehicle.o"
	@echo "... src/Vehicle.i"
	@echo "... src/Vehicle.s"
	@echo "... tests/TestingMain.o"
	@echo "... tests/TestingMain.i"
	@echo "... tests/TestingMain.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

