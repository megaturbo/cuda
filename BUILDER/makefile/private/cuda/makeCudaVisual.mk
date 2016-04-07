# Version 	: 0.0.8
# Date		: 01.08.2014
# Author 	: Cedric.Bilat@he-arc.ch
#
# See 		: OptionCompilateur.txt
#
# Hyp		: Application that must be in path
#				nvcc
#				mingw32-make
#				cl
#
# 			:  Environement Variables must be set
#
#				ARCHI_32_64			:	32 or 64

ifndef __MAKE_VISUAL_CUDA_MK__
__MAKE_VISUAL_CUDA_MK__=true


##############################################
#   			 Variables     				 #
##############################################


########
# Path #
########

SRC_ROOT:=src
TARGET_OBJ:=${TARGET_PATH}/obj
TARGET_BIN:= ${TARGET_PATH}/bin
TARGET_CUBIN:=${TARGET_PATH}/cubin

#synonime ameliorer
TARGET_BIN_PATH:=${TARGET_BIN}
TARGET_OBJ_PATH:=${TARGET_OBJ}

#TARGET_DEPLOY_PATH_BIN=${TARGET_DEPLOY_PATH}/bin
TARGET_DEPLOY_PATH_DOC=${TARGET_DEPLOY_PATH}/doc

########
# cpp #
########

CXX=cl

NAME_COMPILATEUR:=visual_cuda
NAME_COMPILATEUR_INSTALL:=visual_cuda

########
# Cuda #
########

NVCC := nvcc
PTXAS_FLAGS := -fastimul
OBJ_EXTENSION:=obj
OPTION_SEPARATOR:=-#attention, end without space
LINK_FLAG_DLL:=-shared#attention,end without space

########
#32/64 #
########

#plus necessaire
#ifeq ($(ARCHI_32_64),64)
	# override NVCCFLAGS+= -m64#default -m64 #dans public
	#override CXXLDFLAGS+= /MACHINE:X64 #Deprecated! 	#En plus posait probl�me de guillement (� la d�finition de CXXLDFLAGS)
#endif

##############
#TARGET_NAME #
##############

#obtain NVCC_VERSION
SCRIPT=${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/cudaVersion.sh
NVCC_VERSION:=$(shell $(SCRIPT))

TARGET_NAME:=${TARGET_NAME}_$(NAME_COMPILATEUR)_$(NVCC_VERSION)_$(ARCHI_32_64)

#############
# Extension  #
#############

EXTENSION_OBJ:=obj#
EXTENSION_LIB:=lib#
EXTENSION_DLL:=dll#
EXTENSION_EXE:=exe#
# Note enstension sans le .

##########
# TARGET #
##########

LIB_PREFIXE:=#rien

TARGET_NAME_EXE:=$(TARGET_NAME).${EXTENSION_EXE}
TARGET_NAME_DLL:=${LIB_PREFIXE}$(TARGET_NAME).$(EXTENSION_DLL)
TARGET_NAME_LIB:=${LIB_PREFIXE}$(TARGET_NAME).${EXTENSION_LIB}

TARGET_EXE:=${TARGET_BIN_PATH}/$(TARGET_NAME_EXE)
TARGET_DLL:=${TARGET_BIN_PATH}/$(TARGET_NAME_DLL)
TARGET_LIB:=${TARGET_BIN_PATH}/$(TARGET_NAME_LIB)
#TARGET_OBJ:=$(addprefix $(TARGET_OBJ_PATH)/,$(notdir $(OBJ_FILES)))

#Selection de la target en fonction TARGET_MODE
ifeq ($(TARGET_MODE),EXE)
	TARGET:=${TARGET_EXE}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_EXE)
endif

ifeq ($(TARGET_MODE),SHARED_LIB)
	TARGET:=${TARGET_DLL}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_DLL)
	TARGET_NAME_LIB_DLL:=$(TARGET_BIN_PATH)/${TARGET_NAME}.lib
	
	override NVCCLDFLAGS += $(LINK_FLAG_DLL)
endif

ifeq ($(TARGET_MODE),STATIC_LIB)
	TARGET:=${TARGET_LIB}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_LIB)
endif


###########
#Extension#
###########

#ifeq ($(TARGET_MODE),SHARED_LIB)
#	override NVCCLDFLAGS+= $(LINK_FLAG_DLL) 
#	TARGET_NAME_FULL=$(TARGET_NAME).dll
#endif

#ifeq ($(TARGET_MODE),EXE)
#	TARGET_NAME_FULL=$(TARGET_NAME).exe
#endif

#TARGET:=$(TARGET_BIN)/$(TARGET_NAME_FULL)
#TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_FULL)

