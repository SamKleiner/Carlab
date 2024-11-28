/*******************************************************************************
* File Name: Ref2_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Ref2.h"

static Ref2_backupStruct Ref2_backup;


/*******************************************************************************
* Function Name: Ref2_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Ref2_SaveConfig(void) 
{
    if (!((Ref2_CR1 & Ref2_SRC_MASK) == Ref2_SRC_UDB))
    {
        Ref2_backup.data_value = Ref2_Data;
    }
}


/*******************************************************************************
* Function Name: Ref2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Ref2_RestoreConfig(void) 
{
    if (!((Ref2_CR1 & Ref2_SRC_MASK) == Ref2_SRC_UDB))
    {
        if((Ref2_Strobe & Ref2_STRB_MASK) == Ref2_STRB_EN)
        {
            Ref2_Strobe &= (uint8)(~Ref2_STRB_MASK);
            Ref2_Data = Ref2_backup.data_value;
            Ref2_Strobe |= Ref2_STRB_EN;
        }
        else
        {
            Ref2_Data = Ref2_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Ref2_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Ref2_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Ref2_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Ref2_ACT_PWR_EN == (Ref2_PWRMGR & Ref2_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Ref2_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Ref2_backup.enableState = 0u;
    }
    
    Ref2_Stop();
    Ref2_SaveConfig();
}


/*******************************************************************************
* Function Name: Ref2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Ref2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ref2_Wakeup(void) 
{
    Ref2_RestoreConfig();
    
    if(Ref2_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Ref2_Enable();

        /* Restore the data register */
        Ref2_SetValue(Ref2_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
