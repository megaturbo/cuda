#!/bin/bash
#
# Version:	0.0.2
#

set -e

#-----------------------------------------------
#		Input
#-----------------------------------------------

#$1: compilateur

#linux
#	gcc
#	intellinux
#
#windows
#	visual
#	intelwin
#	mingw

TIME_START_S=$(date +%s)

#-----------------------------------------------
#		init
#-----------------------------------------------

source ./workspace_classification.sh

#-----------------------------------------------
#		compilateur
#-----------------------------------------------

if [ -z $1 ]
then

	if [ ${OS} == "Linux" ]
	then
		echo "[ERROR] : .sh : input missing : gcc or intellinux"		
	 
	elif [ ${OS} == "Win" ]
	then
		echo "[ERROR] : .sh : input missing : visual or intelwin or mingw"
	fi
	
	exit
fi

compilateur=$1

#-----------------------------------------------
#		architecture
#-----------------------------------------------

if [ -z $2 ]
then
	if [ ${OS} == "Linux" ]
	then
		ARCH=X86_64		
	fi
else
	ARCH=$2
fi

#-----------------------------------------------
#		clean
#-----------------------------------------------

#cd ./BUILDER

#if [ ${OS} == "Linux" ] && [ ${ARCH} == "ARM" ] 
#then
			
	#${MAKE_GCC} arm cleanAll
			
#elif [ ${OS} == "Linux" ] && [ ${ARCH} == "X86_64" ]
#then
			
	#${MAKE_GCC} cleanAll
			
#elif [ ${OS} == "Win" ]
#then
		
	#cmd.exe //c ${MAKE_VISUAL} cleanAll
#fi 

#cd ..

#-----------------------------------------------
#		compile
#-----------------------------------------------

IS_PARALLEL=true

if [ ${IS_PARALLEL} == "true" ]
then
	TARGET=jall
else
	TARGET=all
fi

echo ""
echo ""
echo ""
echo ""
echo "--------------------------------------------------------------------------------------------------------"
echo "[Compiling Workspace]"
echo ""
echo " Workspace       = "${workspaceRoot}
echo " Compilateur     = "${compilateur}
echo " State           = Please wait ..."
echo "--------------------------------------------------------------------------------------------------------"


for cuda in ${setCUDA}
	do
		echo ""
		echo ""	
		echo ""
		echo ""	
		echo "----------------------------------------------------------------------------------"
		echo "[Compiling Cuda Project]"
		echo ""	
		echo "Project           =" ${cuda}		
		echo "Workspace         =" $(pwd)
		echo "Compilateur       = g++ && nvcc"	
		echo "----------------------------------------------------------------------------------"		
		cd ./${cuda}
		
		if [ ${OS} == "Linux" ] && [ ${ARCH} == "ARM" ] 
		then
			
			${MAKE_CUDA_GCC} arm $TARGET
		
		elif [ ${OS} == "Linux" ] && [ ${ARCH} == "X86_64" ]
		then
			
			${MAKE_CUDA_GCC} $TARGET
			
		elif [ ${OS} == "Linux" ] 
		then
		
			${MAKE_CUDA_GCC} $TARGET
			
		elif [ ${OS} == "Win" ]
		then
		
			cmd.exe //c ${MAKE_CUDA_VISUAL} $TARGET
			#echo "fixme tenir compte compilateur"
		fi
		
		cd ..
	done

for cpp in ${setCPP}
	do
		echo ""
		echo ""	
		echo ""
		echo ""		
		echo "----------------------------------------------------------------------------------"
		echo "[Compiling CPP Project]"	
		echo ""		
		echo "Project           =" ${cpp}		
		echo "Workspace         =" $(pwd)
		echo "Compilateur       = ${compilateur}"
		echo "----------------------------------------------------------------------------------"		
		cd ./${cpp}
		
		if [ ${OS} == "Linux" ]
		then

			if  [ ${compilateur} == "gcc" ] && [ ${ARCH} == "ARM" ]
			then
			
				${MAKE_GCC} arm $TARGET

			elif [ ${compilateur} == "gcc" ] && [ ${ARCH} == "X86_64" ]
			then
			
				${MAKE_GCC}  $TARGET
				
			elif [ ${compilateur} == "gcc" ] 
			then
			
				${MAKE_GCC}  $TARGET
				
			elif [ ${compilateur} == "intellinux" ] && [ ${ARCH} == "X86_64" ]
			then
			
				${MAKE_INTEL_LINUX} $TARGET  
				
			fi

		elif [ ${OS} == "Win" ]
		then

			if  [ ${compilateur} == "visual" ]
			then
			
				cmd.exe //c ${MAKE_VISUAL} $TARGET 

			elif [ ${compilateur} == "intelwin" ]
			then
			
				cmd.exe //c ${MAKE_INTEL_WIN} $TARGET  

			elif [ ${compilateur} == "mingw" ] && ! [[ ${cpp} == *JNI* ]]
			then
				
				cmd.exe //c ${MAKE_MINGW} $TARGET  
				
			fi
			
		fi

		cd ..
	done

for intel in ${setIntel}
	do
		echo ""
		echo ""	
		echo ""
		echo ""		
		echo "----------------------------------------------------------------------------------"
		echo "[Compiling CPP-intel only Project]"	
		echo ""		
		echo "Project           =" ${cpp}		
		echo "Workspace         =" $(pwd)
		echo "Compilateur       = icpp"
		echo "----------------------------------------------------------------------------------"		
		cd ./${intel}
	
		if [ ${OS} == "Linux" ] && [ ${ARCH} == "X86_64" ]
		then
		
			${MAKE_INTEL_LINUX} $TARGET  
		
		elif [ ${OS} == "Win" ]
		then
		
			cmd.exe //c ${MAKE_INTEL_WIN} $TARGET
			
		fi

		cd ..
	done

TIME_STOP_S=$(date +%s)

echo ""
echo ""	
echo ""
echo ""	
echo "--------------------------------------------------------------------------------------------------------"
echo "[Compiling Workspace]"
echo ""
echo " Workspace   = "${workspaceRoot}
echo " State       = Success!"
echo " Delta Time  = $(($TIME_STOP_S - $TIME_START_S)) (s)"
echo "--------------------------------------------------------------------------------------------------------"
echo ""
echo ""	
echo ""
echo ""

#-----------------------------------------------
#		end
#-----------------------------------------------


