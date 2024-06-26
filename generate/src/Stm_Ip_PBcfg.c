/*==================================================================================================
* Project :             RTD AUTOSAR 4.7
* Platform :            CORTEXM
* Peripheral :          Stm_Pit_Rtc_Emios
* Dependencies :        none
*
* Autosar Version :     4.7.0
* Autosar Revision :    ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version :          3.0.0
* Build Version :       S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
* Copyright 2020 - 2023 NXP Semiconductors
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
/**
 *   @file        Stm_Ip_PBcfg.c
 *
 *   @addtogroup  stm_ip Stm IPL
 *
 *   @{
 */


/*==================================================================================================*/
#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Stm_Ip_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define STM_IP_VENDOR_ID_PBCFG_C                    43
#define STM_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_C     4
#define STM_IP_AR_RELEASE_MINOR_VERSION_PBCFG_C     7
#define STM_IP_AR_RELEASE_REVISION_VERSION_PBCFG_C  0
#define STM_IP_SW_MAJOR_VERSION_PBCFG_C             3
#define STM_IP_SW_MINOR_VERSION_PBCFG_C             0
#define STM_IP_SW_PATCH_VERSION_PBCFG_C             0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (STM_IP_VENDOR_ID_PBCFG_C != STM_IP_VENDOR_ID_PBCFG_H)
    #error "Stm_Ip_PBcfg.c and Stm_Ip_PBcfg.h have different vendor ids"
#endif
/* Check if this header file and header file are of the same Autosar version */
#if ((STM_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_C != STM_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_H) || \
     (STM_IP_AR_RELEASE_MINOR_VERSION_PBCFG_C != STM_IP_AR_RELEASE_MINOR_VERSION_PBCFG_H) || \
     (STM_IP_AR_RELEASE_REVISION_VERSION_PBCFG_C != STM_IP_AR_RELEASE_REVISION_VERSION_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Stm_Ip_PBcfg.c and Stm_Ip_PBcfg.h are different"
#endif
/* Check if this header file and header file are of the same Software version */
#if ((STM_IP_SW_MAJOR_VERSION_PBCFG_C != STM_IP_SW_MAJOR_VERSION_PBCFG_H) || \
     (STM_IP_SW_MINOR_VERSION_PBCFG_C != STM_IP_SW_MINOR_VERSION_PBCFG_H) || \
     (STM_IP_SW_PATCH_VERSION_PBCFG_C != STM_IP_SW_PATCH_VERSION_PBCFG_H) \
    )
    #error "Software Version Numbers of Stm_Ip_PBcfg.c and Stm_Ip_PBcfg.h are different"
#endif
/*================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/
#define GPT_START_SEC_CODE
#include "Gpt_MemMap.h"
extern void Stm0_Ch0_Callback(uint8 channel); 
#define GPT_STOP_SEC_CODE
#include "Gpt_MemMap.h"
/*==================================================================================================
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/
#define GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"


const Stm_Ip_InstanceConfigType STM_0_InitConfig_PB =
{
    /** @brief STM Freeze Enable */
    (boolean)(TRUE),
#if(STM_IP_SET_CLOCK_MODE == STD_ON)
    /** @brief STM Alternate Prescaler Value */
    47U,
#endif
    /** @brief STM Prescaler Value
                00h - Divide module clock by 1
                01h - Divide module clock by 2
                ....
                FFh - Divide module clock by 256 */
    47U
};
const Stm_Ip_ChannelConfigType STM_0_ChannelConfig_PB[1U] =
{
    /**@brief StmChannel_0 */ 
    {
        /** @brief STM Channel Id */
        0U,
        /** @brief STM callback name */
        &Stm0_Ch0_Callback,
        /** @brief STM callbackparam */
        (uint8)0U,
        /** @brief STM channel mode  */
        STM_IP_CH_MODE_CONTINUOUS
    }
};
#define GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/

#ifdef __cplusplus
}
#endif  /*STM_IP_PBCFG_C*/
/** @} */
