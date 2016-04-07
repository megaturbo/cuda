ifndef __CLEAN_ALL__
__CLEAN_ALL__=true

##############################################
#      			  TARGET 				     #
##############################################

##########
# cleanALL #
##########

# -v verbose
# -r recursif
# -f pas d'erreur si file existe pas
#rm -rf #serait recursif (dangereux!!)

.PHONY: cleanDeploy
cleanDeploy:
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.lib
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.so
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.dll
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.run
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.exe
	@rm -f ${TARGET_DEPLOY_PATH_BIN}/*.a
	@rm -f ${TARGET_DEPLOY_PATH_DOC}/*.gz
	

.PHONY: cleanTemp
cleanTemp:
	@rm -f -r ${TARGET_PATH_ROOT}
	
.PHONY: cleanAll	
cleanAll: cleanTitleStart cleanDeploy cleanTemp cleanTitleEnd
	@echo ""
	

.PHONY: cleanTitleStart
cleanTitleStart:
	@echo "=================================================================================="
	@echo "[CBI] -> Delete            : "${TARGET_DEPLOY_PATH_BIN}"/*"
	@echo "[CBI] -> Delete            : "${TARGET_DEPLOY_PATH_DOC}"/*"
	@echo "[CBI] -> Delete            : "${TARGET_PATH_ROOT}
	@echo "=================================================================================="
	@echo ""
	@echo "[CBI] -> Please wait ..."
	@echo "[CBI] -> Deleting    ..."
	@echo ""

.PHONY: cleanTitleEnd
cleanTitleEnd:
	@echo "=================================================================================="
	@echo "[CBI] -> Delete            : finished!"
	@echo "=================================================================================="
	

#############################################
#       			 END     			    #
#############################################

endif#__CLEAN_ALL__
