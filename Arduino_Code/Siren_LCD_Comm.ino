#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(BLUE);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(30, 10, "FIRE", &Font24, BLUE, RED);
}
void loop()
{
  Paint_DrawString_EN(30, 10, "123", &Font24, BLUE, RED);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
