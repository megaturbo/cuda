#!/bin/bash
#
# Version:	0.0.2
#

set -e

#-----------------------------------------------
#		Input
#-----------------------------------------------

#rien

#------------------------------------------------------------------------------------
#		Main
#------------------------------------------------------------------------------------

#-----------------------------------------------
#		data
#-----------------------------------------------

OS=$(uname)
if [[ ${OS} == *Linux* ]] 
then
	export PATH_INSTALL_API_VERSION=${BILAT_IMAGE_HOME}/${API_VERSION_PACK}
else
	# avant: C:/Soft_API/ext/CppTest/002
	# apres: /C:/Soft_API/ext/CppTest/002
	export PATH_INSTALL_API_VERSION=/${BILAT_IMAGE_HOME}/${API_VERSION_PACK}
	
	# avant: /C:/Soft_API/ext/CppTest/002
	# apres: /C/Soft_API/ext/CppTest/002
	export PATH_INSTALL_API_VERSION=${PATH_INSTALL_API_VERSION/:/}
fi

#nameproject
#nameApi  
#namejar 
#destinationJar
#CLASSPATH
export nameproject=03_G_JBilatImageGL_JNI 
export nameApi=${BILAT_IMAGE_JNI_HOME}
export namejar=${BILAT_IMAGE_JNI_HOME}_${API_VERSION_PACK} #sans .jar
export destinationJar=${PATH_INSTALL_API_VERSION}/$BILAT_IMAGE_JNI_HOME/JAR
#simlink pas encore fait!
export CLASSPATH=${BILAT_FENETRAGE_HOME}/${API_VERSION_PACK}/${BILAT_FENETRAGE_CANVAS_JNI_HOME}/JAR


#-----------------------------------------------
#		run
#-----------------------------------------------

pushd  ${PRIVATE_POST_INSTALL}
source ./jni.sh
popd

#------------------------------------------------------------------------------------
#		end
#------------------------------------------------------------------------------------


