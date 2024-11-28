/*******************************************************************************
* File Name: UART_Mega_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Mega.h"


/***************************************
* Local data allocation
***************************************/

static UART_Mega_BACKUP_STRUCT  UART_Mega_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_Mega_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the UART_Mega_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Mega_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Mega_SaveConfig(void)
{
    #if(UART_Mega_CONTROL_REG_REMOVED == 0u)
        UART_Mega_backup.cr = UART_Mega_CONTROL_REG;
    #endif /* End UART_Mega_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Mega_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Mega_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling UART_Mega_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void UART_Mega_RestoreConfig(void)
{
    #if(UART_Mega_CONTROL_REG_REMOVED == 0u)
        UART_Mega_CONTROL_REG = UART_Mega_backup.cr;
    #endif /* End UART_Mega_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_Mega_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART_Mega_Sleep() API saves the current component state. Then it
*  calls the UART_Mega_Stop() function and calls 
*  UART_Mega_SaveConfig() to save the hardware configuration.
*  Call the UART_Mega_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Mega_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Mega_Sleep(void)
{
    #if(UART_Mega_RX_ENABLED || UART_Mega_HD_ENABLED)
        if((UART_Mega_RXSTATUS_ACTL_REG  & UART_Mega_INT_ENABLE) != 0u)
        {
            UART_Mega_backup.enableState = 1u;
        }
        else
        {
            UART_Mega_backup.enableState = 0u;
        }
    #else
        if((UART_Mega_TXSTATUS_ACTL_REG  & UART_Mega_INT_ENABLE) !=0u)
        {
            UART_Mega_backup.enableState = 1u;
        }
        else
        {
            UART_Mega_backup.enableState = 0u;
        }
    #endif /* End UART_Mega_RX_ENABLED || UART_Mega_HD_ENABLED*/

    UART_Mega_Stop();
    UART_Mega_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Mega_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART_Mega_Sleep() was called. The UART_Mega_Wakeup() function
*  calls the UART_Mega_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART_Mega_Sleep() function was called, the UART_Mega_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_Mega_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_Mega_Wakeup(void)
{
    UART_Mega_RestoreConfig();
    #if( (UART_Mega_RX_ENABLED) || (UART_Mega_HD_ENABLED) )
        UART_Mega_ClearRxBuffer();
    #endif /* End (UART_Mega_RX_ENABLED) || (UART_Mega_HD_ENABLED) */
    #if(UART_Mega_TX_ENABLED || UART_Mega_HD_ENABLED)
        UART_Mega_ClearTxBuffer();
    #endif /* End UART_Mega_TX_ENABLED || UART_Mega_HD_ENABLED */

    if(UART_Mega_backup.enableState != 0u)
    {
        UART_Mega_Enable();
    }
}


/* [] END OF FILE */
