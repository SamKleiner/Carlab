/*******************************************************************************
* File Name: Count_Lines_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Count_Lines.h"

static Count_Lines_backupStruct Count_Lines_backup;


/*******************************************************************************
* Function Name: Count_Lines_SaveConfig
********************************************************************************
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
*  Count_Lines_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Count_Lines_SaveConfig(void) 
{
    #if (!Count_Lines_UsingFixedFunction)

        Count_Lines_backup.CounterUdb = Count_Lines_ReadCounter();

        #if(!Count_Lines_ControlRegRemoved)
            Count_Lines_backup.CounterControlRegister = Count_Lines_ReadControlRegister();
        #endif /* (!Count_Lines_ControlRegRemoved) */

    #endif /* (!Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_RestoreConfig
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
*  Count_Lines_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Count_Lines_RestoreConfig(void) 
{      
    #if (!Count_Lines_UsingFixedFunction)

       Count_Lines_WriteCounter(Count_Lines_backup.CounterUdb);

        #if(!Count_Lines_ControlRegRemoved)
            Count_Lines_WriteControlRegister(Count_Lines_backup.CounterControlRegister);
        #endif /* (!Count_Lines_ControlRegRemoved) */

    #endif /* (!Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_Sleep
********************************************************************************
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
*  Count_Lines_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Count_Lines_Sleep(void) 
{
    #if(!Count_Lines_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Count_Lines_CTRL_ENABLE == (Count_Lines_CONTROL & Count_Lines_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Count_Lines_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Count_Lines_backup.CounterEnableState = 0u;
        }
    #else
        Count_Lines_backup.CounterEnableState = 1u;
        if(Count_Lines_backup.CounterEnableState != 0u)
        {
            Count_Lines_backup.CounterEnableState = 0u;
        }
    #endif /* (!Count_Lines_ControlRegRemoved) */
    
    Count_Lines_Stop();
    Count_Lines_SaveConfig();
}


/*******************************************************************************
* Function Name: Count_Lines_Wakeup
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
*  Count_Lines_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Count_Lines_Wakeup(void) 
{
    Count_Lines_RestoreConfig();
    #if(!Count_Lines_ControlRegRemoved)
        if(Count_Lines_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Count_Lines_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Count_Lines_ControlRegRemoved) */
    
}


/* [] END OF FILE */
