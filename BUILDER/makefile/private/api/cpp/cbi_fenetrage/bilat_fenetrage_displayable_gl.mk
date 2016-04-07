# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_FENETRAGE_DISPLAYABLE_GL_MK__
__API_BILAT_FENETRAGE_DISPLAYABLE_GL_MK__=true

##########################################
#   		Bilat DISPLAYABLE  			 #
##########################################

#dependance
include $(API_BILAT_TOOLS)/bilat_tools_dll.mk
include ${API}/GL.mk
include ${API_BILAT_FENETRAGE}/bilat_fenetrage_version.mk
include $(API_BILAT_FENETRAGE)/bilat_fenetrage_displayable.mk


#path
BILAT_FENETRAGE_DISPLAYABLE_GL_PATH=${BILAT_FENETRAGE_PATH}/${BILAT_FENETRAGE_DISPLAYABLE_GL_HOME}

#########################
# 	COMMOM ALL OS		#
#########################

#compil
override CODE_DEFINE_VARIABLES+=#
override API_INC+= ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/$(subst ${SEPARATOR}, ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/,${BILAT_FENETRAGE_DISPLAYABLE_GL_INC})

#Linkage
#Use SrcAux car nom lib complexe!
override SRC_AUX+= ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/$(subst ${SEPARATOR}, ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/,${BILAT_FENETRAGE_DISPLAYABLE_GL_LIB})  

#Runtime
override API_BIN+= ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/$(subst ${SEPARATOR}, ${BILAT_FENETRAGE_DISPLAYABLE_GL_PATH}/,${BILAT_FENETRAGE_DISPLAYABLE_GL_BIN})

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

endif#__API_BILAT_FENETRAGE_DISPLAYABLE_GL_MK__

