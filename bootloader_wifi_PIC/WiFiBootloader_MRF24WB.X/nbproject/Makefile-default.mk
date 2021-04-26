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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=../src/rtc/daylight.c ../src/rtc/rtc.c ../src/rtc/rtcconverter.c ../src/BootLoader.c ../src/Framework.c ../src/NVMem.c ../src/EthernetTasks.c ../src/Tick.c ../src/stack_task.c ../src/UDP.c ../src/dhcp_client.c ../src/ARP.c ../src/Helpers.c ../src/dns_client.c ../src/nbns.c ../src/drv_wifi_mac.c ../src/drv_wifi_raw.c ../src/drv_wifi_com.c ../src/Delay.c ../src/drv_wifi_eint.c ../src/drv_wifi_debug_strings.c ../src/drv_wifi_spi.c ../src/drv_wifi_power_save.c ../src/announce.c ../src/drv_wifi_mgmt_msg.c ../src/drv_wifi_event_handler.c ../src/drv_wifi_config.c ../src/drv_wifi_connection_algorithm.c ../src/drv_wifi_connection_manager.c ../src/drv_wifi_pbkdf2.c ../src/drv_wifi_init.c ../src/drv_wifi_param_msg.c ../src/IP.c ../src/icmp.c ../src/tcp.c ../src/uart.c ../src/drv_wifi_connection_profile.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c ../src/big_int_helper_pic32.S c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c ../src/smtp.c ../src/smtp_demo.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/659867239/daylight.o ${OBJECTDIR}/_ext/659867239/rtc.o ${OBJECTDIR}/_ext/659867239/rtcconverter.o ${OBJECTDIR}/_ext/1360937237/BootLoader.o ${OBJECTDIR}/_ext/1360937237/Framework.o ${OBJECTDIR}/_ext/1360937237/NVMem.o ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o ${OBJECTDIR}/_ext/1360937237/Tick.o ${OBJECTDIR}/_ext/1360937237/stack_task.o ${OBJECTDIR}/_ext/1360937237/UDP.o ${OBJECTDIR}/_ext/1360937237/dhcp_client.o ${OBJECTDIR}/_ext/1360937237/ARP.o ${OBJECTDIR}/_ext/1360937237/Helpers.o ${OBJECTDIR}/_ext/1360937237/dns_client.o ${OBJECTDIR}/_ext/1360937237/nbns.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o ${OBJECTDIR}/_ext/1360937237/Delay.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o ${OBJECTDIR}/_ext/1360937237/announce.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o ${OBJECTDIR}/_ext/1360937237/IP.o ${OBJECTDIR}/_ext/1360937237/icmp.o ${OBJECTDIR}/_ext/1360937237/tcp.o ${OBJECTDIR}/_ext/1360937237/uart.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o ${OBJECTDIR}/_ext/252762716/sntp.o ${OBJECTDIR}/_ext/252762716/ssl.o ${OBJECTDIR}/_ext/252762716/random.o ${OBJECTDIR}/_ext/252762716/hashes.o ${OBJECTDIR}/_ext/252762716/rsa.o ${OBJECTDIR}/_ext/252762716/big_int.o ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o ${OBJECTDIR}/_ext/252762716/arc4.o ${OBJECTDIR}/_ext/1360937237/smtp.o ${OBJECTDIR}/_ext/1360937237/smtp_demo.o ${OBJECTDIR}/_ext/252762716/http2.o ${OBJECTDIR}/_ext/252762716/mpfs2.o ${OBJECTDIR}/_ext/252762716/custom_http_app.o ${OBJECTDIR}/_ext/252762716/mpfs_img2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/659867239/daylight.o.d ${OBJECTDIR}/_ext/659867239/rtc.o.d ${OBJECTDIR}/_ext/659867239/rtcconverter.o.d ${OBJECTDIR}/_ext/1360937237/BootLoader.o.d ${OBJECTDIR}/_ext/1360937237/Framework.o.d ${OBJECTDIR}/_ext/1360937237/NVMem.o.d ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d ${OBJECTDIR}/_ext/1360937237/Tick.o.d ${OBJECTDIR}/_ext/1360937237/stack_task.o.d ${OBJECTDIR}/_ext/1360937237/UDP.o.d ${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d ${OBJECTDIR}/_ext/1360937237/ARP.o.d ${OBJECTDIR}/_ext/1360937237/Helpers.o.d ${OBJECTDIR}/_ext/1360937237/dns_client.o.d ${OBJECTDIR}/_ext/1360937237/nbns.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d ${OBJECTDIR}/_ext/1360937237/Delay.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d ${OBJECTDIR}/_ext/1360937237/announce.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d ${OBJECTDIR}/_ext/1360937237/IP.o.d ${OBJECTDIR}/_ext/1360937237/icmp.o.d ${OBJECTDIR}/_ext/1360937237/tcp.o.d ${OBJECTDIR}/_ext/1360937237/uart.o.d ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d ${OBJECTDIR}/_ext/252762716/sntp.o.d ${OBJECTDIR}/_ext/252762716/ssl.o.d ${OBJECTDIR}/_ext/252762716/random.o.d ${OBJECTDIR}/_ext/252762716/hashes.o.d ${OBJECTDIR}/_ext/252762716/rsa.o.d ${OBJECTDIR}/_ext/252762716/big_int.o.d ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d ${OBJECTDIR}/_ext/252762716/arc4.o.d ${OBJECTDIR}/_ext/1360937237/smtp.o.d ${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d ${OBJECTDIR}/_ext/252762716/http2.o.d ${OBJECTDIR}/_ext/252762716/mpfs2.o.d ${OBJECTDIR}/_ext/252762716/custom_http_app.o.d ${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/659867239/daylight.o ${OBJECTDIR}/_ext/659867239/rtc.o ${OBJECTDIR}/_ext/659867239/rtcconverter.o ${OBJECTDIR}/_ext/1360937237/BootLoader.o ${OBJECTDIR}/_ext/1360937237/Framework.o ${OBJECTDIR}/_ext/1360937237/NVMem.o ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o ${OBJECTDIR}/_ext/1360937237/Tick.o ${OBJECTDIR}/_ext/1360937237/stack_task.o ${OBJECTDIR}/_ext/1360937237/UDP.o ${OBJECTDIR}/_ext/1360937237/dhcp_client.o ${OBJECTDIR}/_ext/1360937237/ARP.o ${OBJECTDIR}/_ext/1360937237/Helpers.o ${OBJECTDIR}/_ext/1360937237/dns_client.o ${OBJECTDIR}/_ext/1360937237/nbns.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o ${OBJECTDIR}/_ext/1360937237/Delay.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o ${OBJECTDIR}/_ext/1360937237/announce.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o ${OBJECTDIR}/_ext/1360937237/IP.o ${OBJECTDIR}/_ext/1360937237/icmp.o ${OBJECTDIR}/_ext/1360937237/tcp.o ${OBJECTDIR}/_ext/1360937237/uart.o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o ${OBJECTDIR}/_ext/252762716/sntp.o ${OBJECTDIR}/_ext/252762716/ssl.o ${OBJECTDIR}/_ext/252762716/random.o ${OBJECTDIR}/_ext/252762716/hashes.o ${OBJECTDIR}/_ext/252762716/rsa.o ${OBJECTDIR}/_ext/252762716/big_int.o ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o ${OBJECTDIR}/_ext/252762716/arc4.o ${OBJECTDIR}/_ext/1360937237/smtp.o ${OBJECTDIR}/_ext/1360937237/smtp_demo.o ${OBJECTDIR}/_ext/252762716/http2.o ${OBJECTDIR}/_ext/252762716/mpfs2.o ${OBJECTDIR}/_ext/252762716/custom_http_app.o ${OBJECTDIR}/_ext/252762716/mpfs_img2.o

# Source Files
SOURCEFILES=../src/rtc/daylight.c ../src/rtc/rtc.c ../src/rtc/rtcconverter.c ../src/BootLoader.c ../src/Framework.c ../src/NVMem.c ../src/EthernetTasks.c ../src/Tick.c ../src/stack_task.c ../src/UDP.c ../src/dhcp_client.c ../src/ARP.c ../src/Helpers.c ../src/dns_client.c ../src/nbns.c ../src/drv_wifi_mac.c ../src/drv_wifi_raw.c ../src/drv_wifi_com.c ../src/Delay.c ../src/drv_wifi_eint.c ../src/drv_wifi_debug_strings.c ../src/drv_wifi_spi.c ../src/drv_wifi_power_save.c ../src/announce.c ../src/drv_wifi_mgmt_msg.c ../src/drv_wifi_event_handler.c ../src/drv_wifi_config.c ../src/drv_wifi_connection_algorithm.c ../src/drv_wifi_connection_manager.c ../src/drv_wifi_pbkdf2.c ../src/drv_wifi_init.c ../src/drv_wifi_param_msg.c ../src/IP.c ../src/icmp.c ../src/tcp.c ../src/uart.c ../src/drv_wifi_connection_profile.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c ../src/big_int_helper_pic32.S c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c ../src/smtp.c ../src/smtp_demo.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F256H
MP_LINKER_FILE_OPTION=,--script="c:\temp\project\_sandbox\bootloader_pic32\WiFiBootloader_MRF24WB\lkr\btl_32MX440F256H_generic.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o: ../src/big_int_helper_pic32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.ok ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d" "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d"  -o ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o ../src/big_int_helper_pic32.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
else
${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o: ../src/big_int_helper_pic32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.ok ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d" "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.d"  -o ${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o ../src/big_int_helper_pic32.S  -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/big_int_helper_pic32.o.asm.d"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/659867239/daylight.o: ../src/rtc/daylight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/daylight.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/daylight.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/daylight.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/daylight.o.d" -o ${OBJECTDIR}/_ext/659867239/daylight.o ../src/rtc/daylight.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/659867239/rtc.o: ../src/rtc/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/rtc.o.d" -o ${OBJECTDIR}/_ext/659867239/rtc.o ../src/rtc/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/659867239/rtcconverter.o: ../src/rtc/rtcconverter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtcconverter.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtcconverter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/rtcconverter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/rtcconverter.o.d" -o ${OBJECTDIR}/_ext/659867239/rtcconverter.o ../src/rtc/rtcconverter.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/BootLoader.o: ../src/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BootLoader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BootLoader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1360937237/BootLoader.o ../src/BootLoader.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Framework.o: ../src/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/Framework.o ../src/Framework.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/NVMem.o: ../src/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/NVMem.o.d" -o ${OBJECTDIR}/_ext/1360937237/NVMem.o ../src/NVMem.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/EthernetTasks.o: ../src/EthernetTasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o ../src/EthernetTasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Tick.o: ../src/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Tick.o.d" -o ${OBJECTDIR}/_ext/1360937237/Tick.o ../src/Tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/stack_task.o: ../src/stack_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/stack_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/stack_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/stack_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/stack_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/stack_task.o ../src/stack_task.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/UDP.o: ../src/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/UDP.o.d" -o ${OBJECTDIR}/_ext/1360937237/UDP.o ../src/UDP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/dhcp_client.o: ../src/dhcp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dhcp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d" -o ${OBJECTDIR}/_ext/1360937237/dhcp_client.o ../src/dhcp_client.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ARP.o: ../src/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/ARP.o.d" -o ${OBJECTDIR}/_ext/1360937237/ARP.o ../src/ARP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Helpers.o: ../src/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Helpers.o.d" -o ${OBJECTDIR}/_ext/1360937237/Helpers.o ../src/Helpers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/dns_client.o: ../src/dns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/dns_client.o.d" -o ${OBJECTDIR}/_ext/1360937237/dns_client.o ../src/dns_client.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/nbns.o: ../src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/nbns.o.d" -o ${OBJECTDIR}/_ext/1360937237/nbns.o ../src/nbns.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o: ../src/drv_wifi_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o ../src/drv_wifi_mac.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o: ../src/drv_wifi_raw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o ../src/drv_wifi_raw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o: ../src/drv_wifi_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o ../src/drv_wifi_com.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Delay.o: ../src/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Delay.o.d" -o ${OBJECTDIR}/_ext/1360937237/Delay.o ../src/Delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o: ../src/drv_wifi_eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o ../src/drv_wifi_eint.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o: ../src/drv_wifi_debug_strings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o ../src/drv_wifi_debug_strings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o: ../src/drv_wifi_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o ../src/drv_wifi_spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o: ../src/drv_wifi_power_save.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o ../src/drv_wifi_power_save.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/announce.o: ../src/announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/announce.o.d" -o ${OBJECTDIR}/_ext/1360937237/announce.o ../src/announce.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o: ../src/drv_wifi_mgmt_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o ../src/drv_wifi_mgmt_msg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o: ../src/drv_wifi_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o ../src/drv_wifi_event_handler.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o: ../src/drv_wifi_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o ../src/drv_wifi_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o: ../src/drv_wifi_connection_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o ../src/drv_wifi_connection_algorithm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o: ../src/drv_wifi_connection_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o ../src/drv_wifi_connection_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o: ../src/drv_wifi_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o ../src/drv_wifi_pbkdf2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o: ../src/drv_wifi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o ../src/drv_wifi_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o: ../src/drv_wifi_param_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o ../src/drv_wifi_param_msg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IP.o: ../src/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/IP.o.d" -o ${OBJECTDIR}/_ext/1360937237/IP.o ../src/IP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/icmp.o: ../src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/icmp.o.d" -o ${OBJECTDIR}/_ext/1360937237/icmp.o ../src/icmp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/tcp.o: ../src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/tcp.o.d" -o ${OBJECTDIR}/_ext/1360937237/tcp.o ../src/tcp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart.o: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart.o ../src/uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o: ../src/drv_wifi_connection_profile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o ../src/drv_wifi_connection_profile.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/sntp.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/sntp.o.d" -o ${OBJECTDIR}/_ext/252762716/sntp.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/ssl.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/ssl.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/ssl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/ssl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/ssl.o.d" -o ${OBJECTDIR}/_ext/252762716/ssl.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/random.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/random.o.d" -o ${OBJECTDIR}/_ext/252762716/random.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/hashes.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/hashes.o.d" -o ${OBJECTDIR}/_ext/252762716/hashes.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/rsa.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/rsa.o.d" -o ${OBJECTDIR}/_ext/252762716/rsa.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/big_int.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/big_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/big_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/big_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/big_int.o.d" -o ${OBJECTDIR}/_ext/252762716/big_int.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d" -o ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/arc4.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/arc4.o.d" -o ${OBJECTDIR}/_ext/252762716/arc4.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/smtp.o: ../src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/smtp.o.d" -o ${OBJECTDIR}/_ext/1360937237/smtp.o ../src/smtp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/smtp_demo.o: ../src/smtp_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d" -o ${OBJECTDIR}/_ext/1360937237/smtp_demo.o ../src/smtp_demo.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/http2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/http2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/http2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/http2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/http2.o.d" -o ${OBJECTDIR}/_ext/252762716/http2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/mpfs2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/mpfs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/mpfs2.o.d" -o ${OBJECTDIR}/_ext/252762716/mpfs2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/custom_http_app.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/252762716/custom_http_app.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/mpfs_img2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/252762716/mpfs_img2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/659867239/daylight.o: ../src/rtc/daylight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/daylight.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/daylight.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/daylight.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/daylight.o.d" -o ${OBJECTDIR}/_ext/659867239/daylight.o ../src/rtc/daylight.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/659867239/rtc.o: ../src/rtc/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/rtc.o.d" -o ${OBJECTDIR}/_ext/659867239/rtc.o ../src/rtc/rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/659867239/rtcconverter.o: ../src/rtc/rtcconverter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867239" 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtcconverter.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867239/rtcconverter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867239/rtcconverter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/659867239/rtcconverter.o.d" -o ${OBJECTDIR}/_ext/659867239/rtcconverter.o ../src/rtc/rtcconverter.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/BootLoader.o: ../src/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BootLoader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BootLoader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1360937237/BootLoader.o ../src/BootLoader.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Framework.o: ../src/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/Framework.o ../src/Framework.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/NVMem.o: ../src/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/NVMem.o.d" -o ${OBJECTDIR}/_ext/1360937237/NVMem.o ../src/NVMem.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/EthernetTasks.o: ../src/EthernetTasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/EthernetTasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/EthernetTasks.o ../src/EthernetTasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Tick.o: ../src/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Tick.o.d" -o ${OBJECTDIR}/_ext/1360937237/Tick.o ../src/Tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/stack_task.o: ../src/stack_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/stack_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/stack_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/stack_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/stack_task.o.d" -o ${OBJECTDIR}/_ext/1360937237/stack_task.o ../src/stack_task.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/UDP.o: ../src/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/UDP.o.d" -o ${OBJECTDIR}/_ext/1360937237/UDP.o ../src/UDP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/dhcp_client.o: ../src/dhcp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dhcp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/dhcp_client.o.d" -o ${OBJECTDIR}/_ext/1360937237/dhcp_client.o ../src/dhcp_client.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ARP.o: ../src/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/ARP.o.d" -o ${OBJECTDIR}/_ext/1360937237/ARP.o ../src/ARP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Helpers.o: ../src/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Helpers.o.d" -o ${OBJECTDIR}/_ext/1360937237/Helpers.o ../src/Helpers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/dns_client.o: ../src/dns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/dns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/dns_client.o.d" -o ${OBJECTDIR}/_ext/1360937237/dns_client.o ../src/dns_client.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/nbns.o: ../src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/nbns.o.d" -o ${OBJECTDIR}/_ext/1360937237/nbns.o ../src/nbns.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o: ../src/drv_wifi_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mac.o ../src/drv_wifi_mac.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o: ../src/drv_wifi_raw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_raw.o ../src/drv_wifi_raw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o: ../src/drv_wifi_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_com.o ../src/drv_wifi_com.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/Delay.o: ../src/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/Delay.o.d" -o ${OBJECTDIR}/_ext/1360937237/Delay.o ../src/Delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o: ../src/drv_wifi_eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_eint.o ../src/drv_wifi_eint.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o: ../src/drv_wifi_debug_strings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_debug_strings.o ../src/drv_wifi_debug_strings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o: ../src/drv_wifi_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_spi.o ../src/drv_wifi_spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o: ../src/drv_wifi_power_save.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_power_save.o ../src/drv_wifi_power_save.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/announce.o: ../src/announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/announce.o.d" -o ${OBJECTDIR}/_ext/1360937237/announce.o ../src/announce.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o: ../src/drv_wifi_mgmt_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_mgmt_msg.o ../src/drv_wifi_mgmt_msg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o: ../src/drv_wifi_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_event_handler.o ../src/drv_wifi_event_handler.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o: ../src/drv_wifi_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_config.o ../src/drv_wifi_config.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o: ../src/drv_wifi_connection_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_algorithm.o ../src/drv_wifi_connection_algorithm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o: ../src/drv_wifi_connection_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_manager.o ../src/drv_wifi_connection_manager.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o: ../src/drv_wifi_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_pbkdf2.o ../src/drv_wifi_pbkdf2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o: ../src/drv_wifi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_init.o ../src/drv_wifi_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o: ../src/drv_wifi_param_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_param_msg.o ../src/drv_wifi_param_msg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IP.o: ../src/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/IP.o.d" -o ${OBJECTDIR}/_ext/1360937237/IP.o ../src/IP.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/icmp.o: ../src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/icmp.o.d" -o ${OBJECTDIR}/_ext/1360937237/icmp.o ../src/icmp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/tcp.o: ../src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/tcp.o.d" -o ${OBJECTDIR}/_ext/1360937237/tcp.o ../src/tcp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart.o: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart.o ../src/uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o: ../src/drv_wifi_connection_profile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_wifi_connection_profile.o ../src/drv_wifi_connection_profile.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/sntp.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/sntp.o.d" -o ${OBJECTDIR}/_ext/252762716/sntp.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/sntp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/ssl.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/ssl.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/ssl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/ssl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/ssl.o.d" -o ${OBJECTDIR}/_ext/252762716/ssl.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/ssl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/random.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/random.o.d" -o ${OBJECTDIR}/_ext/252762716/random.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/random.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/hashes.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/hashes.o.d" -o ${OBJECTDIR}/_ext/252762716/hashes.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/hashes.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/rsa.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/rsa.o.d" -o ${OBJECTDIR}/_ext/252762716/rsa.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/rsa.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/big_int.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/big_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/big_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/big_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/big_int.o.d" -o ${OBJECTDIR}/_ext/252762716/big_int.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/big_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o.d" -o ${OBJECTDIR}/_ext/252762716/custom_ssl_cert.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_ssl_cert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/arc4.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/arc4.o.d" -o ${OBJECTDIR}/_ext/252762716/arc4.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/arc4.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/smtp.o: ../src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/smtp.o.d" -o ${OBJECTDIR}/_ext/1360937237/smtp.o ../src/smtp.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/smtp_demo.o: ../src/smtp_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/smtp_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/1360937237/smtp_demo.o.d" -o ${OBJECTDIR}/_ext/1360937237/smtp_demo.o ../src/smtp_demo.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/http2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/http2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/http2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/http2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/http2.o.d" -o ${OBJECTDIR}/_ext/252762716/http2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/http2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/mpfs2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/mpfs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/mpfs2.o.d" -o ${OBJECTDIR}/_ext/252762716/mpfs2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/custom_http_app.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/252762716/custom_http_app.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/custom_http_app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/252762716/mpfs_img2.o: c\:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/252762716" 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/252762716/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../inc/mal" -I"../inc/rtc" -I"../inc" -I"." -MMD -MF "${OBJECTDIR}/_ext/252762716/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/252762716/mpfs_img2.o c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/src/mpfs_img2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/lkr/btl_32MX440F256H_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-L"../../../../../../Program Files (x86)/Microchip/xc32/v2.30/pic32mx/lib",-L".",-Map="${DISTDIR}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   c:/temp/project/_sandbox/bootloader_pic32/WiFiBootloader_MRF24WB/lkr/btl_32MX440F256H_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-L"../../../../../../Program Files (x86)/Microchip/xc32/v2.30/pic32mx/lib",-L".",-Map="${DISTDIR}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/WiFiBootloader_MRF24WB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
