/*******************************************************************************
* File Name: Comp_Black2.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Comp_Black2.h"

static Comp_Black2_backupStruct Comp_Black2_backup;


/*******************************************************************************
* Function Name: Comp_Black2_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Comp_Black2_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp_Black2_RestoreConfig
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
********************************************************************************/
void Comp_Black2_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp_Black2_Sleep
********************************************************************************
*
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
*  Comp_Black2_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp_Black2_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp_Black2_ACT_PWR_EN == (Comp_Black2_PWRMGR & Comp_Black2_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp_Black2_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp_Black2_backup.enableState = 0u;
    }    
    
    Comp_Black2_Stop();
    Comp_Black2_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp_Black2_Wakeup
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
*  Comp_Black2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp_Black2_Wakeup(void) 
{
    Comp_Black2_RestoreConfig();
    
    if(Comp_Black2_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp_Black2_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
