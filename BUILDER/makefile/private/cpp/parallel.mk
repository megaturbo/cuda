
ifndef __PARALLEL_MK__
__PARALLEL_MK__=true

##########
# parallel   #
##########

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

ifeq (${COMPILATEUR},g++)
MAKE_FILE_NAME:=gcc.mk# see /usr/local/etc/cbi/dev/make/makeGcc.sh
endif

ifeq (${COMPILATEUR},INTEL)
MAKE_FILE_NAME:=intelLinux.mk# see /usr/local/etc/cbi/dev/make/makeIntelLinux.sh
endif

else#windows
NB_THREAD_COMPILATION:=$(NUMBER_OF_PROCESSORS)#NUMBER_OF_PROCESSORS variable of win10

ifeq (${COMPILATEUR},MINGW)
MAKE_FILE_NAME:=mingw.mk# see G:\CBI\HEARC\SoftLocal\ScriptLaucher\makefile\makeMinGW.bat
endif
ifeq (${COMPILATEUR},VISUAL)
MAKE_FILE_NAME:=visual.mk# see G:\CBI\HEARC\SoftLocal\ScriptLaucher\makefile\makeVisual.bat
endif
ifeq (${COMPILATEUR},INTEL)
MAKE_FILE_NAME:=intelWin.mk# see G:\CBI\HEARC\SoftLocal\ScriptLaucher\makefile\makeIntelWin.bat
endif
endif

.PHONY: jall	
jall: echoing init
	@echo "[CBI] -> Compilation parallel ($(NB_THREAD_COMPILATION) threads)"
	@echo ""
	@exec make -f $(ROOT_MAKEFILE_PRIVATE_CPP)/$(MAKE_FILE_NAME) $(INPUT_MAKE) compilelink -j${NB_THREAD_COMPILATION} --no-print-directory
	@exec make -f $(ROOT_MAKEFILE_PRIVATE_CPP)/$(MAKE_FILE_NAME) $(INPUT_MAKE) deploy --no-print-directory
	@echo ""
	@echo "[CBI] -> "$(TITLE)" : End ALL!"
	@echo ""
	
#pour parallel compil only
.PHONY: compilelink	
compilelink:$(TARGET) 

#############################################
#       			 END     			    #
#############################################

endif#__PARALLEL_MK__
