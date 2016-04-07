#!/bin/bash
#
# version	: 0.0.1
# author	: cedric.bilat@he-arc.ch


# ---------------------------------------
#		Init
#----------------------------------------

set -e

# ---------------------------------------
#		Projets
#----------------------------------------

projet1=BilatTools_CPP
projet2=BilatTools_Cuda
projet3=BilatTools_Cuda_Image
projet4=BilatTools_Image
projet5=BilatTools_OMP
projet6=BilatTools_OpenCV

# ---------------------------------------
#		List Projets (export)
#----------------------------------------

export listProjet="    $projet1                   $projet4 $projet5 $projet6"
export listProjetCuda="$projet1 $projet2 $projet3          $projet5 $projet6"
export listProjetJNI=""

#todo pas traiter
export listProjetLinux=""

# listProjet     : inc pour projet non cuda
# listProjetCuda : inc pour projet cuda
# Attention : exclusif! Raison pour laquelle un meme projet peut apparaitre dans les deux listes!

# ---------------------------------------
#		end
#----------------------------------------
