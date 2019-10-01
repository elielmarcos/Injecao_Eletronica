#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source.c delay.c lcd.c setup.c adc.c eeprom.c teclado.c beep.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source.p1 ${OBJECTDIR}/delay.p1 ${OBJECTDIR}/lcd.p1 ${OBJECTDIR}/setup.p1 ${OBJECTDIR}/adc.p1 ${OBJECTDIR}/eeprom.p1 ${OBJECTDIR}/teclado.p1 ${OBJECTDIR}/beep.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/source.p1.d ${OBJECTDIR}/delay.p1.d ${OBJECTDIR}/lcd.p1.d ${OBJECTDIR}/setup.p1.d ${OBJECTDIR}/adc.p1.d ${OBJECTDIR}/eeprom.p1.d ${OBJECTDIR}/teclado.p1.d ${OBJECTDIR}/beep.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source.p1 ${OBJECTDIR}/delay.p1 ${OBJECTDIR}/lcd.p1 ${OBJECTDIR}/setup.p1 ${OBJECTDIR}/adc.p1 ${OBJECTDIR}/eeprom.p1 ${OBJECTDIR}/teclado.p1 ${OBJECTDIR}/beep.p1

# Source Files
SOURCEFILES=source.c delay.c lcd.c setup.c adc.c eeprom.c teclado.c beep.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source.p1: source.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 source.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  source.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/source.p1: > ${OBJECTDIR}/source.p1.d
	@cat ${OBJECTDIR}/source.dep >> ${OBJECTDIR}/source.p1.d
	@${FIXDEPS} "${OBJECTDIR}/source.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/delay.p1: delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/delay.p1: > ${OBJECTDIR}/delay.p1.d
	@cat ${OBJECTDIR}/delay.dep >> ${OBJECTDIR}/delay.p1.d
	@${FIXDEPS} "${OBJECTDIR}/delay.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lcd.p1: lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 lcd.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  lcd.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/lcd.p1: > ${OBJECTDIR}/lcd.p1.d
	@cat ${OBJECTDIR}/lcd.dep >> ${OBJECTDIR}/lcd.p1.d
	@${FIXDEPS} "${OBJECTDIR}/lcd.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/setup.p1: setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 setup.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  setup.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/setup.p1: > ${OBJECTDIR}/setup.p1.d
	@cat ${OBJECTDIR}/setup.dep >> ${OBJECTDIR}/setup.p1.d
	@${FIXDEPS} "${OBJECTDIR}/setup.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/adc.p1: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/adc.p1: > ${OBJECTDIR}/adc.p1.d
	@cat ${OBJECTDIR}/adc.dep >> ${OBJECTDIR}/adc.p1.d
	@${FIXDEPS} "${OBJECTDIR}/adc.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/eeprom.p1: eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 eeprom.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  eeprom.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/eeprom.p1: > ${OBJECTDIR}/eeprom.p1.d
	@cat ${OBJECTDIR}/eeprom.dep >> ${OBJECTDIR}/eeprom.p1.d
	@${FIXDEPS} "${OBJECTDIR}/eeprom.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/teclado.p1: teclado.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 teclado.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  teclado.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/teclado.p1: > ${OBJECTDIR}/teclado.p1.d
	@cat ${OBJECTDIR}/teclado.dep >> ${OBJECTDIR}/teclado.p1.d
	@${FIXDEPS} "${OBJECTDIR}/teclado.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/beep.p1: beep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 beep.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  beep.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/beep.p1: > ${OBJECTDIR}/beep.p1.d
	@cat ${OBJECTDIR}/beep.dep >> ${OBJECTDIR}/beep.p1.d
	@${FIXDEPS} "${OBJECTDIR}/beep.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/source.p1: source.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 source.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  source.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/source.p1: > ${OBJECTDIR}/source.p1.d
	@cat ${OBJECTDIR}/source.dep >> ${OBJECTDIR}/source.p1.d
	@${FIXDEPS} "${OBJECTDIR}/source.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/delay.p1: delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  delay.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/delay.p1: > ${OBJECTDIR}/delay.p1.d
	@cat ${OBJECTDIR}/delay.dep >> ${OBJECTDIR}/delay.p1.d
	@${FIXDEPS} "${OBJECTDIR}/delay.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lcd.p1: lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 lcd.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  lcd.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/lcd.p1: > ${OBJECTDIR}/lcd.p1.d
	@cat ${OBJECTDIR}/lcd.dep >> ${OBJECTDIR}/lcd.p1.d
	@${FIXDEPS} "${OBJECTDIR}/lcd.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/setup.p1: setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 setup.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  setup.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/setup.p1: > ${OBJECTDIR}/setup.p1.d
	@cat ${OBJECTDIR}/setup.dep >> ${OBJECTDIR}/setup.p1.d
	@${FIXDEPS} "${OBJECTDIR}/setup.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/adc.p1: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/adc.p1: > ${OBJECTDIR}/adc.p1.d
	@cat ${OBJECTDIR}/adc.dep >> ${OBJECTDIR}/adc.p1.d
	@${FIXDEPS} "${OBJECTDIR}/adc.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/eeprom.p1: eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 eeprom.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  eeprom.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/eeprom.p1: > ${OBJECTDIR}/eeprom.p1.d
	@cat ${OBJECTDIR}/eeprom.dep >> ${OBJECTDIR}/eeprom.p1.d
	@${FIXDEPS} "${OBJECTDIR}/eeprom.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/teclado.p1: teclado.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 teclado.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  teclado.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/teclado.p1: > ${OBJECTDIR}/teclado.p1.d
	@cat ${OBJECTDIR}/teclado.dep >> ${OBJECTDIR}/teclado.p1.d
	@${FIXDEPS} "${OBJECTDIR}/teclado.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/beep.p1: beep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	${MP_CC} --pass1 beep.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@${MP_CC} --scandep  beep.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}" -N31 --warn=0 --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 --cp=16 -Blarge --double=24  --mode=pro -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  
	@echo ${OBJECTDIR}/beep.p1: > ${OBJECTDIR}/beep.p1.d
	@cat ${OBJECTDIR}/beep.dep >> ${OBJECTDIR}/beep.p1.d
	@${FIXDEPS} "${OBJECTDIR}/beep.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -D__DEBUG --debugger=realice -N31 --warn=0 --cp=16 -Blarge --double=24  --mode=pro  --output=default,-inhx032 -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" ${OBJECTFILES_QUOTED_IF_SPACED}    
	${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.hex
else
dist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/Injecao_Elet_firmware.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,+clib,-plib --opt=all,+asm,-asmfile,+speed,-space,9 -N31 --warn=0 --cp=16 -Blarge --double=24  --mode=pro  --output=default,-inhx032 -g --asmlist "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" ${OBJECTFILES_QUOTED_IF_SPACED}    
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
