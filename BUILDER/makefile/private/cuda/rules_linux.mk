ifndef _RULES_LINUX_CUDA_MK__
_RULES_LINUX_CUDA_MK__=true

##############################################
#      			  Rules 				     #
##############################################

TITLE:=$(TARGET_NAME)

################
#.o->.run      #
################

$(TARGET) : $(OBJ_CU_FILES)
	@echo ""
	@echo "[CBI] -> Linking to   : "$(TARGET)
	@echo ""
	@echo "[CBI] -> Library Link :"
	@echo "[CBI] ->"  
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(call containing,-l,$(NVCCLDFLAGS)))
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/print.sh  $(sort $(call containing,-l,$(CXXLDFLAGS)))
	@echo "" 
	@$(NVCC) $(NVCCLDFLAGS) -Xlinker $(CXXLDFLAGS) $^ -o $(TARGET)
	@echo ""
	@echo "=================================================================================="
	@echo "[CBI] -> Target Name  : "$(TARGET_NAME)
	@echo "[CBI] -> Location     : "$(TARGET)
	@echo "[CBI] -> Deploy 	  : "$(TARGET_DEPLOY_PATH_BIN)
	@echo "[CBI] ->"
	@echo "[CBI] -> Type	 	  : "$(TARGET_MODE)
	@echo "[CBI] -> Arch	 	  : "$(ARCHI_32_64)
	@echo "[CBI] -> OS	 	      : "$(OS)
	@echo "[CBI] -> User	 	  : "$(USER)
	@echo "[CBI] ->"
	@echo "[CBI] -> Compilateur  : ${CXX}) && ${NVCC}"
	@echo "[CBI] -> Task		  : End Compiling-Linking !" 
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/time.sh "[CBI] -> Time		  :" ${TIME_START_S}
	@echo "=================================================================================="
	@echo ""

# -o =outfile
# tabulation obligatoire before @

################
#  .o->.lib    #
################

${TARGET_LIB}:$(OBJ_CU_FILES)
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
	@echo "[CBI] -> Compilateur  : ${CXX}) && ${NVCC}"
	@echo "[CBI] -> Task	      : End Compiling-Archive !" 
	@${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/time.sh "[CBI] -> Time		  :" ${TIME_START_S} 
	@echo "=================================================================================="
	@echo ""

################
#   .cpp->.o   #
################

$(TARGET_OBJ)/%.$(OBJ_EXTENSION) :%.cpp
ifdef ARM
	@echo "[${TITLE}] -> g++ARM compiling .cpp : "$<  	
else
	@echo "[${TITLE}] -> ${CXX} compiling .cpp : "$<
endif
	@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler $(CXXFLAGS) -o $@ -c $<

# -c = compilation
# -o =outfile

################
#   .c->.o   #
################

$(TARGET_OBJ)/%.$(OBJ_EXTENSION) :%.c
ifdef ARM
	@echo "[${TITLE}] -> g++ARM compiling .cpp : "$<  	
else
	@echo "[${TITLE}] -> ${CXX} compiling .cpp : "$<
endif
	@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler $(CXXFLAGS) -o $@ -c $<

# -c = compilation
# -o =outfile

################
#   .cu->.o   #
################

#pour jetson
CXXFLAGS_ADAPTED:=$(filter-out -std=c++0x,$(CXXFLAGS))
#pour cuda1 cuda2
override CXXFLAGS_ADAPTED:=$(filter-out -std=c++11,$(CXXFLAGS_ADAPTED))

$(TARGET_OBJ)/%.$(OBJ_EXTENSION) :%.cu
	@echo "[${TITLE}] -> ${NVCC} compiling .cu : "$<
#@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler ""$(filter-out -std=c++0x,$(CXXFLAGS))"" -c $< -o $@
#@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler ""$(filter-out -std=c++11,$(CXXFLAGS))"" -c $< -o $@
	@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler $(CXXFLAGS_ADAPTED) -c $< -o $@
##Adding "" "" around final CXXFLAGS, to keep one " " around final CXXFLAGS , in order to can specifie more than one options !

# -c = compilation
# -o =outfile

#############################################
#       			 END     			    #
#############################################

endif#_RULES_LINUX_CUDA_MK__
