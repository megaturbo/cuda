# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

#ifndef __API_BILAT_SURFACE_CUDA_FREEGLUT_MK__
#__API_BILAT_SURFACE_CUDA_FREEGLUT_MK__=true

##########################################
#   	Bilat CUDA Surface Freeglut 	 #
##########################################

#
# Only helper makefiles, no real Cuda Freeglut api
#

#dependance
include $(API_BILAT_SURFACE)/bilat_surface_freeglut.mk
include $(API_BILAT_SURFACE_CUDA)/bilat_surface_gl_cuda.mk

##########################################
#   			 END 		   			 #
##########################################

#endif#__API_BILAT_SURFACE_CUDA_FREEGLUT_MK__