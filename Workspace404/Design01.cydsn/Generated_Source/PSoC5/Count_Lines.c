/*******************************************************************************
* File Name: Count_Lines.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 Count_Lines_initVar = 0u;


/*******************************************************************************
* Function Name: Count_Lines_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Count_Lines_Init(void) 
{
        #if (!Count_Lines_UsingFixedFunction && !Count_Lines_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Count_Lines_UsingFixedFunction && !Count_Lines_ControlRegRemoved) */
        
        #if(!Count_Lines_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Count_Lines_interruptState;
        #endif /* (!Count_Lines_UsingFixedFunction) */
        
        #if (Count_Lines_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Count_Lines_CONTROL &= Count_Lines_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Count_Lines_CONTROL2 &= ((uint8)(~Count_Lines_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Count_Lines_CONTROL3 &= ((uint8)(~Count_Lines_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Count_Lines_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Count_Lines_CONTROL |= Count_Lines_ONESHOT;
            #endif /* (Count_Lines_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Count_Lines_CONTROL2 |= Count_Lines_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Count_Lines_RT1 &= ((uint8)(~Count_Lines_RT1_MASK));
            Count_Lines_RT1 |= Count_Lines_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Count_Lines_RT1 &= ((uint8)(~Count_Lines_SYNCDSI_MASK));
            Count_Lines_RT1 |= Count_Lines_SYNCDSI_EN;

        #else
            #if(!Count_Lines_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Count_Lines_CONTROL & ((uint8)(~Count_Lines_CTRL_CMPMODE_MASK));
            Count_Lines_CONTROL = ctrl | Count_Lines_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Count_Lines_CONTROL & ((uint8)(~Count_Lines_CTRL_CAPMODE_MASK));
            
            #if( 0 != Count_Lines_CAPTURE_MODE_CONF)
                Count_Lines_CONTROL = ctrl | Count_Lines_DEFAULT_CAPTURE_MODE;
            #else
                Count_Lines_CONTROL = ctrl;
            #endif /* 0 != Count_Lines_CAPTURE_MODE */ 
            
            #endif /* (!Count_Lines_ControlRegRemoved) */
        #endif /* (Count_Lines_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Count_Lines_UsingFixedFunction)
            Count_Lines_ClearFIFO();
        #endif /* (!Count_Lines_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Count_Lines_WritePeriod(Count_Lines_INIT_PERIOD_VALUE);
        #if (!(Count_Lines_UsingFixedFunction && (CY_PSOC5A)))
            Count_Lines_WriteCounter(Count_Lines_INIT_COUNTER_VALUE);
        #endif /* (!(Count_Lines_UsingFixedFunction && (CY_PSOC5A))) */
        Count_Lines_SetInterruptMode(Count_Lines_INIT_INTERRUPTS_MASK);
        
        #if (!Count_Lines_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Count_Lines_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Count_Lines_WriteCompare(Count_Lines_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Count_Lines_interruptState = CyEnterCriticalSection();
            
            Count_Lines_STATUS_AUX_CTRL |= Count_Lines_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Count_Lines_interruptState);
            
        #endif /* (!Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void Count_Lines_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Count_Lines_UsingFixedFunction)
        Count_Lines_GLOBAL_ENABLE |= Count_Lines_BLOCK_EN_MASK;
        Count_Lines_GLOBAL_STBY_ENABLE |= Count_Lines_BLOCK_STBY_EN_MASK;
    #endif /* (Count_Lines_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Count_Lines_ControlRegRemoved || Count_Lines_UsingFixedFunction)
        Count_Lines_CONTROL |= Count_Lines_CTRL_ENABLE;                
    #endif /* (!Count_Lines_ControlRegRemoved || Count_Lines_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Count_Lines_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Count_Lines_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Count_Lines_Start(void) 
{
    if(Count_Lines_initVar == 0u)
    {
        Count_Lines_Init();
        
        Count_Lines_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Count_Lines_Enable();        
}


/*******************************************************************************
* Function Name: Count_Lines_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Count_Lines_Stop(void) 
{
    /* Disable Counter */
    #if(!Count_Lines_ControlRegRemoved || Count_Lines_UsingFixedFunction)
        Count_Lines_CONTROL &= ((uint8)(~Count_Lines_CTRL_ENABLE));        
    #endif /* (!Count_Lines_ControlRegRemoved || Count_Lines_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Count_Lines_UsingFixedFunction)
        Count_Lines_GLOBAL_ENABLE &= ((uint8)(~Count_Lines_BLOCK_EN_MASK));
        Count_Lines_GLOBAL_STBY_ENABLE &= ((uint8)(~Count_Lines_BLOCK_STBY_EN_MASK));
    #endif /* (Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void Count_Lines_SetInterruptMode(uint8 interruptsMask) 
{
    Count_Lines_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Count_Lines_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Count_Lines_ReadStatusRegister(void) 
{
    return Count_Lines_STATUS;
}


#if(!Count_Lines_ControlRegRemoved)
/*******************************************************************************
* Function Name: Count_Lines_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   Count_Lines_ReadControlRegister(void) 
{
    return Count_Lines_CONTROL;
}


/*******************************************************************************
* Function Name: Count_Lines_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    Count_Lines_WriteControlRegister(uint8 control) 
{
    Count_Lines_CONTROL = control;
}

#endif  /* (!Count_Lines_ControlRegRemoved) */


#if (!(Count_Lines_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Count_Lines_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Count_Lines_WriteCounter(uint16 counter) \
                                   
{
    #if(Count_Lines_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Count_Lines_GLOBAL_ENABLE & Count_Lines_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Count_Lines_GLOBAL_ENABLE |= Count_Lines_BLOCK_EN_MASK;
        CY_SET_REG16(Count_Lines_COUNTER_LSB_PTR, (uint16)counter);
        Count_Lines_GLOBAL_ENABLE &= ((uint8)(~Count_Lines_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(Count_Lines_COUNTER_LSB_PTR, counter);
    #endif /* (Count_Lines_UsingFixedFunction) */
}
#endif /* (!(Count_Lines_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Count_Lines_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 Count_Lines_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Count_Lines_UsingFixedFunction)
		(void)CY_GET_REG16(Count_Lines_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Count_Lines_COUNTER_LSB_PTR_8BIT);
	#endif/* (Count_Lines_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Count_Lines_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Count_Lines_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(Count_Lines_STATICCOUNT_LSB_PTR));
    #endif /* (Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 Count_Lines_ReadCapture(void) 
{
    #if(Count_Lines_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Count_Lines_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(Count_Lines_STATICCOUNT_LSB_PTR));
    #endif /* (Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Count_Lines_WritePeriod(uint16 period) 
{
    #if(Count_Lines_UsingFixedFunction)
        CY_SET_REG16(Count_Lines_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(Count_Lines_PERIOD_LSB_PTR, period);
    #endif /* (Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 Count_Lines_ReadPeriod(void) 
{
    #if(Count_Lines_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Count_Lines_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Count_Lines_PERIOD_LSB_PTR));
    #endif /* (Count_Lines_UsingFixedFunction) */
}


#if (!Count_Lines_UsingFixedFunction)
/*******************************************************************************
* Function Name: Count_Lines_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void Count_Lines_WriteCompare(uint16 compare) \
                                   
{
    #if(Count_Lines_UsingFixedFunction)
        CY_SET_REG16(Count_Lines_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(Count_Lines_COMPARE_LSB_PTR, compare);
    #endif /* (Count_Lines_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Count_Lines_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 Count_Lines_ReadCompare(void) 
{
    return (CY_GET_REG16(Count_Lines_COMPARE_LSB_PTR));
}


#if (Count_Lines_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Count_Lines_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Count_Lines_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Count_Lines_CONTROL &= ((uint8)(~Count_Lines_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Count_Lines_CONTROL |= compareMode;
}
#endif  /* (Count_Lines_COMPARE_MODE_SOFTWARE) */


#if (Count_Lines_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Count_Lines_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Count_Lines_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Count_Lines_CONTROL &= ((uint8)(~Count_Lines_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Count_Lines_CONTROL |= ((uint8)((uint8)captureMode << Count_Lines_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Count_Lines_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Count_Lines_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void Count_Lines_ClearFIFO(void) 
{

    while(0u != (Count_Lines_ReadStatusRegister() & Count_Lines_STATUS_FIFONEMP))
    {
        (void)Count_Lines_ReadCapture();
    }

}
#endif  /* (!Count_Lines_UsingFixedFunction) */


/* [] END OF FILE */

