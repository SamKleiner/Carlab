/*******************************************************************************
* File Name: PWM_IRServo_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_IRServo.h"

static PWM_IRServo_backupStruct PWM_IRServo_backup;


/*******************************************************************************
* Function Name: PWM_IRServo_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_IRServo_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_IRServo_SaveConfig(void) 
{

    #if(!PWM_IRServo_UsingFixedFunction)
        #if(!PWM_IRServo_PWMModeIsCenterAligned)
            PWM_IRServo_backup.PWMPeriod = PWM_IRServo_ReadPeriod();
        #endif /* (!PWM_IRServo_PWMModeIsCenterAligned) */
        PWM_IRServo_backup.PWMUdb = PWM_IRServo_ReadCounter();
        #if (PWM_IRServo_UseStatus)
            PWM_IRServo_backup.InterruptMaskValue = PWM_IRServo_STATUS_MASK;
        #endif /* (PWM_IRServo_UseStatus) */

        #if(PWM_IRServo_DeadBandMode == PWM_IRServo__B_PWM__DBM_256_CLOCKS || \
            PWM_IRServo_DeadBandMode == PWM_IRServo__B_PWM__DBM_2_4_CLOCKS)
            PWM_IRServo_backup.PWMdeadBandValue = PWM_IRServo_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_IRServo_KillModeMinTime)
             PWM_IRServo_backup.PWMKillCounterPeriod = PWM_IRServo_ReadKillTime();
        #endif /* (PWM_IRServo_KillModeMinTime) */

        #if(PWM_IRServo_UseControl)
            PWM_IRServo_backup.PWMControlRegister = PWM_IRServo_ReadControlRegister();
        #endif /* (PWM_IRServo_UseControl) */
    #endif  /* (!PWM_IRServo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_IRServo_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_IRServo_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_IRServo_RestoreConfig(void) 
{
        #if(!PWM_IRServo_UsingFixedFunction)
            #if(!PWM_IRServo_PWMModeIsCenterAligned)
                PWM_IRServo_WritePeriod(PWM_IRServo_backup.PWMPeriod);
            #endif /* (!PWM_IRServo_PWMModeIsCenterAligned) */

            PWM_IRServo_WriteCounter(PWM_IRServo_backup.PWMUdb);

            #if (PWM_IRServo_UseStatus)
                PWM_IRServo_STATUS_MASK = PWM_IRServo_backup.InterruptMaskValue;
            #endif /* (PWM_IRServo_UseStatus) */

            #if(PWM_IRServo_DeadBandMode == PWM_IRServo__B_PWM__DBM_256_CLOCKS || \
                PWM_IRServo_DeadBandMode == PWM_IRServo__B_PWM__DBM_2_4_CLOCKS)
                PWM_IRServo_WriteDeadTime(PWM_IRServo_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_IRServo_KillModeMinTime)
                PWM_IRServo_WriteKillTime(PWM_IRServo_backup.PWMKillCounterPeriod);
            #endif /* (PWM_IRServo_KillModeMinTime) */

            #if(PWM_IRServo_UseControl)
                PWM_IRServo_WriteControlRegister(PWM_IRServo_backup.PWMControlRegister);
            #endif /* (PWM_IRServo_UseControl) */
        #endif  /* (!PWM_IRServo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_IRServo_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_IRServo_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_IRServo_Sleep(void) 
{
    #if(PWM_IRServo_UseControl)
        if(PWM_IRServo_CTRL_ENABLE == (PWM_IRServo_CONTROL & PWM_IRServo_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_IRServo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_IRServo_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_IRServo_UseControl) */

    /* Stop component */
    PWM_IRServo_Stop();

    /* Save registers configuration */
    PWM_IRServo_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_IRServo_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_IRServo_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_IRServo_Wakeup(void) 
{
     /* Restore registers values */
    PWM_IRServo_RestoreConfig();

    if(PWM_IRServo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_IRServo_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
