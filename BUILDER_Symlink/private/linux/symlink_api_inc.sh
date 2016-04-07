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

API_EXT=${SOFT_API}/ext
API_CBI=${SOFT_API}/cbi

DESTINATION=${SOFT_API}/SYMLINK/INC

# -------------
#		purge
#--------------

purgeSymlink $DESTINATION

# ---------------------------------------
#		chrono
#----------------------------------------

TIME_START_S=$(date +%s)
EXTENSTION=h

# ---------------------------------------
#		api cbi
#----------------------------------------

SOURCE=$API_CBI
VERSION=201

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $EXTENSTION

# ---------------------------------------
#		api ext
#----------------------------------------

# -------------
# boost
#--------------

SOURCE=${API_EXT}/boost
VERSION=158

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $EXTENSTION

# -------------
# cpptest
#--------------

SOURCE=${API_EXT}/cpptest
VERSION=112

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $EXTENSTION

# -------------
# opencv
#--------------

SOURCE=${API_EXT}/opencv
VERSION=2411

symlinkRecursifVersionExtentionApi $SOURCE $VERSION $DESTINATION $EXTENSTION

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