##########
#ARCHIVEUR#
###########

AR:=lib
ARFLAGS=# pas= car valeur vaut rv avant sous windows ???
AR_OUT_FLAG:=/OUT:#Sans espace

############
# Params   #
############

#ameliorer deja avant mais sans .
EXTENSION_LIB:=.lib
EXTENSION_DLL:=.dll
#LIB_PREFIX:=#pas de prefixe

############
#Set files #
############

#Hyp : Shell sh
SRC_PATH:=$(shell find $(SRC_ROOT) -type d)	
ifdef SRC_AUX
	SRC_PATH_AUX:=$(shell find $(SRC_AUX) -type d)
else
	SRC_PATH_AUX:=
endif

SRC_PATH_ALL:=$(SRC_PATH) $(SRC_PATH_AUX)

SRC_CPP_FILES := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.cpp)) 
SRC_C_FILES := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.c)) 
SRC_CU_FILES  := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.cu)) 
SRC_LIB_FILES := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.lib)) $(ADD_LIBRARY_FILES)

#################
# PREPARE FLAGS #
#################

#ifneq (, $(findstring openmp,$(CXXFLAGS)))#findstring return vide si openmp pas trouver!
#	ADD_LIBRARY_FILES+=libiomp5md.lib 

#Delete extension .lib
SRC_LIB_FILES:= $(SRC_LIB_FILES:$(EXTENSION_LIB)=)

SRC_LIB_FILES_l:= $(addprefix $(OPTION_SEPARATOR)l,$(notdir $(SRC_LIB_FILES))) 
#ALL_LIB_FILES_l:= $(CUDA_LIB_FILES_l) $(CULA_LIB_FILES_l) $(SRC_LIB_FILES_l)
ALL_LIB_FILES_l:= $(SRC_LIB_FILES_l)

