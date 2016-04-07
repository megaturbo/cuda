# Version 	: 0.0.1
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __COMMON_MK__
__COMMON_MK__=true

###############################################
#  					COMMON						  #
###############################################

########################
#   	pivate		   #
########################

API_ROOT:=${ROOT_MAKEFILE_PRIVATE}/api
API:=${API_ROOT}/cpp
API_CUDA:=${API_ROOT}/cuda

############
#API/BILAT #
############

API_BILAT_TOOLS:=${API}/cbi_tools

API_BILAT_FENETRAGE:=${API}/cbi_fenetrage
API_BILAT_OPENGL:=${API}/cbi_opengl

#image
API_BILAT_IMAGE:=${API}/cbi_image
API_BILAT_IMAGE_CUDA:=${API_CUDA}/cbi_image

#graphe2D
API_BILAT_GRAPH2D:=${API}/cbi_graph2d

#multicourbes
API_BILAT_MULTICOURBES_CUDA:=${API_CUDA}/cbi_multicourbes

#surface
API_BILAT_SURFACE:=${API}/cbi_surface
API_BILAT_SURFACE_CUDA:=${API_CUDA}/cbi_surface

##############
#dataProject #
##############

include dataProject.mk

##############
#  c++11     #
##############

include ${ROOT_MAKEFILE_PRIVATE_COMMON}/c++11.mk

##############
#  cleanALL  #
##############

include ${ROOT_MAKEFILE_PRIVATE_COMMON}/cleanAll.mk

########################
#   	macro		   #
########################

include ${ROOT_MAKEFILE_PRIVATE_COMMON}/macro.mk

###############################################
#  					End						  #
###############################################

endif#__COMMON_MK__
