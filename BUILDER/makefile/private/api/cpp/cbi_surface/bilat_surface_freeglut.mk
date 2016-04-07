# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_SURFACE_FREEGLUT_MK__
__API_BILAT_SURFACE_FREEGLUT_MK__=true

##########################################
#   		Bilat Surface Freeglut	 	 #
##########################################


#dependance
include $(API_BILAT_FENETRAGE)/bilat_fenetrage_freeglut_tools.mk
include $(API_BILAT_SURFACE)/bilat_surface_gl.mk

#path
BILAT_SURFACE_FREEGLUT_PATH=${BILAT_SURFACE_PATH}/${BILAT_SURFACE_FREEGLUT_HOME}

#########################
# 	COMMOM ALL OS		#
#########################

#compil
override CODE_DEFINE_VARIABLES+=#
override API_INC+= ${BILAT_SURFACE_FREEGLUT_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_FREEGLUT_PATH}/,${BILAT_SURFACE_FREEGLUT_INC})

#Linkage
#Use SrcAux car nom lib complexe!
override SRC_AUX+= ${BILAT_SURFACE_FREEGLUT_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_FREEGLUT_PATH}/,${BILAT_SURFACE_FREEGLUT_LIB})  

#Runtime
override API_BIN+= ${BILAT_SURFACE_FREEGLUT_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_FREEGLUT_PATH}/,${BILAT_SURFACE_FREEGLUT_BIN})

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)
	#rien
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)
	#rien	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	#rien	
endif

endif#win

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	ARM_FOLDER="_arm"
else
	ARM_FOLDER=#
endif

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)
	#rien	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)
	#rien	
endif

endif#linux

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BILAT_SURFACE_FREEGLUT_MK__
