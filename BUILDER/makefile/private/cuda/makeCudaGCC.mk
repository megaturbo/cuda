# Version 	: 0.0.8
# Date		: 01.08.2014
# Author 	: Cedric.Bilat@he-arc.ch
#
# See 		: OptionCompilateur.txt
#
# Hyp		: Application that must be in path
#				nvcc
#				make
#				g++
#				gcc
#


ifndef __MAKE_CUDA_GCC_MK__
__MAKE_CUDA_GCC_MK__=true

##############################################
#   			 Variables     				 #
##############################################

#SHELL=/bin/bash

machine:=${shell uname -m}
ifeq (${machine},x86_64)
	ARCHI_32_64:=x86_64
else
	ARCHI_32_64:=x86_32
endif

ifeq (${ARCH},arm) 
	ifeq ($(PLATFORME),jetson)
		ARCHI_32_64:=ARM_32
	endif
	
	ifeq ($(PLATFORME),kayla)
		ARCHI_32_64:=ARM_32
	endif
endif

########
# Path #
########

SRC_ROOT:=src
TARGET_OBJ:=${TARGET_PATH}/obj
TARGET_BIN:=${TARGET_PATH}/bin
TARGET_CUBIN:=${TARGET_PATH}/cubin

#synonime ameliorer
TARGET_BIN_PATH:=${TARGET_BIN}
TARGET_OBJ_PATH:=${TARGET_OBJ}

#TARGET_DEPLOY_PATH_BIN=${TARGET_DEPLOY_PATH}/bin
TARGET_DEPLOY_PATH_DOC=${TARGET_DEPLOY_PATH}/doc

########
# cpp #
########

CXX=g++

#a tester new
#override NVCCFLAGS+= -ccbin=g++#defaul gcc, g++? semble rien changer
# note : peremat pas d'enlever le filter-out ci-dessous
#@$(NVCC) $(NVCCFLAGS) -odir $(TARGET_OBJ) -Xcompiler ""$(filter-out -std=c++11,$(CXXFLAGS))"" -c $< -o $@

NAME_COMPILATEUR:=gcc_cuda

ifeq (${ARCH},arm)	
	NAME_COMPILATEUR_INSTALL:=gcc_cuda_arm
else
	NAME_COMPILATEUR_INSTALL:=gcc_cuda
endif

########
# Cuda #
########

NVCC := nvcc
PTXAS_FLAGS := -fastimul
OBJ_EXTENSION:=o
OPTION_SEPARATOR:=-#attention, end without space
LINK_FLAG_DLL:=-shared #with space ! pour nvcc
EXTENSION_LIB:=.a
EXTENSION_DLL:=.so
LIB_PREFIXE:=lib# example : libXXX.a
LIB_FLAG_SEPARATOR:=l#attention end without space!
LIB_PATH_SEPARATOR:=L#attention end with space!

##############
#TARGET_NAME #
##############

SCRIPT=${ROOT_MAKEFILE_PRIVATE_COMMON_SCRIPT}/cudaVersion.sh
NVCC_VERSION:=$(shell $(SCRIPT))
#${info "NVCC_VERSION"=${NVCC_VERSION}}

ifneq ($(ARCH),arm)
   TARGET_NAME:=${TARGET_NAME}_$(NAME_COMPILATEUR)_${NVCC_VERSION}_$(ARCHI_32_64)
else
   TARGET_NAME:=$(TARGET_NAME)_$(NAME_COMPILATEUR)_${NVCC_VERSION}_$(PLATFORME)_$(ARCHI_32_64)
endif

###########
#Extension#
###########

EXTENSION_OBJ:=o#
EXTENSION_LIB:=a#
EXTENSION_DLL:=so#
EXTENSION_EXE:=run#
# Note enstension sans le .

##########
# TARGET #
##########

#deja ci-dessus
#LIB_PREFIXE:=lib

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
	
	override NVCCLDFLAGS += $(LINK_FLAG_DLL)
	
	#Attention ARM : doit venir juste après le -Xcompiler!
    override CXXFLAGS := -fPIC -fvisibility=hidden ${CXXFLAGS}
  

endif

ifeq ($(TARGET_MODE),STATIC_LIB)
	TARGET:=${TARGET_LIB}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_LIB)
endif

#old

#ifeq ($(TARGET_MODE),SHARED_LIB)
#	override NVCCLDFLAGS+= $(LINK_FLAG_DLL) 
#	override CXXFLAGS += -fPIC -fvisibility=hidden
#	TARGET_NAME_FULL=lib$(TARGET_NAME).so
#endif
#
#ifeq ($(TARGET_MODE),EXE)
#	TARGET_NAME_FULL=$(TARGET_NAME).run
#endif

