# Version 	: 0.0.7
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch

ifndef __CUDA_GCC_ARM_MK__
__CUDA_GCC_ARM_MK__=true

##############################################
#   			 Variables     				 #
##############################################

########
#arm #
########

ifeq (${ARCH},arm)	

	ARM=true

	# Context: 
	#		liba.so depend de libb.so
	#		on link que liba.so avec
	#			-la
	# Probleme:
	#		linker pas content car trouve pas libb.so
	#		warning ou carrement refuse linker!
	#
	# Solution1:
	#		Mettre le folder contenant libb.so dans -rpathlink
	#
	# Solution2:
	#		Flag pour ignorer les dependances seconadires
	#
	#			--allow-shlib-undefined
	#
	#		Observation: Cette technique met beuacoup de warning dans la console et semble �craser la pr�c�dente le rapth-link
	#
	# Conclusion
	#
	#		Solution1 du rpath-link retenu
	#		Utile seulement pour OpenCV en mode gpu cuda, car dans ce cas les .so opencv utilise les .so de cuda (cudart.so) par exemple
	# link: 
	#		http://ftp.gnu.org/pub/old-gnu/Manuals/ld-2.9.1/html_node/ld_3.html
	#
	
	#rpath-link : start
	ifdef RPATH_LINK
		ESPACE:=#
		ESPACE+=#astuce de guere
	
		override RPATH_LINK:=$(strip ${RPATH_LINK})#replaces each internal sequence of one or more whitespace characters with a single space
		override RPATH_LINK:=$(subst ${ESPACE},:,${RPATH_LINK})# ESPACE -> :

		#RPATH_LINK_PATH:=${RPATH_LINK_PATH}:/opt/arm/${PLATFORME}/arm-linux-gnueabihf/usr_lib#ici pour garantir unicite, si manque warning only, pas error
		#RPATH_LINK_PATH:=${RPATH_LINK_PATH}:/opt/arm/${PLATFORME}/arm-linux-gnueabihf/lib#ici pour garantir unicite, si manque warning only, pas error
		#L_RPATH_LINK:= -L$(subst :, -L,${RPATH_LINK_PATH})# on met aussi RPATH_LINK dans L	
		
		override RPATH_LINK:= -rpath-link=${RPATH_LINK}#-rpath-link pourrait apparaitre plusieurs fois
		
		override CXXLDFLAGS+= ${RPATH_LINK}
	endif
	#rpath-link : end
		
	override ARMFLAGS+= -ccbin g++ARM 
	override ARMFLAGS+= -target-cpu-arch ARM 
	override ARMFLAGS+= -m32 	 # jetson
	
	override NVCCFLAGS+= ${ARMFLAGS} 
	override NVCCLDFLAGS+= ${ARMFLAGS} 
	
	override NVCCFLAGS_EXCLUDE+= -m64# jetson
	override CXXFLAGS_EXCLUDE+= -std=c++11 #provisoire cuda6, e enlever cuda7
	override CXXFLAGS+= -std=c++0x # jetson asu lieu de -std=c++11
		 
	override CXXFLAGS+= ${ARM_CXXFLAGS}
else
	
	ifeq (${DEBUG},false)	 
		override CXXFLAGS+= ${X86_CXX_OPTIMISATION}
	endif
	
endif

ifeq (${DEBUG},false)	
	override CXXFLAGS+= ${CXX_OPTIMISATION}
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

endif#__OCUDA_GCC_ARM_MK__

