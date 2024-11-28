/*******************************************************************************
* File Name: Ref.h  
* Version 1.90
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the 8-bit Voltage DAC (vDAC8) User Module.
*
*   Note:
*     
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VDAC8_Ref_H) 
#define CY_VDAC8_Ref_H

#include "cytypes.h"
#include "cyfitter.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component VDAC8_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState; 
    uint8 data_value;
}Ref_backupStruct;

/* component init state */
extern uint8 Ref_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void Ref_Start(void)           ;
void Ref_Stop(void)            ;
void Ref_SetSpeed(uint8 speed) ;
void Ref_SetRange(uint8 range) ;
void Ref_SetValue(uint8 value) ;
void Ref_DacTrim(void)         ;
void Ref_Init(void)            ;
void Ref_Enable(void)          ;
void Ref_SaveConfig(void)      ;
void Ref_RestoreConfig(void)   ;
void Ref_Sleep(void)           ;
void Ref_Wakeup(void)          ;


/***************************************
*            API Constants
***************************************/

/* SetRange constants */

#define Ref_RANGE_1V       0x00u
#define Ref_RANGE_4V       0x04u


/* Power setting for Start API  */
#define Ref_LOWSPEED       0x00u
#define Ref_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

 /* Default DAC range */
#define Ref_DEFAULT_RANGE    0u
 /* Default DAC speed */
#define Ref_DEFAULT_SPEED    2u
 /* Default Control */
#define Ref_DEFAULT_CNTL      0x00u
/* Default Strobe mode */
#define Ref_DEFAULT_STRB     0u
 /* Initial DAC value */
#define Ref_DEFAULT_DATA     150u
 /* Default Data Source */
#define Ref_DEFAULT_DATA_SRC 0u


/***************************************
*              Registers        
***************************************/
#define Ref_CR0_REG            (* (reg8 *) Ref_viDAC8__CR0 )
#define Ref_CR0_PTR            (  (reg8 *) Ref_viDAC8__CR0 )
#define Ref_CR1_REG            (* (reg8 *) Ref_viDAC8__CR1 )
#define Ref_CR1_PTR            (  (reg8 *) Ref_viDAC8__CR1 )
#define Ref_Data_REG           (* (reg8 *) Ref_viDAC8__D )
#define Ref_Data_PTR           (  (reg8 *) Ref_viDAC8__D )
#define Ref_Strobe_REG         (* (reg8 *) Ref_viDAC8__STROBE )
#define Ref_Strobe_PTR         (  (reg8 *) Ref_viDAC8__STROBE )
#define Ref_SW0_REG            (* (reg8 *) Ref_viDAC8__SW0 )
#define Ref_SW0_PTR            (  (reg8 *) Ref_viDAC8__SW0 )
#define Ref_SW2_REG            (* (reg8 *) Ref_viDAC8__SW2 )
#define Ref_SW2_PTR            (  (reg8 *) Ref_viDAC8__SW2 )
#define Ref_SW3_REG            (* (reg8 *) Ref_viDAC8__SW3 )
#define Ref_SW3_PTR            (  (reg8 *) Ref_viDAC8__SW3 )
#define Ref_SW4_REG            (* (reg8 *) Ref_viDAC8__SW4 )
#define Ref_SW4_PTR            (  (reg8 *) Ref_viDAC8__SW4 )
#define Ref_TR_REG             (* (reg8 *) Ref_viDAC8__TR )
#define Ref_TR_PTR             (  (reg8 *) Ref_viDAC8__TR )
/* Power manager */
#define Ref_PWRMGR_REG         (* (reg8 *) Ref_viDAC8__PM_ACT_CFG )
#define Ref_PWRMGR_PTR         (  (reg8 *) Ref_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Ref_STBY_PWRMGR_REG    (* (reg8 *) Ref_viDAC8__PM_STBY_CFG )
#define Ref_STBY_PWRMGR_PTR    (  (reg8 *) Ref_viDAC8__PM_STBY_CFG )

/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define Ref_CR0         (* (reg8 *) Ref_viDAC8__CR0 )
#define Ref_CR1         (* (reg8 *) Ref_viDAC8__CR1 )
#define Ref_Data        (* (reg8 *) Ref_viDAC8__D )
#define Ref_Data_PTR    (  (reg8 *) Ref_viDAC8__D )
#define Ref_Strobe      (* (reg8 *) Ref_viDAC8__STROBE )
#define Ref_SW0         (* (reg8 *) Ref_viDAC8__SW0 )
#define Ref_SW2         (* (reg8 *) Ref_viDAC8__SW2 )
#define Ref_SW3         (* (reg8 *) Ref_viDAC8__SW3 )
#define Ref_SW4         (* (reg8 *) Ref_viDAC8__SW4 )
#define Ref_TR          (* (reg8 *) Ref_viDAC8__TR )
/* Power manager */
#define Ref_PWRMGR      (* (reg8 *) Ref_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Ref_STBY_PWRMGR (* (reg8 *) Ref_viDAC8__PM_STBY_CFG )


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define Ref_HS_MASK        0x02u
#define Ref_HS_LOWPOWER    0x00u
#define Ref_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define Ref_MODE_MASK      0x10u
#define Ref_MODE_V         0x00u
#define Ref_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define Ref_RANGE_MASK     0x0Cu
#define Ref_RANGE_0        0x00u
#define Ref_RANGE_1        0x04u

/* CR1 iDac Control Register 1 definitions */

/* Bit Field  DAC_MX_DATA                  */
#define Ref_SRC_MASK       0x20u
#define Ref_SRC_REG        0x00u
#define Ref_SRC_UDB        0x20u

/* This bit enable reset from UDB array      */
#define Ref_RESET_MASK     0x10u
#define Ref_RESET_ENABLE   0x10u
#define Ref_RESET_DISABLE  0x00u

/* This bit enables data from DAC bus      */
#define Ref_DACBUS_MASK     0x20u
#define Ref_DACBUS_ENABLE   0x20u
#define Ref_DACBUS_DISABLE  0x00u

/* DAC STROBE Strobe Control Register definitions */

/* Bit Field  DAC_MX_STROBE                  */
#define Ref_STRB_MASK     0x08u
#define Ref_STRB_EN       0x08u
#define Ref_STRB_DIS      0x00u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define Ref_ACT_PWR_EN   Ref_viDAC8__PM_ACT_MSK
  /* Standby Power enable mask */
#define Ref_STBY_PWR_EN  Ref_viDAC8__PM_STBY_MSK


/*******************************************************************************
*              Trim    
* Note - VDAC trim values are stored in the "Customer Table" area in * Row 1 of
*the Hidden Flash.  There are 8 bytes of trim data for each VDAC block.
* The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* The data set for the 4 VDACs are arranged using a left side/right side
* approach:
*   Left 0, Left 1, Right 0, Right 1.
* When mapped to the VDAC0 thru VDAC3 as:
*   VDAC 0, VDAC 2, VDAC 1, VDAC 3
*******************************************************************************/
#define Ref_TRIM_M7_1V_RNG_OFFSET  0x06u
#define Ref_TRIM_M8_4V_RNG_OFFSET  0x07u
/*Constatnt to set DAC in current mode and turnoff output */
#define Ref_CUR_MODE_OUT_OFF       0x1Eu 
#define Ref_DAC_TRIM_BASE          (Ref_viDAC8__TRIM__M1)

#endif /* CY_VDAC8_Ref_H  */


/* [] END OF FILE */


