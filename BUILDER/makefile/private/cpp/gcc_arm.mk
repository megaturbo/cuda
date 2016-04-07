# Version 	: 0.0.7
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch


ifndef __GCC_ARM_MK__
__GCC_ARM_MK__=true

##############################################
#   			 Variables     				 #
##############################################

########
#arm #
########

ifeq (${ARCH},arm)	

	ARM=true
	
	# rpath-link : start
	ifdef RPATH_LINK
	
		# see comment cudaGCC_arm.mk
		ESPACE:=#
		ESPACE+=#astice de guere
	
		override RPATH_LINK:=$(strip ${RPATH_LINK})#replaces each internal sequence of one or more whitespace characters with a single space
		override RPATH_LINK:=$(subst ${ESPACE},:,${RPATH_LINK})# ESPACE -> :
	
		override RPATH_LINK:= -rpath-link=${RPATH_LINK}#-rpath-link pourrait apparaitre plusieurs fois.

		override LDFLAGS+= -Xlinker ${RPATH_LINK}

	endif
	#rpath-link : end
	
	override CXXFLAGS+= ${ARM_CXXFLAGS}
	
endif

#####################
# 		Target 		#
#####################

########
# Copy #
########

.PHONY: toARM
toARM:
	@echo ""
	@echo "[CBI] -> Copy to ${PLATFORME}(${PLATFORME_IP}) : "$(TARGET_DEPLOY)
	@echo ""
	@scp $(TARGET_DEPLOY) ${PLATFORME_USER}@${PLATFORME_IP}:${PLATFORME_BIN}
	@echo ""
	@echo "[CBI] -> Success!"
	@echo ""
#va define in public folder

########
# execute #
########

.PHONY: runARM
runARM:
	@echo ""
	@echo "[CBI] -> Run on ${PLATFORME}(${PLATFORME_IP}) : $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${PLATFORME_USER}@${PLATFORME_IP} cd ${PLATFORME_BIN} && cbirt ./$(TARGET_NAME).run"
	@echo ""
	@ssh -X ${PLATFORME_USER}@${PLATFORME_IP} "cd ${PLATFORME_BIN} && cbirt ./$(TARGET_NAME).run"
	@echo ""
#va define in public folder

########
# kill #
########

.PHONY: killARM	
killARM:
	@echo ""
	@echo "[CBI] -> Killing on ${PLATFORME}(${PLATFORME_IP}) : $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${PLATFORME_USER}@${PLATFORME_IP} killall ${TARGET_NAME_EXE}"
	@echo ""
	@ssh -X ${PLATFORME_USER}@${PLATFORME_IP} killall ${TARGET_NAME_EXE}
	@echo ""

#############################################
#       			 END     			    #
#############################################

endif#__GCC_ARM_MK__

