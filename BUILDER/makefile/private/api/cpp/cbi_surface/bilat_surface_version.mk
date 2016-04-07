# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_SURFACE_VERSION_MK__
__API_BILAT_SURFACE_VERSION_MK__=true

##########################################
#   		Bilat PATH			 #
##########################################

#dependance
include ${API}/bilat_api_version.mk

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

	BILAT_SURFACE_VERSION:=${BILAT_API_VERSION}#
	BILAT_SURFACE_PATH:=${BILAT_SURFACE_HOME}/${BILAT_SURFACE_VERSION}#

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

	BILAT_SURFACE_VERSION:=${BILAT_API_VERSION}#
	BILAT_SURFACE_PATH:=${BILAT_SURFACE_HOME}/${BILAT_SURFACE_VERSION}#

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BILAT_SURFACE_VERSION_MK__