#TARGET:=$(TARGET_BIN)/$(TARGET_NAME_FULL)
#TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_FULL)

##########
#ARCHIVEUR#
###########

ifneq ($(ARCH),arm)
    AR:=ar
else
    AR:=arARM
endif

ARFLAGS=# pas= car valeur vaut rv avant sous windows ???
AR_OUT_FLAG:=-r #with espace important !

############
# Params   #
############

#ameliorer deja avant mais sans .
EXTENSION_LIB:=.a
EXTENSION_DLL:=.so
#LIB_PREFIX:=#pas de prefixe

############
#Set files #
############

SRC_PATH:=$(shell find $(SRC_ROOT) -type d)	

ifdef SRC_AUX
	SRC_PATH_AUX:=$(shell find $(SRC_AUX) -type d)
else
	SRC_PATH_AUX:=
endif

SRC_PATH_ALL:=$(SRC_PATH) $(SRC_PATH_AUX)
SRC_SO_FILES:=$(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.so))

# Libraries au format standard
#
#	Input : 
#		SRC_PATH_ALL
#	Output :
#		All files 
#			libXXX.a
#		 	libXXX.so
#			XXX.so
#		Excepted
#			XXX.a 
#	Goals :
#		Les .a prefixe par lib (example libXXX.a) seront donnee a GCC sous la forme -lXXX)
#		Alors que les YYY.a devront etre donner a GCC sous la forme YYY.a
#	Convention
#		Sous linux les .a standards sont libXXX.a
#		Les YYY.a sont non standards.
#
SRC_A_FILES_STANDART:=$(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/$(LIB_PREFIXE)*$(EXTENSION_LIB)))
override SRC_A_FILES_STANDART+=$(SRC_SO_FILES)

