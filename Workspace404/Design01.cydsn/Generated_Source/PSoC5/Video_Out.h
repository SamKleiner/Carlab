/*******************************************************************************
* File Name: Video_Out.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Video_Out_H) /* Pins Video_Out_H */
#define CY_PINS_Video_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Video_Out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Video_Out__PORT == 15 && ((Video_Out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Video_Out_Write(uint8 value);
void    Video_Out_SetDriveMode(uint8 mode);
uint8   Video_Out_ReadDataReg(void);
uint8   Video_Out_Read(void);
void    Video_Out_SetInterruptMode(uint16 position, uint16 mode);
uint8   Video_Out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Video_Out_SetDriveMode() function.
     *  @{
     */
        #define Video_Out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Video_Out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Video_Out_DM_RES_UP          PIN_DM_RES_UP
        #define Video_Out_DM_RES_DWN         PIN_DM_RES_DWN
        #define Video_Out_DM_OD_LO           PIN_DM_OD_LO
        #define Video_Out_DM_OD_HI           PIN_DM_OD_HI
        #define Video_Out_DM_STRONG          PIN_DM_STRONG
        #define Video_Out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Video_Out_MASK               Video_Out__MASK
#define Video_Out_SHIFT              Video_Out__SHIFT
#define Video_Out_WIDTH              1u

/* Interrupt constants */
#if defined(Video_Out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Video_Out_SetInterruptMode() function.
     *  @{
     */
        #define Video_Out_INTR_NONE      (uint16)(0x0000u)
        #define Video_Out_INTR_RISING    (uint16)(0x0001u)
        #define Video_Out_INTR_FALLING   (uint16)(0x0002u)
        #define Video_Out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Video_Out_INTR_MASK      (0x01u) 
#endif /* (Video_Out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Video_Out_PS                     (* (reg8 *) Video_Out__PS)
/* Data Register */
#define Video_Out_DR                     (* (reg8 *) Video_Out__DR)
/* Port Number */
#define Video_Out_PRT_NUM                (* (reg8 *) Video_Out__PRT) 
/* Connect to Analog Globals */                                                  
#define Video_Out_AG                     (* (reg8 *) Video_Out__AG)                       
/* Analog MUX bux enable */
#define Video_Out_AMUX                   (* (reg8 *) Video_Out__AMUX) 
/* Bidirectional Enable */                                                        
#define Video_Out_BIE                    (* (reg8 *) Video_Out__BIE)
/* Bit-mask for Aliased Register Access */
#define Video_Out_BIT_MASK               (* (reg8 *) Video_Out__BIT_MASK)
/* Bypass Enable */
#define Video_Out_BYP                    (* (reg8 *) Video_Out__BYP)
/* Port wide control signals */                                                   
#define Video_Out_CTL                    (* (reg8 *) Video_Out__CTL)
/* Drive Modes */
#define Video_Out_DM0                    (* (reg8 *) Video_Out__DM0) 
#define Video_Out_DM1                    (* (reg8 *) Video_Out__DM1)
#define Video_Out_DM2                    (* (reg8 *) Video_Out__DM2) 
/* Input Buffer Disable Override */
#define Video_Out_INP_DIS                (* (reg8 *) Video_Out__INP_DIS)
/* LCD Common or Segment Drive */
#define Video_Out_LCD_COM_SEG            (* (reg8 *) Video_Out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Video_Out_LCD_EN                 (* (reg8 *) Video_Out__LCD_EN)
/* Slew Rate Control */
#define Video_Out_SLW                    (* (reg8 *) Video_Out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Video_Out_PRTDSI__CAPS_SEL       (* (reg8 *) Video_Out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Video_Out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Video_Out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Video_Out_PRTDSI__OE_SEL0        (* (reg8 *) Video_Out__PRTDSI__OE_SEL0) 
#define Video_Out_PRTDSI__OE_SEL1        (* (reg8 *) Video_Out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Video_Out_PRTDSI__OUT_SEL0       (* (reg8 *) Video_Out__PRTDSI__OUT_SEL0) 
#define Video_Out_PRTDSI__OUT_SEL1       (* (reg8 *) Video_Out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Video_Out_PRTDSI__SYNC_OUT       (* (reg8 *) Video_Out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Video_Out__SIO_CFG)
    #define Video_Out_SIO_HYST_EN        (* (reg8 *) Video_Out__SIO_HYST_EN)
    #define Video_Out_SIO_REG_HIFREQ     (* (reg8 *) Video_Out__SIO_REG_HIFREQ)
    #define Video_Out_SIO_CFG            (* (reg8 *) Video_Out__SIO_CFG)
    #define Video_Out_SIO_DIFF           (* (reg8 *) Video_Out__SIO_DIFF)
#endif /* (Video_Out__SIO_CFG) */

/* Interrupt Registers */
#if defined(Video_Out__INTSTAT)
    #define Video_Out_INTSTAT            (* (reg8 *) Video_Out__INTSTAT)
    #define Video_Out_SNAP               (* (reg8 *) Video_Out__SNAP)
    
	#define Video_Out_0_INTTYPE_REG 		(* (reg8 *) Video_Out__0__INTTYPE)
#endif /* (Video_Out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Video_Out_H */


/* [] END OF FILE */
