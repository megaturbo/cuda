#!/bin/bash
#
# Version:	0.0.2
#

set -e

#-----------------------------------------------
#		Input
#-----------------------------------------------

#rien

#------------------------------------------------------------------------------------
#		Path
#------------------------------------------------------------------------------------

export ROOT_WORKSPACE=../../..

PUBLIC_DATA=../../public
PUBLIC_DATA_POST_INSTALL=${PUBLIC_DATA}/postinstall

#------------------------------------------------------------------------------------
#		main
#------------------------------------------------------------------------------------

#-----------------------------------------------
#		os
#-----------------------------------------------

OS=$(uname)

if [[ ${OS} == *Linux* ]] 
then
		COMPILATEUR_MAISON=gcc
else
		COMPILATEUR_MAISON=visual	
fi

#-----------------------------------------------
#		compilateur
#-----------------------------------------------

if [[ ${OS} == *Linux* ]] 
then
	COMPILATEUR_LIST="gcc intel"
else
	COMPILATEUR_LIST="visual intel mingw"
fi

#Note: projet passe en modue cuda automatiqument(si projet name contient cuda)
#	   Mais projet cuda compiler alors autant de fois que de compilateur, ce qui est inutile!

#echo "OS               = "${OS}
#echo "COMPILATEUR_LIST = "${COMPILATEUR_LIST}

#-----------------------------------------------
#		clean
#-----------------------------------------------

./apibuilderPack.sh ${COMPILATEUR_MAISON} uninstall

#-----------------------------------------------
#		Inc (only once)
#-----------------------------------------------

./apibuilderPack.sh ${COMPILATEUR_MAISON} installTitle installInc

#avant build car projet2 a besoin include projet1 maybe!

#-----------------------------------------------
#		build
#-----------------------------------------------

#echo "ARCH=$ARCH"

IS_PARALLEL=true

if [ ${IS_PARALLEL} == "true" ]
then
	TARGET=jall
else
	TARGET=all
fi

#if provisoire, build arm et non arm en meme temps
if [[ $ARCH != "arm" ]]
then
	for COMPILATEUR in ${COMPILATEUR_LIST}
	do
		echo "-------------------------------------------------------------------------------------"	
		echo "COMPILATEUR="${COMPILATEUR}
		echo "-------------------------------------------------------------------------------------"
		#read p
	
		#Warning : apibuilderPack.sh : processing all project of packs with the compilateur of the loop
		#			=> all installTitle installBin 		doit etre fait en meme temps, car un projet du pack peut dependre d'un autre projet du pack
		#
		
		# clean tous les projest du packs 
		./apibuilderPack.sh ${COMPILATEUR} clean
		
		# build tous les projets du packs (installTitle installBin sur meme ligne cf remarque ci-dessus)
		./apibuilderPack.sh ${COMPILATEUR} $TARGET installTitle installBin
	done
else
	source ./arm.sh
fi

#-----------------------------------------------
#		src (only once)
#-----------------------------------------------

./apibuilderPack.sh ${COMPILATEUR_MAISON} installTitle installSrc

#-----------------------------------------------
#		doc (only once)
#-----------------------------------------------

./apibuilderPack.sh ${COMPILATEUR_MAISON} doc installTitle installDoc

#------------------------------------------------------------------------------------
#		post custom run
#------------------------------------------------------------------------------------

echo ""
echo "-------------------------------------------------------------------------------------"
echo " PostInstall"
echo "-------------------------------------------------------------------------------------"
echo ""

pushd  ${PUBLIC_DATA_POST_INSTALL}
source ./postinstall.sh
popd

#------------------------------------------------------------------------------------
#		end
#------------------------------------------------------------------------------------


