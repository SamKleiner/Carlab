/*******************************************************************************
* File Name: Temp_received.h
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
#if !defined(CY_ISR_Temp_received_H)
#define CY_ISR_Temp_received_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Temp_received_Start(void);
void Temp_received_StartEx(cyisraddress address);
void Temp_received_Stop(void);

CY_ISR_PROTO(Temp_received_Interrupt);

void Temp_received_SetVector(cyisraddress address);
cyisraddress Temp_received_GetVector(void);

void Temp_received_SetPriority(uint8 priority);
uint8 Temp_received_GetPriority(void);

void Temp_received_Enable(void);
uint8 Temp_received_GetState(void);
void Temp_received_Disable(void);

void Temp_received_SetPending(void);
void Temp_received_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Temp_received ISR. */
#define Temp_received_INTC_VECTOR            ((reg32 *) Temp_received__INTC_VECT)

/* Address of the Temp_received ISR priority. */
#define Temp_received_INTC_PRIOR             ((reg8 *) Temp_received__INTC_PRIOR_REG)

/* Priority of the Temp_received interrupt. */
#define Temp_received_INTC_PRIOR_NUMBER      Temp_received__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Temp_received interrupt. */
#define Temp_received_INTC_SET_EN            ((reg32 *) Temp_received__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Temp_received interrupt. */
#define Temp_received_INTC_CLR_EN            ((reg32 *) Temp_received__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Temp_received interrupt state to pending. */
#define Temp_received_INTC_SET_PD            ((reg32 *) Temp_received__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Temp_received interrupt. */
#define Temp_received_INTC_CLR_PD            ((reg32 *) Temp_received__INTC_CLR_PD_REG)


#endif /* CY_ISR_Temp_received_H */


/* [] END OF FILE */
