/*******************************************************************************
* File Name: HE_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "HE_Timer.h"

static HE_Timer_backupStruct HE_Timer_backup;


/*******************************************************************************
* Function Name: HE_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  HE_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HE_Timer_SaveConfig(void) 
{
    #if (!HE_Timer_UsingFixedFunction)
        HE_Timer_backup.TimerUdb = HE_Timer_ReadCounter();
        HE_Timer_backup.InterruptMaskValue = HE_Timer_STATUS_MASK;
        #if (HE_Timer_UsingHWCaptureCounter)
            HE_Timer_backup.TimerCaptureCounter = HE_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HE_Timer_UDB_CONTROL_REG_REMOVED)
            HE_Timer_backup.TimerControlRegister = HE_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HE_Timer_RestoreConfig
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
* Global variables:
*  HE_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HE_Timer_RestoreConfig(void) 
{   
    #if (!HE_Timer_UsingFixedFunction)

        HE_Timer_WriteCounter(HE_Timer_backup.TimerUdb);
        HE_Timer_STATUS_MASK =HE_Timer_backup.InterruptMaskValue;
        #if (HE_Timer_UsingHWCaptureCounter)
            HE_Timer_SetCaptureCount(HE_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HE_Timer_UDB_CONTROL_REG_REMOVED)
            HE_Timer_WriteControlRegister(HE_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HE_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  HE_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HE_Timer_Sleep(void) 
{
    #if(!HE_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HE_Timer_CTRL_ENABLE == (HE_Timer_CONTROL & HE_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HE_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HE_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HE_Timer_Stop();
    HE_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: HE_Timer_Wakeup
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
*  HE_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HE_Timer_Wakeup(void) 
{
    HE_Timer_RestoreConfig();
    #if(!HE_Timer_UDB_CONTROL_REG_REMOVED)
        if(HE_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HE_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
