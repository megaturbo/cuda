# Version 	: 0.0.6
# Author 	: Cedric.Bilat@he-arc.ch
#
#
# https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/
#

ifndef __API_MKL_MK__
__API_MKL_MK__=true

##########################################
#   		MKL				   			 #
##########################################

#http://software.intel.com/en-us/articles/intel-mkl-link-line-advisor

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#compil
	#TODO

	#link
	#TODO
	
	#runtime
	#TODO 
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#compilation. TODO necessaire?
	override CXXFLAGS+= /Qmkl
	
	#link
	#rien
	
	#runtime
	#rien 
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#Possible? je pense pas!
	
	#compil
	#TODO
	
	#link
	#TODO 
	
endif

endif#win

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#compil
	#CXXFLAGS+= -I/opt/intel/mkl/include
	#CXXFLAGS+= -I$(subst :, -I,${MKL_INC})
	override API_INC+=$(subst ${SEPARATOR}, ,${MKL_INC})

	override CXXFLAGS+= -DMKL_ILP64 
	override CXXFLAGS+= -m64 

	#link
	#LDFLAGS+= -L/opt/intel/mkl/lib/intel64 
	#LDFLAGS+= -L$(subst :, -L,${MKL_LIB}) 
	#LDFLAGS+= -l$(subst :, -l,${MKL_LIB_GCC_LIBRARIES}) 

	override API_LIB+= ${BOOST_PATH}/$(subst ${SEPARATOR}, ,${MKL_LIB})
	override API_LIBRARIES+= $(subst ${SEPARATOR}, ,${MKL_LIB_GCC_LIBRARIES}) 

	#runtime
	override API_BIN+= $(MKL_LIB)
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#compilation
	override CXXFLAGS+= -mkl
	
	#link
	#LDFLAGS+= -l$(subst :, -l,${MKL_LIB_INTEL_LIBRARIES}) 
	override API_LIBRARIES+= $(subst ${SEPARATOR}, ,${MKL_LIB_INTEL_LIBRARIES}) 

	#runtime
	override API_BIN+= $(MKL_LIB)
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#pas possible
endif

endif#linux

##########################################
#   			 END 		   			 #
##########################################

endif#__API_MKL_MK__

