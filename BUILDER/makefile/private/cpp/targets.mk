ifndef __TARGET_MK__
__TARGET_MK__=true

##############################################
#      			  TARGET 				     #
##############################################

.DEFAULT_GOAL:=all 
all: echoing init $(TARGET) deploy
	@echo ""
	@echo "[CBI] -> "$(TITLE)" : End ALL!"
	@echo ""

.PHONY: version	
version:
	@echo ""
	@$(VERSION_CXX)
	@echo ""

.PHONY: help
help:
	@echo ""
	@$(CXX_HELP)
	@echo ""

##########
# parallel   #
##########

include ${ROOT_MAKEFILE_PRIVATE_CPP}/parallel.mk

##########
# init   #
##########

.PHONY: init
init:
#create folder heirerarchy TARGET_BIN_PATH iff don't exist
ifeq (,$(findstring $(TARGET_BIN_PATH),$(wildcard $(TARGET_BIN_PATH) )))
	@$(shell mkdir -p $(TARGET_BIN_PATH))
	@echo "[CBI] -> Create folder : "$(TARGET_BIN_PATH)
endif
#create folder heirerarchy TARGET_OBJ_PATH iff don't exist
ifeq (,$(findstring $(TARGET_OBJ_PATH),$(wildcard $(TARGET_OBJ_PATH) )))
	@$(shell mkdir -p $(TARGET_OBJ_PATH))
	@echo "[CBI] -> Create folder : "$(TARGET_OBJ_PATH)
endif
ifeq (,$(findstring $(TARGET_DEPLOY_PATH_BIN),$(wildcard $(TARGET_DEPLOY_PATH_BIN) )))
	@$(shell mkdir -p $(TARGET_DEPLOY_PATH_BIN))
	@echo "[CBI] -> Create folder : "$(TARGET_DEPLOY_PATH_BIN)
endif
	@echo ""

# -p permet de cr�er l�arborescence complete si existe pas

##########
# run    #
##########

.PHONY: run
run: printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Running      : "$(TARGET)  $(ARGS)
	@echo ""
	@echo "------------------------------------------------------------------------"
	@echo ""
	@echo ""
	@$(TARGET) $(ARGS)
#$(MAKECMDGOALS) donne liste des para de make, et ainsi les args du code en c si il y en a

.PHONY: runDeploy	
runDeploy: printRuntimeInfo 
	@echo ""
	@echo "[CBI] -> Running      : "$(TARGET_DEPLOY)  $(ARGS)
	@echo ""
	@echo "------------------------------------------------------------------------"
	@echo ""
	@echo ""
	@$(TARGET_DEPLOY) $(ARGS)

.PHONY: runGl
runGl: printRuntimeInfo
#gl is a wrapper of virtualgl
#gl is necessary to run opengl remotely with turbovnc
#OS : linux only
	@echo ""
	@echo "[CBI] -> Running remote-gl : "$(TARGET)  $(ARGS)
	@echo ""
	@echo ""
	@gl $(TARGET) $(ARGS)

.PHONY: runGlDeploy
runGlDeploy: printRuntimeInfo
#gl is a wrapper of virtualgl
#gl is necessary to run opengl remotely with turbovnc
#OS : linux only!
	@echo ""
	@echo "[CBI] -> Running remote-gl : "$(TARGET_DEPLOY)  $(ARGS)
	@echo ""
	@echo ""
	@gl $(TARGET_DEPLOY) $(ARGS)


.PHONY: printRuntimeInfo	
printRuntimeInfo:
	@echo "[CBI] -> API BIN      :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh ${sort ${API_BIN}}	
	@echo ""
	@echo "[CBI] -> ARGS         :"
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh ${sort ${ARGS}}	
#@${info "PATH= "${PATH}}


##########
# kill   #
##########

.PHONY: kill
kill:
	@echo "[CBI] -> killing : "${TARGET_NAME_EXE}
ifeq ($(OS),Linux)
	@killall ${TARGET_NAME_EXE}
else
	@powershell stop-process -processname ${TARGET_NAME}
endif
	@echo "[CBI] -> ..."
	@echo "[CBI] -> done"!
	@echo ""
	
##########
# depends #
##########
	
.PHONY: dependenciesLinux
dependenciesLinux: printRuntimeInfo
	@echo ""
ifeq (${TARGET_MODE},STATIC_LIB)	
	@echo "[${TARGET_NAME}.${EXTENSION_LIB}] depends from :"
	@echo ""
	@ar -t ${TARGET_DEPLOY}
else ifeq (${TARGET_MODE},SHARED_LIB)
	@echo "[${TARGET_NAME}.${EXTENSION_DLL}] depends from :"
	@echo ""
	@ldd -v ${TARGET_DEPLOY}
else
	@echo "[${TARGET_NAME}.run] depends from :"
	@echo ""
	@ldd -v ${TARGET_DEPLOY}
endif	
	@echo ""

.PHONY: dependenciesWin
dependenciesWin:	printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Dependencies .dll : "${TARGET_NAME_EXE}
	@${DEPENDS_EXE} ${TARGET_DEPLOY}


##########
# contents #
##########

.PHONY: contentsLinux
contentsLinux:
	@echo ""
