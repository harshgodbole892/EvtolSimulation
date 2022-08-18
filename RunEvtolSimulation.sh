#!/bin/bash
#
# Runfile for project:
#
# 1: Ensure that generated directory exists, if not, then make one:
if [ -d "generated" ]; then
rm -rf generated/*.txt
else
mkdir generated
fi
export PROJECT_HOME_DIR=$(pwd)
# Run generated Files!
./build/EvtolSimulation
###
##### << 1 >> End of section.
###
