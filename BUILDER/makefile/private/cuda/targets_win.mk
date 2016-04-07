ifndef __TARGET_WIN_CUDA_MK__
__TARGET_WIN_CUDA_MK__=true

##############################################
#      			  TARGET 				     #
##############################################

#all: version help
#all: echoing $(TARGET) deploy 
.DEFAULT_GOAL:=all 
all: echoing init $(TARGET) deploy cleanTempCudaFile 
	@echo ""
	@echo "[CBI] -> "$(TITLE)"   : End ALL!"
	@echo ""
	
.PHONY: version
version:
	@echo ""
	@nvcc --version
	@echo ""
	@cl 

.PHONY: help
help:
	@echo ""
	@nvcc --help

##########
# parallel   #
##########

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/parallel.mk
	
##########
# deploy #
##########

.PHONY: deploy
deploy:
ifdef TARGET_DEPLOY_PATH
	@$(shell cp $(TARGET) $(TARGET_DEPLOY))
	@echo ""
	@echo "[CBI] -> Deploying    : "$(TARGET_DEPLOY) 
endif

##########
# run    #
##########

.PHONY: run
run: printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Running  : "$(TARGET)  $(ARGS)
	@echo ""
	@echo "------------------------------------------------------------------------"
	@echo ""
	@echo ""
	@$(TARGET) $(ARGS)

.PHONY: runDeploy	
runDeploy: printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Running  : "$(TARGET_DEPLOY)  $(ARGS)
	@echo ""
	@echo "------------------------------------------------------------------------"
	@echo ""
	@echo ""
	@$(TARGET_DEPLOY) $(ARGS)	


.PHONY: printRuntimeInfo	
printRuntimeInfo:
	@echo ""
	@echo "[CBI] -> API BIN      :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh ${sort ${API_BIN}}	
	@echo ""
	@echo "[CBI] -> ARGS         :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh ${sort ${ARGS}}	

##########
# kill   #
##########

.PHONY: kill
kill:
	@echo "[CBI] -> killing : "${TARGET_NAME_EXE}
	@powershell stop-process -processname ${TARGET_NAME}
	@echo "[CBI] -> ..."
	@echo "[CBI] -> done"!
	@echo ""

##########
# depends #
##########
	
.PHONY: dependenciesWin
dependenciesWin:	printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Dependencies .dll : "${TARGET}
	@${DEPENDS_EXE} ${TARGET_DEPLOY}

##########
# contents #
##########

.PHONY: contententsWin
contententsWin:	printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Dependencies .dll : "${TARGET_NAME_EXE}
	@${DEPENDS_EXE} ${TARGET_DEPLOY}

##########
# init   #
##########

.PHONY: init	
init:
#create folder heirerarchy TARGET_BIN_PATH iff don't exist
ifeq (,$(findstring $(TARGET_BIN),$(wildcard $(TARGET_BIN) )))
	@$(shell mkdir -p $(TARGET_BIN))
	@echo "[CBI] -> Create folder  : "$(TARGET_BIN)
endif
#create folder heirerarchy TARGET_BIN_PATH iff don't exist
ifeq (,$(findstring $(TARGET_OBJ),$(wildcard $(TARGET_OBJ) )))
	@$(shell mkdir -p $(TARGET_OBJ))
	@echo "[CBI] -> Create folder  : "$(TARGET_OBJ)
endif
#create folder heirerarchy TARGET_BIN_PATH iff don't exist
ifeq (,$(findstring $(TARGET_CUBIN),$(wildcard $(TARGET_CUBIN) )))
	@$(shell mkdir -p $(TARGET_CUBIN))
	@echo "[CBI] -> Create folder  : "$(TARGET_CUBIN)
endif
ifeq (,$(findstring $(TARGET_DEPLOY_PATH_BIN),$(wildcard $(TARGET_DEPLOY_PATH_BIN) )))
	@$(shell mkdir -p $(TARGET_DEPLOY_PATH_BIN))
	@echo "[CBI] -> Create folder : "$(TARGET_DEPLOY_PATH_BIN)
	@echo ""
endif
	@echo ""

##########
# install #
##########

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/install.mk

##########
# doc    #
##########

include ${ROOT_MAKEFILE_PRIVATE_DOC}/doxyCPP.mk

##########
# clean #
##########

