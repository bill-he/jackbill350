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
#include <project.h>

void MCP41010_Write(unsigned char value) 
{
  SPI_CS_Write(0);
  SPI_WriteTxData(0b00010001); // This tells the chip to set the pot
  SPI_WriteTxData(value);     // This tells it the pot position
  SPI_CS_Write(1);
  LED_Write(LED_Read() ^ 1);
  LCD_Position(1, 0);
  LCD_PrintInt8(value);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPI_Start();
    
    LCD_Start();
    LCD_Position(0u,0u);
    LCD_PrintString("value:");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
       // move the potentiometer in one direction
        int level;
          for (level = 0; level < 255; level++) 
          {
            MCP41010_Write(0);
            CyDelay(100); //delay(100);
          }
          CyDelay(2000); //delay(2000);  // wait a couple seconds
          // Now mover potentiometer in other directions
          
          for (level = 255; level > 0; level--) 
          {
            MCP41010_Write(0);
            CyDelay(100); //delay(100);
          }
          CyDelay(2000); //delay(2000);
    }
}

/* [] END OF FILE */
