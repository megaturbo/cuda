# Version 	: 0.0.6
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch

ifndef __GCC_ARM_MK_PUBLIC__
__GCC_ARM_MK_PUBLIC__=true

##############################################
#   			 Variables     				 #
##############################################

########
#arm #
########

ifeq (${ARCH},arm)	

	#Deploment data
	JETSON_1_IP:=157.26.100.60
	JETSON_2_IP:=157.26.103.143
	
	JETSON_IP:=${JETSON_1_IP}
	
	JETSON_USER:=ubuntu
	JETSON_BIN:=/home/ubuntu/HEARC/bin

	ifeq ($(PLATFORME),jetson) 
		PLATFORME_IP:=${JETSON_IP}
		PLATFORME_BIN:=${JETSON_BIN}
		PLATFORME_USER:=${JETSON_USER}
	endif

endif


endif#__GCC_ARM_MK_PUBLIC__

