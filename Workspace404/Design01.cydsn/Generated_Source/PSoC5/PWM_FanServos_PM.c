/*******************************************************************************
* File Name: PWM_FanServos_PM.c
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

#include "PWM_FanServos.h"

static PWM_FanServos_backupStruct PWM_FanServos_backup;


/*******************************************************************************
* Function Name: PWM_FanServos_SaveConfig
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
*  PWM_FanServos_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_FanServos_SaveConfig(void) 
{

    #if(!PWM_FanServos_UsingFixedFunction)
        #if(!PWM_FanServos_PWMModeIsCenterAligned)
            PWM_FanServos_backup.PWMPeriod = PWM_FanServos_ReadPeriod();
        #endif /* (!PWM_FanServos_PWMModeIsCenterAligned) */
        PWM_FanServos_backup.PWMUdb = PWM_FanServos_ReadCounter();
        #if (PWM_FanServos_UseStatus)
            PWM_FanServos_backup.InterruptMaskValue = PWM_FanServos_STATUS_MASK;
        #endif /* (PWM_FanServos_UseStatus) */

        #if(PWM_FanServos_DeadBandMode == PWM_FanServos__B_PWM__DBM_256_CLOCKS || \
            PWM_FanServos_DeadBandMode == PWM_FanServos__B_PWM__DBM_2_4_CLOCKS)
            PWM_FanServos_backup.PWMdeadBandValue = PWM_FanServos_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_FanServos_KillModeMinTime)
             PWM_FanServos_backup.PWMKillCounterPeriod = PWM_FanServos_ReadKillTime();
        #endif /* (PWM_FanServos_KillModeMinTime) */

        #if(PWM_FanServos_UseControl)
            PWM_FanServos_backup.PWMControlRegister = PWM_FanServos_ReadControlRegister();
        #endif /* (PWM_FanServos_UseControl) */
    #endif  /* (!PWM_FanServos_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_FanServos_RestoreConfig
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
*  PWM_FanServos_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_FanServos_RestoreConfig(void) 
{
        #if(!PWM_FanServos_UsingFixedFunction)
            #if(!PWM_FanServos_PWMModeIsCenterAligned)
                PWM_FanServos_WritePeriod(PWM_FanServos_backup.PWMPeriod);
            #endif /* (!PWM_FanServos_PWMModeIsCenterAligned) */

            PWM_FanServos_WriteCounter(PWM_FanServos_backup.PWMUdb);

            #if (PWM_FanServos_UseStatus)
                PWM_FanServos_STATUS_MASK = PWM_FanServos_backup.InterruptMaskValue;
            #endif /* (PWM_FanServos_UseStatus) */

            #if(PWM_FanServos_DeadBandMode == PWM_FanServos__B_PWM__DBM_256_CLOCKS || \
                PWM_FanServos_DeadBandMode == PWM_FanServos__B_PWM__DBM_2_4_CLOCKS)
                PWM_FanServos_WriteDeadTime(PWM_FanServos_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_FanServos_KillModeMinTime)
                PWM_FanServos_WriteKillTime(PWM_FanServos_backup.PWMKillCounterPeriod);
            #endif /* (PWM_FanServos_KillModeMinTime) */

            #if(PWM_FanServos_UseControl)
                PWM_FanServos_WriteControlRegister(PWM_FanServos_backup.PWMControlRegister);
            #endif /* (PWM_FanServos_UseControl) */
        #endif  /* (!PWM_FanServos_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_FanServos_Sleep
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
*  PWM_FanServos_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_FanServos_Sleep(void) 
{
    #if(PWM_FanServos_UseControl)
        if(PWM_FanServos_CTRL_ENABLE == (PWM_FanServos_CONTROL & PWM_FanServos_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_FanServos_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_FanServos_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_FanServos_UseControl) */

    /* Stop component */
    PWM_FanServos_Stop();

    /* Save registers configuration */
    PWM_FanServos_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_FanServos_Wakeup
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
*  PWM_FanServos_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_FanServos_Wakeup(void) 
{
     /* Restore registers values */
    PWM_FanServos_RestoreConfig();

    if(PWM_FanServos_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_FanServos_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
