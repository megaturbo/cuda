# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_OPEN_MP_MK__
__API_OPEN_MP_MK__=true

##########################################
#   			 OpenMP	   			 #
##########################################

# OMP
# 	Visual 2008 cuda 4.1
# 		bug : /openmp ne peut pas etre use with cu files
# 		Solution : 	compile cu files without /openmp 
# 					compile .ccp file with /openmp
# 		Tip:		compile all file without /openmp
#					modify file usinf omp
#					compile with flag /openmp
# 		Conclusion : with this technique omp ok !
#	Visual 2010 cuda 5.0
# 		bug : fix
#		Conclusion : On peut compiler/linker avec /openmp
#	Linux : ok

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#compil
	override CXXFLAGS+= /openmp  
	
	#link
	#rien automatique by compilateur
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#compil
	override CXXFLAGS+= /Qopenmp
	
	#link
	#rien automatique by compilateur
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#compil
	override CXXFLAGS+= -fopenmp
	
	#link
	#ADD_LIBRARY_FILES+= gomp
	override LDFLAGS+= -lgomp
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

	#compilation
	override CXXFLAGS+= -fopenmp
	#NVCCFLAGS+= -fopenmp#ko
	 
	#link
	#ADD_LIBRARY_FILES+= gomp
	override LDFLAGS+= -lgomp
	override NVCCLDFLAGS+= -lgomp
	#LDFLAGS+= -l$(subst :, -l,${OPENMP_LIBRARIES})  
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#compilation
	override CXXFLAGS+= -openmp
	#NVCCFLAGS+= -openmp
	
	#link
	#ADD_LIBRARY_FILES+= iomp5
	override LDFLAGS+= -liomp5
	override NVCCLDFLAGS+= -liomp5
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#LDFLAGS+= -L$(subst :, -L,${OPENMP_LIB})#car use opencv system
	#RPATH_LINK+=${OPENCV_LIB}
	
	#compilation
	#CXXFLAGS+= -fopenmp
	#NVCCFLAGS+= -fopenmp
	
	#link
	override LDFLAGS+= -lgomp
	override NVCCLDFLAGS+= -lgomp
endif

endif#linux

##########################################
#   			 END 		   			 #
##########################################

endif#__API_OPEN_MP_MK__

