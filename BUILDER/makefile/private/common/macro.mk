# Version 	: 0.0.6
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch

ifndef __MACRO_MK__
__MACRO_MK__=true


#############################################
#       			 MACRO     			    #
#############################################


#http://stackoverflow.com/questions/12315834/makefile-how-to-apply-an-equivalent-to-filter-on-multiple-wildcards
not-containing = $(foreach v,$2,$(if $(findstring $1,$v),,$v))
containing = $(foreach v,$2,$(if $(findstring $1,$v),$v))

#example
#LIST := a_old_tt x_old_da a_new_da q_ty_we
#LIST_OLD := $(call containing,old,$(LIST))
#LIST_NOT_OLD := $(call not-containing,old,$(LIST))

#http://stackoverflow.com/questions/16144115/makefile-remove-duplicate-words-without-sorting

#v1: linux : ko : win : ok
#define uniq =
#	$(eval seen :=)
#	$(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
#	${seen}
#endef
#exemple
#w := z z x x y c x
#w:=$(call uniq,${w})
#w:=$(strip ${w})
#${info ${w}}#print immediately ww

#v2 : linux ok : win ok
uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))
#exemple
#w := z z x x y c x
#w:=$(call uniq,${w})
#${info ${w}}#print immediately ww


#############################################
#       			 END     			    #
#############################################

endif#__MACRO_MK___
