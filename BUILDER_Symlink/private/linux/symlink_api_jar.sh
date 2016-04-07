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
else
		SOFT_API=/C/Soft_API
fi

SOURCE_FILE_EXTENSION="*.jar"

API_EXT=${SOFT_API}/ext
API_CBI=${SOFT_API}/cbi

DESTINATION=${SOFT_API}/SYMLINK/JAR
SOURCE_FILE_EXTENSION=jar

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
VERSION=201

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $SOURCE_FILE_EXTENSION

# ---------------------------------------
#		api ext
#----------------------------------------

# -------------
# boost
#--------------

SOURCE=${API_EXT}/boost
VERSION=158

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $SOURCE_FILE_EXTENSION

# -------------
# cpptest
#--------------

SOURCE=${API_EXT}/cpptest
VERSION=112

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $SOURCE_FILE_EXTENSION

# -------------
# opencv
#--------------

SOURCE=${API_EXT}/opencv
VERSION=2411

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $SOURCE_FILE_EXTENSION

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