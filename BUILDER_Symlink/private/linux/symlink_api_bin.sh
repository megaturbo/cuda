#!/bin/bash
#
# version	: 0.0.1
# author	: cedric.bilat@he-arc.ch


# ---------------------------------------
#		Init
#----------------------------------------

set -e
source ./symlink_tools.sh

# ---------------------------------------
#		Destination
#----------------------------------------

# -------------
#		OS
#--------------

OS=$(uname)

if [[ ${OS} == *Linux* ]] 
then
		SOFT_API=/opt/api		
		SOURCE_FILE_EXTENSION="*.so"
		SOURCE_FILE_EXTENSION_VERSION="*.so.*"
else
		SOFT_API=/C/Soft_API
		SOURCE_FILE_EXTENSION="*.dll"
fi

API_EXT=${SOFT_API}/ext
API_CBI=${SOFT_API}/cbi

DESTINATION=${SOFT_API}/SYMLINK/BIN

# -------------
#		purge
#--------------

purgeSymlink $DESTINATION

# ---------------------------------------
#		chrono
#----------------------------------------

TIME_START_S=$(date +%s)

# ---------------------------------------
#		api cbi
#----------------------------------------

SOURCE=$API_CBI

symlinkRecursif $SOURCE $DESTINATION $SOURCE_FILE_EXTENSION

# ---------------------------------------
#		api ext
#----------------------------------------

# -------------
# boost
#--------------

SOURCE=${API_EXT}

if [[ ${OS} == *Linux* ]] 
then
	#pas genant mais conflit si plusieurs versions
	# xxx.so pointe vers xxx.so.1
	# xxx.so.1
	#symlinkRecursif $SOURCE $DESTINATION $SOURCE_FILE_EXTENSION

	symlinkRecursif $SOURCE $DESTINATION $SOURCE_FILE_EXTENSION_VERSION
else
	symlinkRecursif $SOURCE $DESTINATION $SOURCE_FILE_EXTENSION
fi

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