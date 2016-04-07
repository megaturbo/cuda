ifndef __PARALLEL_CUDA_MK__
__PARALLEL_CUDA_MK__=true

##############################################
# 			parallel 						 #
##############################################

#problem
#
# all : a b c
#
# make -j8
#
# a b c se font en parallel
#
# example 
#
#	a = init
#	b = $(TARGET)
#	c = deploy
#
# deploy se fait avant la fin de la compilation (b)
#

ifeq ($(OS),Linux)
NB_THREAD_COMPILATION:=$(shell nproc)#
MAKE_FILE_NAME:=cudaGCC.mk# see /usr/local/etc/cbi/dev/make/makeCudaGcc.sh
else#windows
NB_THREAD_COMPILATION:=$(NUMBER_OF_PROCESSORS)#NUMBER_OF_PROCESSORS variable of win10
MAKE_FILE_NAME:=cudaVisual.mk# see G:\CBI\HEARC\SoftLocal\ScriptLaucher\makefile\makeCudaVisual.bat
endif

.PHONY: jall	
jall: echoing init
	@echo "[CBI] -> Compilation parallel ($(NB_THREAD_COMPILATION) threads)"
	@echo ""
	@exec make -f $(ROOT_MAKEFILE_PRIVATE_CUDA)/$(MAKE_FILE_NAME) $(INPUT_MAKE) compilelink -j${NB_THREAD_COMPILATION} --no-print-directory
	@exec make -f $(ROOT_MAKEFILE_PRIVATE_CUDA)/$(MAKE_FILE_NAME) $(INPUT_MAKE) deploy cleanTempCudaFile --no-print-directory
	@echo ""
	@echo "[CBI] -> "$(TITLE)" : End ALL!"
	@echo ""
	
#pour parallel compil only
.PHONY: compilelink	
compilelink:$(TARGET) 

#############################################
#       			 END     			    #
#############################################

endif#__PARALLEL_CUDA_MK__
