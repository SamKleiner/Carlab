/*******************************************************************************
* File Name: Ref.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Ref.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Ref_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Ref_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Ref_backupStruct Ref_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Ref_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Ref_Init(void) 
{
    Ref_CR0 = (Ref_MODE_V );

    /* Set default data source */
    #if(Ref_DEFAULT_DATA_SRC != 0 )
        Ref_CR1 = (Ref_DEFAULT_CNTL | Ref_DACBUS_ENABLE) ;
    #else
        Ref_CR1 = (Ref_DEFAULT_CNTL | Ref_DACBUS_DISABLE) ;
    #endif /* (Ref_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Ref_DEFAULT_STRB != 0)
        Ref_Strobe |= Ref_STRB_EN ;
    #endif/* (Ref_DEFAULT_STRB != 0) */

    /* Set default range */
    Ref_SetRange(Ref_DEFAULT_RANGE); 

    /* Set default speed */
    Ref_SetSpeed(Ref_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Ref_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Ref_Enable(void) 
{
    Ref_PWRMGR |= Ref_ACT_PWR_EN;
    Ref_STBY_PWRMGR |= Ref_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Ref_restoreVal == 1u) 
        {
             Ref_CR0 = Ref_backup.data_value;
             Ref_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Ref_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  Ref_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Ref_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Ref_initVar == 0u)
    { 
        Ref_Init();
        Ref_initVar = 1u;
    }

    /* Enable power to DAC */
    Ref_Enable();

    /* Set default value */
    Ref_SetValue(Ref_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Ref_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Ref_Stop(void) 
{
    /* Disble power to DAC */
    Ref_PWRMGR &= (uint8)(~Ref_ACT_PWR_EN);
    Ref_STBY_PWRMGR &= (uint8)(~Ref_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Ref_backup.data_value = Ref_CR0;
        Ref_CR0 = Ref_CUR_MODE_OUT_OFF;
        Ref_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Ref_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Ref_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Ref_CR0 &= (uint8)(~Ref_HS_MASK);
    Ref_CR0 |=  (speed & Ref_HS_MASK);
}


/*******************************************************************************
* Function Name: Ref_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Ref_SetRange(uint8 range) 
{
    Ref_CR0 &= (uint8)(~Ref_RANGE_MASK);      /* Clear existing mode */
    Ref_CR0 |= (range & Ref_RANGE_MASK);      /*  Set Range  */
    Ref_DacTrim();
}


/*******************************************************************************
* Function Name: Ref_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Ref_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Ref_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Ref_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Ref_Data = value;
        CyExitCriticalSection(Ref_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Ref_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Ref_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Ref_CR0 & Ref_RANGE_MASK) >> 2) + Ref_TRIM_M7_1V_RNG_OFFSET;
    Ref_TR = CY_GET_XTND_REG8((uint8 *)(Ref_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
