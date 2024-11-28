/*******************************************************************************
* File Name: turn.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_turn_H)
#define CY_ISR_turn_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void turn_Start(void);
void turn_StartEx(cyisraddress address);
void turn_Stop(void);

CY_ISR_PROTO(turn_Interrupt);

void turn_SetVector(cyisraddress address);
cyisraddress turn_GetVector(void);

void turn_SetPriority(uint8 priority);
uint8 turn_GetPriority(void);

void turn_Enable(void);
uint8 turn_GetState(void);
void turn_Disable(void);

void turn_SetPending(void);
void turn_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the turn ISR. */
#define turn_INTC_VECTOR            ((reg32 *) turn__INTC_VECT)

/* Address of the turn ISR priority. */
#define turn_INTC_PRIOR             ((reg8 *) turn__INTC_PRIOR_REG)

/* Priority of the turn interrupt. */
#define turn_INTC_PRIOR_NUMBER      turn__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable turn interrupt. */
#define turn_INTC_SET_EN            ((reg32 *) turn__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the turn interrupt. */
#define turn_INTC_CLR_EN            ((reg32 *) turn__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the turn interrupt state to pending. */
#define turn_INTC_SET_PD            ((reg32 *) turn__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the turn interrupt. */
#define turn_INTC_CLR_PD            ((reg32 *) turn__INTC_CLR_PD_REG)


#endif /* CY_ISR_turn_H */


/* [] END OF FILE */