ifeq (${TARGET_MODE},STATIC_LIB)	
	@echo "[${TARGET_NAME}.${EXTENSION_LIB}] export :"
	@echo ""
	@ar -t ${TARGET_DEPLOY}
else ifeq (${TARGET_MODE},SHARED_LIB)
	@echo "[${TARGET_NAME}.${EXTENSION_DLL}] export:"
	@echo ""
	@echo "[CBI] -> nm"
	@echo ""
	@nm -D --defined-only --extern--only ${TARGET_DEPLOY}
	@echo ""
	@echo "[CBI] -> readelf"
	@echo ""
	@readelf -s ${TARGET_DEPLOY}
endif	
	@echo ""

.PHONY: contententsWin
contententsWin:	printRuntimeInfo
	@echo ""
	@echo "[CBI] -> Dependencies .dll : "${TARGET_NAME_EXE}
	@${DEPENDS_EXE} ${TARGET_DEPLOY}

##########
# deploy #
##########

.PHONY: deploy
deploy:
ifdef IS_DEPLOY
	@$(shell cp $(TARGET) $(TARGET_DEPLOY))	
	@echo ""
	@echo "[CBI] -> Deploying    : "$(TARGET_DEPLOY)
ifneq ($(nbFileRessources),0)
	@echo "[CBI] -> Copying      : "$(RESOURCES_PATH)" -> "${TARGET_DEPLOY_PATH_BIN}
	@cp -f -r $(RESOURCES_PATH)/* $(TARGET_DEPLOY_PATH_BIN)
endif
endif

##########
# install #
##########

include ${ROOT_MAKEFILE_PRIVATE_CPP}/install.mk
	
##########
# doc    #
##########

include ${ROOT_MAKEFILE_PRIVATE_DOC}/doxyCPP.mk

##########
# clean #
##########

.PHONY: clean	
clean:
	@rm -f $(TARGET_OBJ_PATH)/*.o
	@rm -f $(TARGET_OBJ_PATH)/*.obj
	@rm -f $(TARGET_BIN_PATH)/*.exp
	@rm -f $(TARGET_BIN_PATH)/*.html
	@rm -f $(TARGET_BIN_PATH)/*.lib
	@rm -f $(TARGET_BIN_PATH)/*.a
	@rm -f $(TARGET_BIN_PATH)/*.def
	@rm -f $(TARGET_BIN_PATH)/*.map
	@rm -f $(TARGET)
	@rm -f $(TARGET_DEPLOY)
	@rm -f $(TARGET_DOC_DEPLOY_FILE)
	@rm -f -r $(TARGET_DOC_PATH)
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target            : "$(TARGET_NAME)
	@echo "[CBI] -> Task			   : DELETE"
	@echo "[CBI] ->"
	@echo "[CBI] -> Delete .obj       : "$(TARGET_OBJ_PATH)
	@echo "[CBI] -> Delete .bin       : "$(TARGET_BIN_PATH)
	@echo "[CBI] -> Delete doc        : "$(TARGET_DOC_PATH)
	@echo "[CBI] ->"
	@echo "[CBI] -> Delete deploy     : "$(TARGET_DEPLOY)
	@echo "[CBI] -> Delete deploy doc : "$(TARGET_DOC_DEPLOY_FILE)
	@echo "=================================================================================="
	@echo ""

##########
# echo   #
##########

.PHONY: echoing
echoing:
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] ->"
	@echo "[CBI] -> Build     	  : "$(TARGET)
	@echo "[CBI] -> Deploy       : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	 	  : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	 	  : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 		  : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Task		  : Compiling-Linking" 
	@echo "=================================================================================="
	@echo ""
	@echo "[CBI] -> SRC AUX (Recursif) :"
	@echo "[CBI] ->"  
#@echo $(SRC_AUX)  
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(SRC_AUX))
	@echo "" 
	@echo "[CBI] -> CXXFLAGS (Partial) :"
	@echo "[CBI] ->"   
#@echo $(CXXFLAGS)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call not-containing,${OPTION_SEPARATOR}$(HEADER_OPTION),$(CXXFLAGS)))	
	@echo "" 
ifneq (${TARGET_MODE},STATIC_LIB)
	@echo "[CBI] -> LDFLAGS (Partial) :"
	@echo "[CBI] ->"  
#@echo $(LDFLAGS)
ifeq (${OS},Win)
ifeq (${COMPILATEUR},VISUAL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call not-containing,${LIB_PATH_SEPARATOR},$(call not-containing,.${EXTENSION_LIB},$(LDFLAGS)))) 
endif
ifeq (${COMPILATEUR},INTEL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call not-containing,${LIB_PATH_SEPARATOR},$(call not-containing,.${EXTENSION_LIB},$(LDFLAGS))))
endif
ifeq (${COMPILATEUR},MINGW)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call not-containing,-${LIB_FLAG_SEPARATOR},$(call not-containing,-${LIB_PATH_SEPARATOR},$(LDFLAGS)))) 
endif
else
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call not-containing,-${LIB_FLAG_SEPARATOR},$(call not-containing,-${LIB_PATH_SEPARATOR},$(LDFLAGS)))) 
endif
endif
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
# @ = diminue verbosite commande
#
# Attention : tabulation obligatoire avant commande dans rule!!
#
# http://www.gnu.org/software/make/manual/

#############################################
#       			 END     			    #
#############################################

endif#__TARGET_MK__
