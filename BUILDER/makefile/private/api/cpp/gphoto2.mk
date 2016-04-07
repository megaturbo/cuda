# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_GPHOTO2_MK__
__API_GPHOTO2_MK__=true

##########################################
#   			 cpptest	   			 #
##########################################

#########################
# 	COMMOM ALL OS		#
#########################



#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# commmon   #
############

#not available

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)


endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	

endif

endif#win


#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# commmon   #
############

#version
GPHOTO2_VERSION=2259

#path
GPHOTO2_PATH=${GPHOTO2_HOME}/${GPHOTO2_VERSION}

override API_INC+= ${GPHOTO2_PATH}/$(subst ${SEPARATOR}, ${GPHOTO2_PATH}/,${GPHOTO2_INC})
override API_LIB+= ${GPHOTO2_PATH}/$(subst ${SEPARATOR}, ${GPHOTO2_PATH}/,${GPHOTO2_LIB})  
override API_BIN+= ${GPHOTO2_PATH}/$(subst ${SEPARATOR}, ${GPHOTO2_PATH}/,${GPHOTO2_BIN}) 
override API_LIBRARIES+= $(subst ${SEPARATOR}, ,${GPHOTO2_LIBRARIES}) 

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#API_CppTest=../API_CppTest
	
	#compil
	#override SRC_AUX+= ${API_CppTest}/INC
	
	#link
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/gcc_arm
endif

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#link 
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link 
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/intelLinux${ARM_FOLDER}
	
endif

endif#linux


##########################################
#   			 END 		   			 #
##########################################

endif#__API_GPHOTO2_MK__

