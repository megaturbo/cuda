#!/bin/bash
#
# version	: 0.0.1
# author	: cedric.bilat@he-arc.ch


# ---------------------------------------
#		Init
#----------------------------------------

set -e

# ../.. accede root workpsace
pushd ..

source ./linux/symlink_tools.sh

# ---------------------------------------
#		Destination
#----------------------------------------

DESTINATION=../INC
DESTINATION_CUDA=../INC_CUDA
DESTINATION_JAR=../JAR

purgeSymlink $DESTINATION
purgeSymlink $DESTINATION_CUDA
purgeSymlink $DESTINATION_JAR

# ---------------------------------------
#		chrono
#----------------------------------------

TIME_START_S=$(date +%s)

# ---------------------------------------
#		List Projets
#----------------------------------------

source ../public/symlink_data.sh

# ---------------------------------------
#		Main
#----------------------------------------

for projeti in $listProjet
	do
		SOURCE=../../$projeti/src/core
		SOURCE_FILE_EXTENSION="*.h"
		
		symlinkRecursif $SOURCE $DESTINATION $SOURCE_FILE_EXTENSION
	done
	
for projeti in $listProjetCuda
	do
		SOURCE=../../$projeti/src/core
		SOURCE_FILE_EXTENSION="*.h"
		
		symlinkRecursif $SOURCE $DESTINATION_CUDA $SOURCE_FILE_EXTENSION
	done

for projeti in $listProjetJNI
	do
		SOURCE=../../$projeti
		SOURCE_FILE_EXTENSION="*.jar"
		
		symlinkRecursif $SOURCE $DESTINATION_JAR $SOURCE_FILE_EXTENSION
	done

popd

# ---------------------------------------
#		chrono
#----------------------------------------

TIME_STOP_S=$(date +%s)

echo ""
echo " Delta Time = $(($TIME_STOP_S - $TIME_START_S)) (s)"
echo ""

# ---------------------------------------
#		end
#----------------------------------------
