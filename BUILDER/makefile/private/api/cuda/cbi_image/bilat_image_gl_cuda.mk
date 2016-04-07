# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_IMAGE_CUDA_GL_MK__
__API_BILAT_IMAGE_CUDA_GL_MK__=true

##########################################
#   		Bilat CUDA IMAGE GL 		 #
##########################################


#dependance
include $(API_CUDA)/cuda.mk
include $(API_BILAT_IMAGE)/bilat_image_gl.mk

#path
BILAT_IMAGE_GL_CUDA_PATH=${BILAT_IMAGE_PATH}/${BILAT_IMAGE_GL_CUDA_HOME}

#########################
# 	COMMOM ALL OS		#
#########################

#compil
override CODE_DEFINE_VARIABLES+=#
override API_INC+= ${BILAT_IMAGE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_IMAGE_GL_CUDA_PATH}/,${BILAT_IMAGE_GL_CUDA_INC})

#Linkage
#Use SrcAux car nom lib complexe!
override SRC_AUX+= ${BILAT_IMAGE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_IMAGE_GL_CUDA_PATH}/,${BILAT_IMAGE_GL_CUDA_LIB})  

#Runtime
override API_BIN+= ${BILAT_IMAGE_GL_CUDA_PATH}/$(subst ${SEPARATOR}, ${BILAT_IMAGE_GL_CUDA_PATH}/,${BILAT_IMAGE_GL_CUDA_BIN})

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

endif#__API_BILAT_IMAGE_CUDA_GL_MK__
