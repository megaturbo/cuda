#!/bin/bash
#
# version	: 0.0.1
# author	: cedric.bilat@he-arc.ch

# --------------------------------------------------------------------------------------------------------------
#		Tools (private)
# --------------------------------------------------------------------------------------------------------------

function purgeSymlink()
	{
	local DESTINATION=$1

	echo ""
	echo "----------------------------------------------------------------"
	echo "Purge : $DESTINATION"
	echo "----------------------------------------------------------------"
	echo "WARNING : Delete $DESTINATION"
	echo -n "PRESS y to confirm > "
	read input

	#ls $DESTINATION

	if [[ $input != y ]]
	then
		echo ""	
		echo "Abord"
		echo ""	
		exit
	fi
		rm -r -f $DESTINATION
		mkdir -p $DESTINATION
	}

#undewr windows 8.1, required to be admin	
function makeSymlink()
	{
	local FILE=$1
	local FILE_DESTINATION=$2
	local OS=$3

	if [[ ${OS} == *Linux* ]] 
	then
		ln -s $FILE $FILE_DESTINATION
	else
		
		#avant: a/b/c
		#apres: a\b\c
		#http://www.unix.com/unix-for-dummies-questions-and-answers/139404-replace-slash-space.html
		#replace / by \
		#sed s/replace_this//with_this/g
		local fileDos=$(echo $FILE | sed 's/\//\\/g')
		local fileDestinationDos=$(echo $FILE_DESTINATION | sed 's/\//\\/g')

		#http://www.patpro.net/blog/index.php/2006/04/07/20-manipulations-sur-les-variables-dans-bash/
		#avant: \C\
		#apres: C:\
		fileDos=${fileDos/\\C/C:}
		fileDestinationDos=${fileDestinationDos/\\C/C:}
		
		#echo "fileDos="$fileDos
		#echo "fileDestinationDos="$fileDestinationDos

		#http://superuser.com/questions/124679/how-do-i-create-a-link-in-windows-7-home-premium-as-a-regular-user/125981#125981
		#link ci-dessus semble pas marcher
		#under windows 8.1, required to be admin: lancer console admin: ok	
		local executable="MKLINK $fileDestinationDos $fileDos"

		cmd.exe /c "$executable"
		
	fi
	}

# --------------------------------------------------------------------------------------------------------------
#		symlinkRecursifVersionExtentionApi (public) 				[Attention : voir aussi symlinkRecursif]
# --------------------------------------------------------------------------------------------------------------

function symlinkRecursifVersionExtentionApi()
	{
		
	# ---------------------------------------
	#		Inputs
	#----------------------------------------
	
	#example
	
	#SOURCE=/opt/api/cbi
	#DESTINATION=/home/bilat/temp/inc
	#VERSION=002
	#EXTENSION=h
	
	if [ $# -ne 4 ]
	then
		
		echo ""
		echo "Missing 3 input: SOURCE VERSION DESTINATION"
		echo "Abord"
		echo ""
	
		echo "$@"
		
		exit
	
	else
		local SOURCE=$1
		local VERSION=$2
		local DESTINATION=$3	
		local EXTENSION=$4
	fi
	
	#echo "SOURCE=$SOURCE"
	#echo "VERSION=$VERSION"
	#echo "DESTINATION=$DESTINATION"
	
	# ---------------------------------------
	#		Init
	#----------------------------------------
	
	echo ""
	echo "----------------------------------------------------------------"
	echo "Symlink : $SOURCE --> $DESTINATION"
	echo "----------------------------------------------------------------"
	echo ""
	
	# ---------------------------------------
	#		Main
	#----------------------------------------
	
	echo "Files found (Please wait) : "
	echo ""
	
	OS=$(uname)
	
	#http://alvinalexander.com/unix/edu/examples/find.shtml
	
	#lent (inside files)
	#for file in $(find $SOURCE -type f -name "*.${EXTENSION}" | grep $VERSION)
	
	#fast (todo: lancer exec commande toute de suite de symlink)
	for file in $(find $SOURCE -name "*.${EXTENSION}" | grep $VERSION)
	do
	
		local namefile="${file##*/}"
		
		echo "$file"
		#echo "namefile="$namefile
		
		#ls $DESTINATION
		#ls $DESTINATION | grep $namefile
		
		fileDestination=$DESTINATION/$namefile
	
		if [ -f $fileDestination ]
		then
			echo "Warning : symlink $fileDestination already exist for $file" 
		else
			makeSymlink $file $fileDestination $OS
		fi	
	done
	
	echo ""
	echo "$DESTINATION :"
	echo ""
	ls $DESTINATION
	echo ""
	
	}

# --------------------------------------------------------------------------------------------------------------
#		symlinkRecursif (public) 	[Attention : voir aussi symlinkRecursifVersionExtentionApi] 
# --------------------------------------------------------------------------------------------------------------

# SOURCE_FILE_EXTENSION="*.h"
# SOURCE_FILE_EXTENSION="*.so" (linux)
function symlinkRecursif()
	{
		
	# ---------------------------------------
	#		Inputs
	#----------------------------------------
	
	#example
	
	#SOURCE=/opt/api/cbi
	#DESTINATION=/home/bilat/temp/inc
	
	if [ $# -ne 3 ]
	then
		
		echo ""
		echo "Missing 2 input: SOURCE DESTINATION SOURCE_FILE_EXTENSION(*.h or *.so)"
		echo "Abord"
		echo ""
	
		echo "$@"
		
		exit
	
	else
		local SOURCE=$1
		local DESTINATION=$2	
		local SOURCE_FILE_EXTENSION=$3
	fi
	
	# ---------------------------------------
	#		Init
	#----------------------------------------
	
	echo ""
	echo "----------------------------------------------------------------"
	echo "Symlink : $SOURCE --> $DESTINATION"
	echo "----------------------------------------------------------------"
	echo ""
	
	# ---------------------------------------
	#		Main
	#----------------------------------------
	
	echo "Files found (Please wait) : "
	echo ""
	
	OS=$(uname)
		
	#http://alvinalexander.com/unix/edu/examples/find.shtml
	
	#lent : inside files	
	#for file in $(find $SOURCE -type f -name "*.h")
	#for file in $(find $SOURCE -type f -name ${SOURCE_FILE_EXTENSION})
	
	#fast:
	for file in $(find $SOURCE -name ${SOURCE_FILE_EXTENSION})
	do
	
		local namefile="${file##*/}"
		
		echo "$file"
		#echo "namefile="$namefile
		
		#ls $DESTINATION
		#ls $DESTINATION | grep $namefile
		
		fileDestination=$DESTINATION/$namefile
	
		if [ -f $fileDestination ]
		then
			echo "Warning : symlink $fileDestination already exist for $file" 
		else
			makeSymlink $file $fileDestination $OS
		fi	
	done
	
	echo ""
	echo "$DESTINATION :"
	echo ""
	ls $DESTINATION
	echo ""
	
	}

# ---------------------------------------
#		end
#----------------------------------------