LIB_PATH:=$(foreach dir,$(SRC_PATH_ALL),$(dir $(wildcard $(dir)/*.lib)))#dir extract directory of file,  $(wildcard $(dir)/*.h)=> take file.h if exist
override LIB_PATH:=$(call uniq,${LIB_PATH})
#SRC_LIB_L:=$(addprefix $(OPTION_SEPARATOR)L,$(SRC_PATH_ALL))#old
SRC_LIB_L:=$(addprefix $(OPTION_SEPARATOR)L,$(LIB_PATH))

#ALL_LIB_L:=$(SRC_LIB_L) $(CUDA_LIB_L) $(CULA_LIB_L)
ALL_LIB_L:=$(SRC_LIB_L)


override INC_PATH:=${INC_PATH} $(foreach dir,$(SRC_PATH_ALL),$(dir $(wildcard $(dir)/*.h)))#dir extract directory of file,  $(wildcard $(dir)/*.h)=> take file.h if exist
override INC_PATH:=$(call uniq,${INC_PATH})
#${info "INC_PATH= "${INC_PATH}}#print immediately
#SRC_HEADER_I := $(addprefix  $(OPTION_SEPARATOR)I,$(SRC_PATH_ALL))#old
SRC_HEADER_I := $(addprefix  $(OPTION_SEPARATOR)I,$(INC_PATH))
#ALL_HEADERS_I:= $(SRC_HEADER_I)#old 

OBJ_FILES_CPP:= $(SRC_CPP_FILES:.cpp=.$(OBJ_EXTENSION))
OBJ_FILES_C:= $(SRC_C_FILES:.c=.$(OBJ_EXTENSION))
OBJ_FILES:= ${OBJ_FILES_CPP} ${OBJ_FILES_C}
OBJ_FILES:= $(addprefix $(TARGET_OBJ)/,$(notdir $(OBJ_FILES)))

CU_FILES := $(SRC_CU_FILES:.cu=.$(OBJ_EXTENSION))
CU_FILES := $(addprefix $(TARGET_OBJ)/,$(notdir $(CU_FILES))) 

OBJ_CU_FILES:=$(OBJ_FILES) $(CU_FILES)

#Injection variable in .cpp code (VAR1 VAR2 -> -DVAR1 -DVAR2)
CODE_DEFINE_VARIABLES_D:= $(addprefix  -D,$(CODE_DEFINE_VARIABLES))

#override NVCCFLAGS   += $(ALL_HEADERS_I)#old 
override NVCCFLAGS   += $(SRC_HEADER_I) 
override NVCCLDFLAGS += $(ALL_LIB_L) $(ALL_LIB_FILES_l)
override CXXFLAGS += $(CODE_DEFINE_VARIABLES_D)

ifneq (, $(findstring /MD,$(CXXFLAGS)))#findstring return vide si /MD pas trouver!
	override CXXLDFLAGS+= /NODEFAULTLIB:LIBCMT
endif

#Adding " " around CXXFLAGS and CXXLDFLAGS, otherwise we can't specifie more than one options !
#override CXXFLAGS:=" $(CXXFLAGS) " 
#override CXXLDFLAGS:=" $(CXXLDFLAGS) "
#plus tard apres optimisation

##########
# securite #
##########

#Directory search path(use implicit in rules)
VPATH := $(SRC_PATH_ALL)

########
#Optimisation #
########

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/optimisation.mk

##########
# exclude #
##########

override NVCCFLAGS:=$(filter-out $(NVCCFLAGS_EXCLUDE),$(NVCCFLAGS))
override CXXFLAGS:=$(filter-out $(CXXFLAGS_EXCLUDE),$(CXXFLAGS))

#https://www.gnu.org/software/make/manual/make.html#Functions

##########
# runtime #
##########

space:= #ne suufit pas ajoutre espaca, mais += le fait!
space+=#

ifeq (${OS},Win)
	separateurPath:=;#	
else
	separateurPath:=:#
endif

API_BIN_FORMATTER:=$(subst ${space},${separateurPath},${API_BIN})

ifeq (${OS},Win)
	override PATH:=${API_BIN_FORMATTER}${separateurPath}${PATH}#
	export ${PATH}#
else
	override LD_LIBRARY_PATH:=${LD_LIBRARY_PATH}${separateurPath}${API_BIN_FORMATTER}#
	export ${LD_LIBRARY_PATH}#fixme semble pas marcher
endif

######
#-Xcompiler
######

#ok avec cette transformation
#ok sans cette transformation

#avant : aaa bbb ccc
#apres : aaa,bbb,ccc

#remove space
#override CXXFLAGS:=$(strip ${CXXFLAGS})
# espace -> virgule
#VIRGULE=,
#override CXXFLAGS:=$(subst ${ESPACE},${VIRGULE},${CXXFLAGS})
#${info CXXFLAGS=[${CXXFLAGS}]}

##########
# unicitye #
##########

UNICITY=true

ifdef UNICITY

	override CXXFLAGS:=$(call uniq,${CXXFLAGS})
	override CXXLDFLAGS:=$(call uniq,${CXXLDFLAGS})
	#override NVCCFLAGS:=$(call uniq,${NVCCFLAGS}) pas possible car enleve -gencode
	override NVCCLDFLAGS:=$(call uniq,${NVCCLDFLAGS})
	override ARFLAGS:=$(call uniq,${ARFLAGS})
	#override AR_OUT_FLAG:=$(call uniq,${AR_OUT_FLAG})#met espace apres /out, pas pour visual/intel

endif#UNICITY

##########
# remove space #
##########

#let a minimum of one space
REMOVE_SPACE=true

ifdef REMOVE_SPACE

	override CXXFLAGS:=$(strip ${CXXFLAGS})
	override CXXLDFLAGS:=$(strip ${CXXLDFLAGS})
	override NVCCLDFLAGS:=$(strip ${NVCCLDFLAGS})
	override NVCCFLAGS:=$(strip ${NVCCFLAGS})
	override ARFLAGS:=$(strip ${ARFLAGS})
	#override AR_OUT_FLAG:=$(strip ${AR_OUT_FLAG}) #pas pour mingw car enleve espace apres -r

	#override CXXFLAGS:=$(subst $(space),,$(CXXFLAGS))

endif#REMOVE_SPACE

##########
# debug #
##########

#${info "CXXFLAGS    = "${CXXFLAGS}}#print immediately
#${info "CXXLDFLAGS  = "${CXXLDFLAGS}}#print immediatel
#${info "NVCCFLAGS   = "${NVCCFLAGS}}#print immediatel
#${info "NVCCLDFLAGS = "${NVCCLDFLAGS}}#print immediatel
#${info "ARFLAGS= "${ARFLAGS}}#print immediatel
#${info "AR_OUT_FLAG= "${AR_OUT_FLAG}}#print immediatel


##########
# bug #
##########

#Adding " " around CXXFLAGS and CXXLDFLAGS, otherwise we can't specifie more than one options !
override CXXFLAGS:=" $(CXXFLAGS) " 
override CXXLDFLAGS:=" $(CXXLDFLAGS) "

###########
# chrono  #
###########

override TIME_START_S:=$(shell date +%s)

##############################################
#      			  Rules 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/rules_win.mk

##############################################
#      			  TARGET 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/targets_win.mk

#############################################
#       			 END     			    #
#############################################

endif#__MAKE_VISUAL_CUDA_MK__
