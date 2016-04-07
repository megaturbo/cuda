#!/bin/bash
#
# Version:	0.0.3
#

set -e


#-----------------------------------------------
#		Input
#-----------------------------------------------

#nameproject
#namejar
#nameNative
#destinationJar
#CLASSPATH

#-----------------------------------------------
#		functions
#-----------------------------------------------

#
# Input :
#	NameApi
#	ProjectName
#	Path where to find sharedlib
#
# Output :
#
#	sharedLibName variable
#
# Exemple :
#
#	apiName=Bilat_Image_GL
#	projectName=03_F_Bilat_Image_GL
#	sharedLibPath=../../RELEASE/bin
#	Output = Bilat_Image_GL_003_gcc_x86 (par exemple)
#
function findSharedLibraryName()
	{
	local inputNameApi=$1
	local inputProjectName=$2
	local inputSharedLibraryDir=$3
	
	#echo "inputNameApi=$inputNameApi"
	#echo "inputProjectName=$inputProjectName"
	#echo "inputSharedLibraryDir=$inputSharedLibraryDir"
	
	local OS=$(uname)
	if [[ ${OS} == *Linux* ]] 
	then
		extension="so"
		suffix="lib"
	else
		extension="dll"
		suffix=""
	fi

	echo ""
	
	
	if [[ ${inputProjectName} == *Cuda* ]] 
	then
		echo "Try to find sharedLib ${suffix}${nameApi}*_cuda_*.${extension} in $inputSharedLibraryDir"
		listFiles=$(find ${inputSharedLibraryDir} -type f -and -regex ".*[a-zA-Z0-9_]+cuda[a-zA-Z0-9_]+\.${extension}$" -name "${suffix}${nameApi}*.${extension}"  -exec ls {} \;) 
	else
		echo "Try to find sharedLib ${suffix}${nameApi}*.${extension} in $inputSharedLibraryDir"
		listFiles=$(find ${inputSharedLibraryDir} -type f -and ! -regex ".*[a-zA-Z0-9_]+cuda[a-zA-Z0-9_]+\.${extension}$" -name "${suffix}${nameApi}*.${extension}"  -exec ls {} \;) 
	fi


	fileId=0
	for fileName in ${listFiles}
	do
		tabFile[$fileId]=$(basename $fileName)
		fileId=$((fileId+1))
	done
	fileCount=${#tabFile[@]} 
	 
	if [[ $fileCount = 1 ]]
	then
		sharedLibName=${tabFile[0]}	
		echo ""
		echo "found sharedlib = $sharedLibName"
		echo ""
	elif [[ $fileCount == 0 ]]
	then
		echo "No file found!"
		exit
	else
		# let user choose
		fileId=0
		maxFileId=$((fileCount-1))
		#Affichage des inputs
		echo ""
		echo "Choose file to link with ${inputNameApi}"
		echo ""
		echo "ID    SharedLib"
		echo ""
		# use for loop read all nameservers
		for (( i=0; i<${fileCount}; i++ ));
		do
  			echo "$i     ${tabFile[$i]}"
		done
		echo ""
		
		# boucle de saisi valide
		local fileIdChoice=-1
		while [ -z $fileIdChoice ] || [ $fileIdChoice -ge $fileCount ] || [ $fileIdChoice -lt 0 ]
		do
			read -p "Choose [ID] for this api in [0,$maxFileId] " fileIdChoice
		done
		#echo "Choosen ID = ${fileIdChoice}"
		sharedLibName=${tabFile[$fileIdChoice]}
		echo ""
		echo "you choose sharedlib = $sharedLibName"
		echo ""
	fi

	# removing suffix and prefix
	if [[ ${OS} == *Linux* ]] 
	then
		sharedLibName=${sharedLibName:3} #remove first 3 caractere ie 'lib' from libXXX.so
		#ok from bash version 4.2-alpha (-3) Cuda2 OK
		sharedLibName=${sharedLibName::-3} #remove last 3 caractere e '.so' from XXX.so
	else
		# Windows bash 3.82.90
		#sharedLibName=${sharedLibName::-4} #remove last 4 caractere e '.dll' from XXX.dll
		sharedLibName=${sharedLibName%?}
		sharedLibName=${sharedLibName%?}
		sharedLibName=${sharedLibName%?}
		sharedLibName=${sharedLibName%?}
	fi
	
	#echo "$sharedLibName"
	#return $sharedLibName #pas necesaire in variable global!
	}

#------------------------------------------------------------------------------------
#		Main
#------------------------------------------------------------------------------------



PROJECT_DIR=${ROOT_WORKSPACE}/${nameproject}
RELEASE_DIR=${ROOT_WORKSPACE}/RELEASE/bin

#-----------------------------------------------
#	Find sharedLibName in Release
#-----------------------------------------------

echo ""
echo "-------------------------------------------------------------"
echo " Jni : ${nameproject} : find sharedLib "
echo "-------------------------------------------------------------"
echo ""

findSharedLibraryName $nameApi $nameproject $RELEASE_DIR

#-----------------------------------------------
#		generate jar
#-----------------------------------------------

echo ""
echo "-------------------------------------------------------------"
echo " Jni : ${nameproject} : generate/install jar "
echo "-------------------------------------------------------------"
echo ""

echo "classpath = ${CLASSPATH}"
ant -Dbasedir=${PROJECT_DIR} -Dprojet.classpath=${CLASSPATH} -Dshared_lib.name=${sharedLibName} clean jar

echo ""
echo "-------------------------------------------------------------"
echo " Jni ${nameproject} : end"
echo "-------------------------------------------------------------"
echo ""

#------------------------------------------------------------------------------------
#		end
#------------------------------------------------------------------------------------


