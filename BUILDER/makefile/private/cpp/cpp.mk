# Version 	: 0.0.7
# Date		: 04.03.2014
# Author 	: Cedric.Bilat@he-arc.ch
#
# See 		: OptionCompilateur.txt
#
# Hyp		: Application that must be in path
#				nvcc
#				make
#				g++
#				gcc

##############################################
#    				Temp	       			 #
##############################################

# Hyp		: Environement Variables must be set
#
#				ARCHI_32_64	: 32 or 64

ifndef __CPP_MK__
__CPP_MK__=true

##############################################
#   			 Variables     				 #
##############################################

#OS:=$(shell uname)
#MACHINE:=${shell uname -m}



########
#setfile #
########

OBJ_FILES_CPP:= $(SRC_CPP_FILES:.cpp=.$(EXTENSION_OBJ))
OBJ_FILES_C:= $(SRC_C_FILES:.c=.$(EXTENSION_OBJ))

OBJ_FILES:= ${OBJ_FILES_CPP} ${OBJ_FILES_C}

##########
# TARGET #
##########

TARGET_NAME_EXE:=$(TARGET_NAME).${EXTENSION_EXE}
TARGET_NAME_DLL:=${LIB_PREFIXE}$(TARGET_NAME).$(EXTENSION_DLL)
TARGET_NAME_LIB:=${LIB_PREFIXE}$(TARGET_NAME).${EXTENSION_LIB}

TARGET_EXE:=${TARGET_BIN_PATH}/$(TARGET_NAME_EXE)
TARGET_DLL:=${TARGET_BIN_PATH}/$(TARGET_NAME_DLL)
TARGET_LIB:=${TARGET_BIN_PATH}/$(TARGET_NAME_LIB)
TARGET_OBJ:=$(addprefix $(TARGET_OBJ_PATH)/,$(notdir $(OBJ_FILES)))

#Selection de la target en fonction TARGET_MODE
ifeq ($(TARGET_MODE),EXE)
	TARGET:=${TARGET_EXE}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_EXE)
endif

ifeq ($(TARGET_MODE),SHARED_LIB)
	TARGET:=${TARGET_DLL}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_DLL)
	override LDFLAGS += $(LINK_FLAG_DLL)
endif

ifeq ($(TARGET_MODE),STATIC_LIB)
	TARGET:=${TARGET_LIB}
	TARGET_DEPLOY:=$(TARGET_DEPLOY_PATH_BIN)/$(TARGET_NAME_LIB)
endif

##########
# RESSOURCES #
##########

ifeq (,$(findstring $(RESOURCES_PATH),$(wildcard $(RESOURCES_PATH) )))
	nbFileRessources:=0
else
	nbFileRessources:=$(shell ls $(RESOURCES_PATH) | wc -l )
endif

##########
# securite #
##########

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
	override PATH:=${API_BIN_FORMATTER}${separateurPath}${PATH}#
	export ${PATH}#
	
else
	override LD_LIBRARY_PATH:=${LD_LIBRARY_PATH}${separateurPath}${API_BIN_FORMATTER}#
	export ${LD_LIBRARY_PATH}#fixme semble pas marcher
endif



########
#optimisation #
########

include ${ROOT_MAKEFILE_PRIVATE_CPP}/optimisation.mk

########
#arm #
########

include ${ROOT_MAKEFILE_PRIVATE_CPP}/gcc_arm.mk

##########
# exclude #
##########

override CXXFLAGS:=$(filter-out $(CXXFLAGS_EXCLUDE),$(CXXFLAGS))
#https://www.gnu.org/software/make/manual/make.html#Functions

##########
# unicitye #
##########

UNICITY=true

ifdef UNICITY

	override CXXFLAGS:=$(call uniq,${CXXFLAGS})
	override CXXLDFLAGS:=$(call uniq,${CXXLDFLAGS})
	override LDFLAGS:=$(call uniq,${LDFLAGS})
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
	override LDFLAGS:=$(strip ${LDFLAGS})
	override ARFLAGS:=$(strip ${ARFLAGS})
	#override AR_OUT_FLAG:=$(strip ${AR_OUT_FLAG}) #pas pour mingw car enleve espace apres -r

	#override CXXFLAGS:=$(subst $(space),,$(CXXFLAGS))

endif#REMOVE_SPACE

##########
# debug #
##########

#${info "CXXFLAGS= "${CXXFLAGS}}#print immediately
#${info "CXXLDFLAGS"= ${CXXLDFLAGS}}#print immediatel
#${info "LDFLAGS"= ${LDFLAGS}}#print immediatel
#${info "ARFLAGS= "${ARFLAGS}}#print immediatel
#${info "AR_OUT_FLAG= "${AR_OUT_FLAG}}#print immediatel

#######
#boost bug #
#######

#boost static lib: lpthread doit etre a la fin
#http://stackoverflow.com/questions/19901934/strange-linking-error-dso-missing-from-command-line

ifeq ($(OS),Linux)
ifeq ($(NAME_COMPILATEUR),gcc)
ifdef BOOST_VERSION
	#override LDFLAGS:=$(sort $(LDFLAGS))#sort met pthread a la fin par rapport a boost
	override LDFLAGS+= -lpthread	
endif
endif
endif
#${info "LDFLAGS= "${LDFLAGS}}#print immediatel

##########
# chrono #
##########

override TIME_START_S:=$(shell date +%s)

##############################################
#      			  Rules 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CPP}/rules.mk

##############################################
#      			  TARGET 				     #
##############################################

include ${ROOT_MAKEFILE_PRIVATE_CPP}/targets.mk

endif#__CPP_MK__

