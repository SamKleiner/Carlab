/*******************************************************************************
* File Name: Ref_PM.c  
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

#include "Ref.h"

static Ref_backupStruct Ref_backup;


/*******************************************************************************
* Function Name: Ref_SaveConfig
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
void Ref_SaveConfig(void) 
{
    if (!((Ref_CR1 & Ref_SRC_MASK) == Ref_SRC_UDB))
    {
        Ref_backup.data_value = Ref_Data;
    }
}


/*******************************************************************************
* Function Name: Ref_RestoreConfig
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
void Ref_RestoreConfig(void) 
{
    if (!((Ref_CR1 & Ref_SRC_MASK) == Ref_SRC_UDB))
    {
        if((Ref_Strobe & Ref_STRB_MASK) == Ref_STRB_EN)
        {
            Ref_Strobe &= (uint8)(~Ref_STRB_MASK);
            Ref_Data = Ref_backup.data_value;
            Ref_Strobe |= Ref_STRB_EN;
        }
        else
        {
            Ref_Data = Ref_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Ref_Sleep
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
*  Ref_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Ref_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Ref_ACT_PWR_EN == (Ref_PWRMGR & Ref_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Ref_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Ref_backup.enableState = 0u;
    }
    
    Ref_Stop();
    Ref_SaveConfig();
}


/*******************************************************************************
* Function Name: Ref_Wakeup
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
*  Ref_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ref_Wakeup(void) 
{
    Ref_RestoreConfig();
    
    if(Ref_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Ref_Enable();

        /* Restore the data register */
        Ref_SetValue(Ref_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
