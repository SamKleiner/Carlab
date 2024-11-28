/*******************************************************************************
* File Name: Motor_Stop.h
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
#if !defined(CY_ISR_Motor_Stop_H)
#define CY_ISR_Motor_Stop_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Motor_Stop_Start(void);
void Motor_Stop_StartEx(cyisraddress address);
void Motor_Stop_Stop(void);

CY_ISR_PROTO(Motor_Stop_Interrupt);

void Motor_Stop_SetVector(cyisraddress address);
cyisraddress Motor_Stop_GetVector(void);

void Motor_Stop_SetPriority(uint8 priority);
uint8 Motor_Stop_GetPriority(void);

void Motor_Stop_Enable(void);
uint8 Motor_Stop_GetState(void);
void Motor_Stop_Disable(void);

void Motor_Stop_SetPending(void);
void Motor_Stop_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Motor_Stop ISR. */
#define Motor_Stop_INTC_VECTOR            ((reg32 *) Motor_Stop__INTC_VECT)

/* Address of the Motor_Stop ISR priority. */
#define Motor_Stop_INTC_PRIOR             ((reg8 *) Motor_Stop__INTC_PRIOR_REG)

/* Priority of the Motor_Stop interrupt. */
#define Motor_Stop_INTC_PRIOR_NUMBER      Motor_Stop__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Motor_Stop interrupt. */
#define Motor_Stop_INTC_SET_EN            ((reg32 *) Motor_Stop__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Motor_Stop interrupt. */
#define Motor_Stop_INTC_CLR_EN            ((reg32 *) Motor_Stop__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Motor_Stop interrupt state to pending. */
#define Motor_Stop_INTC_SET_PD            ((reg32 *) Motor_Stop__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Motor_Stop interrupt. */
#define Motor_Stop_INTC_CLR_PD            ((reg32 *) Motor_Stop__INTC_CLR_PD_REG)


#endif /* CY_ISR_Motor_Stop_H */


/* [] END OF FILE */
