/*******************************************************************************
* File Name: IRServo.h  
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

#if !defined(CY_PINS_IRServo_H) /* Pins IRServo_H */
#define CY_PINS_IRServo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRServo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRServo__PORT == 15 && ((IRServo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IRServo_Write(uint8 value);
void    IRServo_SetDriveMode(uint8 mode);
uint8   IRServo_ReadDataReg(void);
uint8   IRServo_Read(void);
void    IRServo_SetInterruptMode(uint16 position, uint16 mode);
uint8   IRServo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IRServo_SetDriveMode() function.
     *  @{
     */
        #define IRServo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IRServo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IRServo_DM_RES_UP          PIN_DM_RES_UP
        #define IRServo_DM_RES_DWN         PIN_DM_RES_DWN
        #define IRServo_DM_OD_LO           PIN_DM_OD_LO
        #define IRServo_DM_OD_HI           PIN_DM_OD_HI
        #define IRServo_DM_STRONG          PIN_DM_STRONG
        #define IRServo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IRServo_MASK               IRServo__MASK
#define IRServo_SHIFT              IRServo__SHIFT
#define IRServo_WIDTH              1u

/* Interrupt constants */
#if defined(IRServo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IRServo_SetInterruptMode() function.
     *  @{
     */
        #define IRServo_INTR_NONE      (uint16)(0x0000u)
        #define IRServo_INTR_RISING    (uint16)(0x0001u)
        #define IRServo_INTR_FALLING   (uint16)(0x0002u)
        #define IRServo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IRServo_INTR_MASK      (0x01u) 
#endif /* (IRServo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRServo_PS                     (* (reg8 *) IRServo__PS)
/* Data Register */
#define IRServo_DR                     (* (reg8 *) IRServo__DR)
/* Port Number */
#define IRServo_PRT_NUM                (* (reg8 *) IRServo__PRT) 
/* Connect to Analog Globals */                                                  
#define IRServo_AG                     (* (reg8 *) IRServo__AG)                       
/* Analog MUX bux enable */
#define IRServo_AMUX                   (* (reg8 *) IRServo__AMUX) 
/* Bidirectional Enable */                                                        
#define IRServo_BIE                    (* (reg8 *) IRServo__BIE)
/* Bit-mask for Aliased Register Access */
#define IRServo_BIT_MASK               (* (reg8 *) IRServo__BIT_MASK)
/* Bypass Enable */
#define IRServo_BYP                    (* (reg8 *) IRServo__BYP)
/* Port wide control signals */                                                   
#define IRServo_CTL                    (* (reg8 *) IRServo__CTL)
/* Drive Modes */
#define IRServo_DM0                    (* (reg8 *) IRServo__DM0) 
#define IRServo_DM1                    (* (reg8 *) IRServo__DM1)
#define IRServo_DM2                    (* (reg8 *) IRServo__DM2) 
/* Input Buffer Disable Override */
#define IRServo_INP_DIS                (* (reg8 *) IRServo__INP_DIS)
/* LCD Common or Segment Drive */
#define IRServo_LCD_COM_SEG            (* (reg8 *) IRServo__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRServo_LCD_EN                 (* (reg8 *) IRServo__LCD_EN)
/* Slew Rate Control */
#define IRServo_SLW                    (* (reg8 *) IRServo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRServo_PRTDSI__CAPS_SEL       (* (reg8 *) IRServo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRServo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRServo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRServo_PRTDSI__OE_SEL0        (* (reg8 *) IRServo__PRTDSI__OE_SEL0) 
#define IRServo_PRTDSI__OE_SEL1        (* (reg8 *) IRServo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRServo_PRTDSI__OUT_SEL0       (* (reg8 *) IRServo__PRTDSI__OUT_SEL0) 
#define IRServo_PRTDSI__OUT_SEL1       (* (reg8 *) IRServo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRServo_PRTDSI__SYNC_OUT       (* (reg8 *) IRServo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IRServo__SIO_CFG)
    #define IRServo_SIO_HYST_EN        (* (reg8 *) IRServo__SIO_HYST_EN)
    #define IRServo_SIO_REG_HIFREQ     (* (reg8 *) IRServo__SIO_REG_HIFREQ)
    #define IRServo_SIO_CFG            (* (reg8 *) IRServo__SIO_CFG)
    #define IRServo_SIO_DIFF           (* (reg8 *) IRServo__SIO_DIFF)
#endif /* (IRServo__SIO_CFG) */

/* Interrupt Registers */
#if defined(IRServo__INTSTAT)
    #define IRServo_INTSTAT            (* (reg8 *) IRServo__INTSTAT)
    #define IRServo_SNAP               (* (reg8 *) IRServo__SNAP)
    
	#define IRServo_0_INTTYPE_REG 		(* (reg8 *) IRServo__0__INTTYPE)
#endif /* (IRServo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRServo_H */


/* [] END OF FILE */
