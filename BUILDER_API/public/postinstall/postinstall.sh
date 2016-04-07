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
#		Principe
#------------------------------------------------------------------------------------

# Jar side:
#
#	un jar (unique)
#   contenant : 
#		class java (standard)
#		un file properties avec les names des shared lib (astuce), toutes! (Ok si pas version de Cuda!)
#
# Build side:
#
#	un file properties avec names all shared lib
#	ant inject good name in propertie file just before make jar, in particular :
#			-version (conetnu dans namefile)
#
# Java side:
#
#	java Loader detect 
#			os
#			architecture
#			compliateur (see -Dcxx ci-dessous)
#	lors du runtime, et cherche dans properties le name de la shared lib aproprier a loader
#
# User side:
#
#	Lancemnet de la jvm
#
#	 	java -Dcxx= visual ou intel ou gcc
#
#	pour indiquer compilateur
#

#------------------------------------------------------------------------------------
#		Main
#------------------------------------------------------------------------------------

export PRIVATE_POST_INSTALL=../../private/common/post_install
# Workspace root path relative to PRIVATE_POST_INSTALL
export ROOT_WORKSPACE=../../../..

source ../apiPack.sh

# a activer en pratique
#source ./jni_fenetrage.sh
#source ./jni_image.sh

#------------------------------------------------------------------------------------
#		end
#------------------------------------------------------------------------------------


