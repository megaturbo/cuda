ifndef _RULES_MK__
_RULES_MK__=true

##############################################
#      			  Rules 				     #
##############################################

# tabulation obligatoire before @

TITLE:=$(TARGET_NAME)

################
#   .o->.exe   #
################

${TARGET_EXE}:$(TARGET_OBJ)
	@echo ""
	@echo "[CBI] -> Linking to   : "$(TARGET)
	@echo ""
	@echo "[CBI] -> Library Link :"
ifeq (${OS},Win)
ifeq (${COMPILATEUR},VISUAL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,.${EXTENSION_LIB},$(LDFLAGS))) 
endif
ifeq (${COMPILATEUR},INTEL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,.${EXTENSION_LIB},$(LDFLAGS)))
endif
ifeq (${COMPILATEUR},MINGW)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,-${LIB_FLAG_SEPARATOR},$(LDFLAGS))) 
endif
else
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,-l,$(LDFLAGS))) 
endif
	@$(CXX) $(OUT_FILE_LINK)${TARGET_EXE} $^ $(LDFLAGS)
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] -> Location     : "$(TARGET)
	@echo "[CBI] -> Deploy 	  : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	 	  : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	 	  : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 		  : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Compilateur  : ${COMPILATEUR} (${CXX})"    
	@echo "[CBI] -> Task	      : End Compiling-Linking !" 
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/time.sh "[CBI] -> Time		  :" ${TIME_START_S}
	@echo "=================================================================================="
	@echo ""
	
################
#   .o->.dll   #
################

${TARGET_DLL}:$(TARGET_OBJ)
	@echo ""
	@echo "[$(TITLE)] -> Linking to   : "$(TARGET)
	@echo ""
	@echo "[$(TITLE)] -> Library Link :"
	@echo ""
#@echo ${LDFLAGS}
ifeq (${OS},Win)
ifeq (${COMPILATEUR},VISUAL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,.${EXTENSION_LIB},$(LDFLAGS)))
endif
ifeq (${COMPILATEUR},INTEL)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,.${EXTENSION_LIB},$(LDFLAGS))) 
endif
ifeq (${COMPILATEUR},MINGW)
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,-${LIB_FLAG_SEPARATOR},$(LDFLAGS)))
endif
else
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh $(sort $(call containing,-l,$(LDFLAGS))) 
endif
	@echo ""
	@$(CXX) $(OUT_FILE_LINK)${TARGET_DLL} $^ $(LDFLAGS)
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] -> Location     : "$(TARGET)
	@echo "[CBI] -> Deploy 	  : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	 	  : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	 	  : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 		  : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Compilateur  : ${COMPILATEUR} (${CXX})"     
	@echo "[CBI] -> Task	      : End Compiling-Linking !" 
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/time.sh "[CBI] -> Time		  :" ${TIME_START_S}
	@echo "=================================================================================="
	@echo ""
	
################
#  .o->.lib    #
################

${TARGET_LIB}:$(TARGET_OBJ)
	@echo ""
	@${AR} ${AR_OUT_FLAG}${TARGET_LIB} ${ARFLAGS} $^
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] -> Location     : "$(TARGET)
	@echo "[CBI] -> Deploy 	  : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	 	  : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	 	  : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 		  : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Compilateur  : ${COMPILATEUR} (${CXX})" 
	@echo "[CBI] -> Task	      : End Compiling-Archive !" 
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/time.sh "[CBI] -> Time		  :" ${TIME_START_S}
	@echo "=================================================================================="
	@echo ""
	
################
#   .cpp->.o   #
################

$(TARGET_OBJ_PATH)/%.$(EXTENSION_OBJ):%.cpp  
#intelWin et visual affiche deja file
ifeq (${COMPILATEUR},MINGW)
	@echo "[$(TITLE)] -> ${CXX} compiling .cpp : "$<
endif
ifeq (${COMPILATEUR},g++)
	@echo "[$(TITLE)] -> ${CXX} compiling .cpp : "$<
endif
ifeq (${COMPILATEUR},INTEL)
ifeq (${OS},Linux)
	@echo "[$(TITLE)] -> ${CXX} compiling .cpp : "$<
endif
endif
	@$(CXX) $(CXXFLAGS) $(OUT_FILE_COMPILE)$@ -c  $< 
	
# -c = compilation

################
#   .c->.o   #
################

$(TARGET_OBJ_PATH)/%.$(EXTENSION_OBJ):%.c  
#intelWin et visual affiche deja file
ifeq (${COMPILATEUR},MINGW)
	@echo "[$(TITLE)] -> ${CXX} compiling .c   : "$<
endif
ifeq (${COMPILATEUR},g++)
	@echo "[$(TITLE)] -> ${CXX} compiling .c   : "$<
endif
ifeq (${COMPILATEUR},INTEL)
ifeq (${OS},Linux)
	@echo "[$(TITLE)] -> ${CXX} compiling .cpp : "$<
endif
endif
	@$(CXX) $(CXXFLAGS) $(OUT_FILE_COMPILE)$@ -c  $< 
	
# -c = compilation

#############################################
#       			 END     			    #
#############################################

endif#_RULES_MK__
