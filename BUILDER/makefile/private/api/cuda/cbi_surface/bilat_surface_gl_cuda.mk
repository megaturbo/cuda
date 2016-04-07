# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_SURFACE_GL_CUDA_MK__
__API_BILAT_SURFACE_GL_CUDA_MK__=true

##########################################
#   		Bilat CUDA Surface	    	 #
##########################################


#dependance
include $(API_CUDA)/cuda.mk
include $(API)/openmp.mk
include $(API_BILAT_FENETRAGE)/bilat_fenetrage_displayable_gl.mk
include $(API_BILAT_SURFACE)/bilat_surface_gl.mk
include ${API_BILAT_SURFACE}/bilat_surface_version.mk


#path
BILAT_SURFACE_GL_CUDA_PATH=${BILAT_SURFACE_PATH}/${BILAT_SURFACE_GL_CUDA_HOME}

#########################
# 	COMMOM ALL OS		#
#########################

ifeq ($(CBI_API_SCR_ENABLE),true)
	#compil
	override SRC_AUX+= ../06_B_Bilat_Surface_GL_Cuda/src/core
else
	#compil
	override CODE_DEFINE_VARIABLES+=#
	override API_INC+= ${BILAT_SURFACE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_GL_CUDA_PATH}/,${BILAT_SURFACE_GL_CUDA_INC})
	
	#Linkage
	#Use SrcAux car nom lib complexe!
	override SRC_AUX+= ${BILAT_SURFACE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_GL_CUDA_PATH}/,${BILAT_SURFACE_GL_CUDA_LIB})  
	
	#Runtime
	override API_BIN+= ${BILAT_SURFACE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_SURFACE_GL_CUDA_PATH}/,${BILAT_SURFACE_GL_CUDA_BIN})
endif

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

endif#__API_BILAT_SURFACE_GL_CUDA_MK__
