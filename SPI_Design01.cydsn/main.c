/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is source code for example project of the SPI
*  (Master, Slave) components.
*  Parameters used:
*   Mode                0(CPHA ==0, CPOL ==0)                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits:           8 
*   Bit Rate            1Mbit/s
*   Clock source        External 
*
*  SPI communication test using software buffer. 8 bytes are transmitted
*  between SPI Master and SPI Slave.
*  Received data are displayed on LCD. 
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>


void MCP41010_Write(unsigned char value) 
{
  //CS_Write(0);
  SPIM_WriteTxData(0b00010001); // This tells the chip to set the pot
  SPIM_WriteTxData(value);     // This tells it the pot position
  //CS_Write(1);
  LCD_Position(1, 0);
  LCD_PrintInt8(value);
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Declares cycle counter variable.
*   2. Enables interrupts.
*   3. Starts all used components.
*   3. Writes values to be sent into the SPI Slave's and Master's input buffers.
*   4. Waits for the Slave's SPI Done state generation.
*   5. Displays SPI Master and Slave received data.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint8 i = 0u;
    
    /* Software buffers use internal interrupt functionality to interact with
    * hardware buffers. Thus global interrupt enable command should be called 
    */
    CyGlobalIntEnable;
    
    /* We need to start Character LCD, SPI Master and Slave components */
    LCD_Start();
    SPIM_Start();
    
    LCD_ClearDisplay();
    LCD_Position(0u,0u);
    LCD_PrintString("value:");
    LCD_Position(1u,0u);
    
    while(1) {
       // move the potentiometer in one direction
        int level;
          for (level = 0; level < 255; level++) 
          {
            MCP41010_Write(level);
            CyDelay(100); //delay(100);
          }
          CyDelay(2000); //delay(2000);  // wait a couple seconds
          // Now mover potentiometer in other directions
          
          for (level = 255; level > 0; level--) 
          {
            MCP41010_Write(level);
            CyDelay(100); //delay(100);
          }
          CyDelay(2000); //delay(2000);
        }   
      
}    


/* [] END OF FILE */