.PHONY: clean	
clean:
	@rm -f $(TARGET_OBJ)/*.o
	@rm -f $(TARGET_OBJ)/*.obj
	@rm -f $(TARGET_BIN)/*.exp
	@rm -f $(TARGET_BIN)/*.lib
	@rm -f $(TARGET)
	@rm -f $(TARGET_DEPLOY)
	@rm -f $(TARGET_CUBIN)/*
	@rm -f $(TARGET_DOC_DEPLOY_FILE)
	@rm -f -r $(TARGET_DOC_PATH)
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target            : "$(TARGET_NAME)
	@echo "[CBI] -> Task			     : DELETE"
	@echo "[CBI]"
	@echo "[CBI] -> Delete .obj       : "$(TARGET_OBJ)
	@echo "[CBI] -> Delete .bin       : "$(TARGET_BIN)
	@echo "[CBI] -> Delete .cubin     : "$(TARGET_CUBIN)
	@echo "[CBI] -> Delete doc        : "$(TARGET_DOC_PATH)
	@echo "[CBI]"
	@echo "[CBI] -> Delete deploy     : "$(TARGET_DEPLOY)
	@echo "[CBI] -> Delete deploy doc : "$(TARGET_DOC_DEPLOY_FILE)
	@echo "=================================================================================="
	@echo ""

.PHONY: cleanTempCudaFile
cleanTempCudaFile:
	@rm -f ${TARGET_CUBIN}/*.c
	@rm -f ${TARGET_CUBIN}/*.cpp
	@rm -f ${TARGET_CUBIN}/*.gpu
	@rm -f ${TARGET_CUBIN}/*.i
	@rm -f ${TARGET_CUBIN}/*.ii
	@rm -f ${TARGET_CUBIN}/*.hash
	@rm -f ${TARGET_CUBIN}/*.ptx
#@echo "[CBI] -> Cleaning     : Cuda temp files, excepted .cubin for JCuda"
#@echo ""

#rm -r #serait recursif (dangereux!!)
#rm -f #pas d'erreur si file existe pas!

##########
# echo   #
##########

.PHONY: echoing
echoing:
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] ->"
	@echo "[CBI] -> Build        : "$(TARGET)
	@echo "[CBI] -> Deploy       : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	      : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	      : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 		  : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Task		  : Compiling-Linking !" 
	@echo "=================================================================================="
	@echo ""
	@echo "[CBI] -> SRC AUX (Recursif) :" 
	@echo "[CBI] ->"   
#@echo $(SRC_AUX)	
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(SRC_AUX)
	@echo "" 
	@echo "[CBI] -> CXXFLAGS (Partial) :"
	@echo "[CBI] ->" 
#@echo $(CXXFLAGS)	
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(call not-containing,-I,$(CXXFLAGS)) #sort kp, why
	@echo "" 
	@echo "[CBI] -> CXXLDFLAGS (Partial) :"
	@echo "[CBI] ->" 
#@echo $(CXXLDFLAGS)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(call not-containing,-L, $(call not-containing,-l,$(CXXLDFLAGS)))   #sort ko why?
	@echo "" 
	@echo "[CBI] -> NVCCFLAGS (Partial) :"
	@echo "[CBI] ->" 
#@echo $(NVCCFLAGS)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(call not-containing,-I,$(NVCCFLAGS)))
	@echo "" 
	@echo "[CBI] -> NVCCLDFLAGS (Partial) :"
	@echo "[CBI] ->"  
#@echo $(NVCCLDFLAGS)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(call not-containing,-L, $(call not-containing,-l,$(NVCCLDFLAGS))))
	@echo ""  
	@echo "[CBI] -> INC_PATH (auto detect):"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(INC_PATH))
	@echo "" 
	@echo "[CBI] -> LIB_PATH (auto detect):"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(LIB_PATH))
	@echo ""
	@echo "[CBI] -> API_INC :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(API_INC))
	@echo "" 
	@echo "[CBI] -> API_LIB :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(API_LIB))
	@echo "" 
	@echo "[CBI] -> API_BIN :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(API_BIN))
	@echo "" 
	@echo "[CBI] -> API_LIBRARIES :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(API_LIBRARIES))
	@echo "" 

##############################################
#       			 HELP  				     #
##############################################

# target : dependencies
#
# $@ = name of the target
# $^ = all dependencie of a target
# $< =first (unique dependency of a target) (rm, compilation,linking)
#
# @ = diminue verbosit� commande
#
# Attention : tabulation obligatoire avant commande dans rule!!
#
# http://www.gnu.org/software/make/manual/


#############################################
#       			 END     			    #
#############################################

endif#__TARGET_WIN_CUDA_MK__