# Libraries au format non standard
#
#	Input : 
#		SRC_PATH_ALL
#	Output :
#		All files XXX.a (without libXXX.a)
#	Objectifs :
#		Les .a prefixer par lib (libXXX.a) seront donnee a GCC sous la forme -lXXX
#		Alors que les YYY.a devront etre donner a GCC sous la forme YYY.a avec la path complet (par exemple ../libs/YYY.a)
#
SRC_A_FILES_NOT_STANDARD:=$(foreach dir,$(SRC_PATH_ALL),$(filter-out $(dir)/$(LIB_PREFIXE)%$(EXTENSION_LIB),$(wildcard $(dir)/*$(EXTENSION_LIB))))

SRC_CPP_FILES := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.cpp)) 
SRC_C_FILES := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.c)) 
SRC_CU_FILES  := $(foreach dir,$(SRC_PATH_ALL),$(wildcard $(dir)/*.cu)) 

OBJ_FILES_CPP:= $(SRC_CPP_FILES:.cpp=.$(OBJ_EXTENSION))
OBJ_FILES_C:= $(SRC_C_FILES:.c=.$(OBJ_EXTENSION))
OBJ_FILES:= ${OBJ_FILES_CPP} ${OBJ_FILES_C}
OBJ_FILES:= $(addprefix $(TARGET_OBJ)/,$(notdir $(OBJ_FILES)))

CU_FILES := $(SRC_CU_FILES:.cu=.$(OBJ_EXTENSION))
CU_FILES := $(addprefix $(TARGET_OBJ)/,$(notdir $(CU_FILES))) 

OBJ_CU_FILES:=$(OBJ_FILES) $(CU_FILES)

#################
# PREPARE FLAGS	#
#################

#only fileName (./libs/libXXX.a ./libs/YYY.so -> lixXXX.a YYY.so)
LIB_FLAG:=$(notdir $(SRC_A_FILES_STANDART))

#removing prefix lib (libXXX.a libYYY.a libZZZ.so -> XXX.a YYY.a ZZZ.so)
LIB_FLAG:=$(subst $(LIB_PREFIXE),,$(LIB_FLAG))#remplace lib par rien

#Delete extension .a (XXX YYY)
LIB_FLAG:=$(LIB_FLAG:$(EXTENSION_LIB)=)

#Delete extension .so (AAA.so BBB.so -> AAA BBB)
LIB_FLAG:=$(LIB_FLAG:$(EXTENSION_DLL)=)

#ADDING user specified lib  (GL GLUT gomp ...)
override LIB_FLAG+=$(ADD_LIBRARY_FILES)

# Input :
#	list lib to delete example (AAA ZZZ)
#
#	before : LIB_FLAG (XXX YYY ZZZ)
#	after  : LIB_FLAG (XXX YYY) without ZZZ
override LIB_FLAG:=$(filter-out $(EXCLUDE_LIBRARY_FILES),$(LIB_FLAG))

#Adding Lib FLAG separator (XXX YYY -> -lXXX -lYYY)
override LIB_FLAG:=$(addprefix $(OPTION_SEPARATOR)$(LIB_FLAG_SEPARATOR),$(LIB_FLAG))
override LIB_FLAG+=$(CUDA_LIB_FILES_l) $(CULA_LIB_FILES_l)

#Adding Lib path FLAG separator -L (../AAA ./BBB -> -L../AAA _L./BBB)
LIB_PATH:=$(foreach dir,$(SRC_PATH_ALL),$(dir $(wildcard $(dir)/*.so)))#dir extract directory of file,  $(wildcard $(dir)/*.h)=> take file.h if exist
override LIB_PATH:=$(call uniq,${LIB_PATH})
#LIB_PATH_FLAG+=$(CUDA_LIB_L) $(CULA_LIB_L)#old
#LIB_PATH_FLAG:=$(addprefix $(OPTION_SEPARATOR)$(LIB_PATH_SEPARATOR),$(SRC_PATH_ALL))#old
LIB_PATH_FLAG:=$(addprefix $(OPTION_SEPARATOR)$(LIB_PATH_SEPARATOR),$(LIB_PATH))

#Adding Include FLAG separator
override INC_PATH:=${INC_PATH} $(foreach dir,$(SRC_PATH_ALL),$(dir $(wildcard $(dir)/*.h)))#dir extract directory of file,  $(wildcard $(dir)/*.h)=> take file.h if exist
override INC_PATH:=$(call uniq,${INC_PATH})
#${info "INC_PATH= "${INC_PATH}}#print immediately
#SRC_HEADER_I := $(addprefix  $(OPTION_SEPARATOR)I,$(SRC_PATH_ALL))#old
SRC_HEADER_I := $(addprefix  $(OPTION_SEPARATOR)I,$(INC_PATH))
#ALL_HEADERS_I:= $(SRC_HEADER_I)#old 


#Injection variable in .cpp code (VAR1 VAR2 -> -DVAR1 -DVAR2)
CODE_DEFINE_VARIABLES_D:= $(addprefix  -D,$(CODE_DEFINE_VARIABLES))

#override NVCCFLAGS   += $(ALL_HEADERS_I)#old 
override NVCCFLAGS   += $(SRC_HEADER_I) 
override NVCCLDFLAGS += $(LIB_PATH_FLAG) $(LIB_FLAG) $(SRC_A_FILES_NOT_STANDARD)
override CXXFLAGS += $(CODE_DEFINE_VARIABLES_D)

##########
# securite #
##########

#Directory search path (use implicit in rules)
VPATH := $(SRC_PATH_ALL)

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
	override PATH:=${PATH}${separateurPath}${API_BIN_FORMATTER}	
	export ${PATH}
else
	override LD_LIBRARY_PATH:=${LD_LIBRARY_PATH}${separateurPath}${API_BIN_FORMATTER}
	export ${LD_LIBRARY_PATH}#fixme semble pas marcher
endif

########
#Optimisation #
########

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/optimisation.mk

########
#arm #
########

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/cudaGCC_arm.mk

##########
# exclude #
##########

override CXXFLAGS:=$(filter-out $(CXXFLAGS_EXCLUDE),$(CXXFLAGS))
override NVCCFLAGS:=$(filter-out $(NVCCFLAGS_EXCLUDE),$(NVCCFLAGS))

#https://www.gnu.org/software/make/manual/make.html#Functions

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
	#override AR_OUT_FLAG:=$(call uniq,${AR_OUT_FLAG})
	
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
	#override AR_OUT_FLAG:=$(strip ${AR_OUT_FLAG})#pas pour gcc (enleve espace apres -r)

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

#######
#boost bug#
#######

#boost static lib: lpthread doit etre a la fin
#http://stackoverflow.com/questions/19901934/strange-linking-error-dso-missing-from-command-line

ifdef BOOST_VERSION
	#override LDFLAGS:=$(sort $(LDFLAGS))#sort met pthread a la fin par rapport a boost
	override LDFLAGS+= -lpthread	
endif
#${info "LDFLAGS= "${LDFLAGS}}#print immediatel

##########
# bug #
##########

#Adding " " around CXXFLAGS and CXXLDFLAGS, otherwise we can't specifie more than one options !
override CXXFLAGS:=" $(CXXFLAGS) " 
override CXXLDFLAGS:=" $(CXXLDFLAGS) "

###########
#chrono#
###########

override TIME_START_S:=$(shell date +%s)

##############################################
#      			  Rules 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/rules_linux.mk

##############################################
#      			  TARGET 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CUDA}/targets_linux.mk

#############################################
#       			 END     			    #
#############################################


endif#__MAKE_CUDA_GCC_MK__



