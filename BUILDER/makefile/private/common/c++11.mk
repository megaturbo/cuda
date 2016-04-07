# Version 	: 0.0.6
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch

ifndef __C++11_MK__
__C++11_MK__=true


#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

#cuda windows : visual : rien par defaut

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#rien, par default
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#rien, par default
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	override CXXFLAGS+= -std=c++11#-std=c++0x 
	#To access C++11 threads in Windows, you will need a build of Mingw with posix-threads. 
	
endif

endif#end win

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# ARM   #
############

ifeq  ($(ARCH),arm)

	override CXXFLAGS+= -std=c++11#-std=c++0x

endif

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	override CXXFLAGS+= -std=c++11#-std=c++0x
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	override CXXFLAGS+= -std=c++11#-std=c++0x
	
endif

endif#linux


#############################################
#       			 END     			    #
#############################################

endif#__C++11_MK__
