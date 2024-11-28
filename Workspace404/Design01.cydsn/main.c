  /* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool servo_set = false;
bool flame_found = false;

uint16 old_time = 65535;
uint16 new_time = 0;
uint16 dt = 0;
double oldspeed = 0;
double speed = 0;
double target = 4; 
double n0 = 50;
double n = 50;
double error = 0;
double integration = 0;
double derivative = 0;
double Kp = 80;
double Ki = 1;
double Kd = 0;
double diameter = .216535; 

double percent;
char strbuf2[16];
double PWM_Steer; 
double kp = -0.2;
double kd = -0.2;
uint16 new_timet;

/*
CY_ISR(interCounter) {
    uint16 captureVal;
    char strbuf[16];
    
    captureVal = Timer_ReadCapture();
    
    sprintf(strbuf, "Count: %u", captureVal);
    
    char strbuf2[32];
    sprintf(strbuf2,"%s\r\n",strbuf);
    UART_PutString(strbuf2);
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString(strbuf);
    
    PWM_Motor_WriteCompare((uint8_t) 20);
} */
    
/*
CY_ISR(control) {
    char strbuf[32];
  
    new_time = HE_Timer_ReadCapture();
    HE_Timer_ReadStatusRegister();
    
    if (old_time > new_time){
        dt = old_time - new_time;
    } else{
        dt = 65535 - new_time + old_time;
    }
    old_time = new_time;
    speed = 1300/(double)dt;
    error = target - speed;
    integration = integration + error;
    derivative = (speed - oldspeed)/(double)dt;
    if (speed != 0) {
        oldspeed = speed;
    }
    n = n0 + Kp*error + Ki*integration + Kd*derivative;
    if (n > 220) {
        n = 220;
    }
    if (n < 0) {
        n = 0;
    }
    PWM_Motor_WriteCompare((uint8_t) n);
    
    sprintf(strbuf, "Speed: %lf\r\n", speed);
    UART_PutString(strbuf);
    oldspeed = speed;
}
*/
CY_ISR(tempCheck) {
    /*char receivedData[50]; // Buffer to store received data
    int index = 0;
    int count = 0; // count of turns 0 = center, 1 = left, 2 = right
    // 58 is center, 32 is right, 86 is left
    if (count == 0) {
        PWM_IRServo_WriteCompare((uint8) 58);
        char receivedChar = UART_Mega_ReadRxData();
        if (receivedChar == 1) {
            flame_found = true; // if 1 flame found 
        } */
        /*else {
            PWM_IRServo_WriteCompare((uint8) 86);
            count = 1;
        }*/
     //}
    /*else if (count == 1) {
        PWM_IRServo_WriteCompare((uint8) 86);
        char receivedChar = UART_Mega_ReadRxData();
        count = 2;
    }
    else {
        PWM_IRServo_WriteCompare((uint8) 86);
        char receivedChar = UART_Mega_ReadRxData();
    } */
    //servo_set = false;
}

CY_ISR(turn) {
    // new_timet is the time from the edge of the line of video to the left edge of the black line 
    new_timet = 65535 - Timer_Edge_ReadCapture();
    
    sprintf(strbuf2, "Count: %u \r\n", new_timet);
    UART_PutString(strbuf2);
    
    /* 487 is the count for the timer that represents straight 
    Only the error term was needed to complete PID control */
    PWM_Steer = 110 + kp * (487 - (double)new_timet) + kd * (speed - oldspeed);
    oldspeed = speed;
    speed = PWM_Steer;
    sprintf(strbuf2, "PWM: %f \r\n", PWM_Steer);
    UART_PutString(strbuf2);
        
    PWM_Servo_WriteCompare((uint8)PWM_Steer);
    Timer_Edge_ReadStatusRegister();
}

CY_ISR(stop) {
    PWM_Motor_WriteCompare((uint8_t) 0);
    flame_found = true;
}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Hello World");
    PWM_Motor_Start();
    Timer_Edge_Start();
    PWM_Servo_Start();
    Comp_Black_Start();
    PWM_Fan_Start();
    PWM_FanServos_Start();
    PWM_IRServo_Start();
    Ref_Start();
    Timer_Motor_Start();
    Motor_Stop_Start();
    Motor_Stop_SetVector(stop);
    UART_Mega_Start();
    //UART_Mega_Sleep();
    turn_Start();
    turn_SetVector(turn);
    //Temp_received_Start();
    //Temp_received_SetVector(tempCheck);
    char strbuf2[32];
    sprintf(strbuf2,"test\r\n");
    UART_PutString(strbuf2);
    // 2 = stop going forward flame was found and now is not, 1 = flame found, 0 = flame not found 
    //Uart_mega send temp from left, then psoc send turn finished, 
    // mega send highest, psoc send turn finidhed (no on the right mega send temp
    //if flame found at any of them, break from flame search loop.
    // 58 is center, 32 is right, 86 is left
    //centered
    PWM_Motor_WriteCompare((uint8_t) 40);
    PWM_FanServos_WriteCompare1((uint8) 58); // right fan from back view
    PWM_FanServos_WriteCompare2((uint8) 58); //left fan from back view
    PWM_IRServo_WriteCompare((uint8) 58);
    for(;;)
    {
        /* Place your application code here. */
        double rpm = 0;
        /*
        if (servo_set) { //Want UART only receiving when the IR camera is set in position
            UART_Mega_Wakeup();
        } */
        /* if the flame is close, point the servos */
        /* if the flame is found, turn on the fans */
        UART_Mega_PutChar(0);
        if (flame_found) {
            //centered
            if (!servo_set) {
            PWM_FanServos_WriteCompare1((uint8) 69); // right fan from back view
            PWM_FanServos_WriteCompare2((uint8) 47); //left fan from back view\
            servo_set = true;
            }
            rpm = 254;
            //blowing
            PWM_Fan_WriteCompare1((uint8) rpm);
            PWM_Fan_WriteCompare2((uint8) rpm);
            UART_Mega_PutChar(1);
        }
    }
}

/* [] END OF FILE */
