# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CPP_TEST_MK__
__API_CPP_TEST_MK__=true

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

#version
CPPTEST_VERSION=112

#path
CPPTEST_PATH=${CPPTEST_HOME}/${CPPTEST_VERSION}

#options
CPPTEST_SCR_ENABLE=false

ifeq ($(CPPTEST_SCR_ENABLE),true)
	#compil
	override SRC_AUX+= ${CPPTEST_PATH}/${CPPTEST_SRC}
else
	override API_INC+= ${CPPTEST_PATH}/$(subst ${SEPARATOR}, ${CPPTEST_PATH}/,${CPPTEST_INC})
	#override API_LIB+=
	override API_LIB_STATIC+= ${CPPTEST_PATH}/$(subst ${SEPARATOR}, ${CPPTEST_PATH}/,${CPPTEST_LIB_STATIC}) 
	#override API_LIBRARIES+= 
	#override API_BIN+=
endif

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/intel
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	#override SRC_AUX+= ${API_CppTest}/LIB_STATIC/mingw
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
CPPTEST_VERSION=112

#path
CPPTEST_PATH=${CPPTEST_HOME}/${CPPTEST_VERSION}

CPPTEST_SCR_ENABLE=false

ifeq ($(CPPTEST_SCR_ENABLE),true)
	#compil
	override SRC_AUX+= ${CPPTEST_PATH}/${CPPTEST_SRC}
else
	override API_INC+= ${CPPTEST_PATH}/$(subst ${SEPARATOR}, ${CPPTEST_PATH}/,${CPPTEST_INC})
	#override API_LIB+=
	override API_LIB_STATIC+= ${CPPTEST_PATH}/$(subst ${SEPARATOR}, ${CPPTEST_PATH}/,${CPPTEST_LIB_STATIC}) 
	#override API_LIBRARIES+= 
	#override API_BIN+=
endif

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

endif#__API_CPP_TEST_MK__

