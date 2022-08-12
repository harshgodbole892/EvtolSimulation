#!/bin/bash
#
# Runfile for project:
#
# 1: Ensure that generated directory exists, if not, then make one:
if [ -d "Generated" ]; then
rm -rf Generated/*.txt
else
mkdir Generated
fi
export PROJECT_HOME_DIR=$(pwd)
# Run generated Files!
./bin/EvtolSimulation
###
##### << 1 >> End of section.
###
