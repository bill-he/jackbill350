/*******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description:
*  The SAR ADC and PrISM datasheet example project.
*  This example project demonstrates SAR ADC measurements and transferring
*  results using ISR and DMA to the LCD and PrISM.
*
* Note:
*  Pin_Vin pin (P1[4]) should be connected to the VR.
*  Pin_LED pin (P1[6]) should be connected to the LED.
*  Verify that VR_PWR(J11) is jumpered to ON.
*
* Hardware Dependency:
*  CY8C55 Family Processor
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
#include <stdio.h>
#include <stdlib.h>
#include "FunctionGenerator.h"
#include "Serial.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

void trimString(char *str)
{
  int i;
  
  // trim leading whitespace
  for (i = 0; str[i] != '\0'; i++) {
    if (!isspace(str[i])) {
      break;
    }
  }
  
  // copy string w/o leading whitespace
  // (don't read beyond the end of the input buffer)
  memmove(str, str + i, strlen(str) + 1 - i);
  
  // trim trailing whitespace
  i = strlen(str) - 1; // index of last character
  
  // Edge case: string is empty
  if (i == -1) {
    str[0] = '\0';
    return;
  }
  
  do {
    if (!isspace(str[i])) {
      break;
    }
    i--;
  } while (i >= 0);
  
  str[i + 1] = '\0';
}

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Initialises the DMA to move data from ADC_SAR_1 work registers to the
*      PrISM pulse density registers.
*   2. Initialises the ISR connected to the DMA nrq terminal(DMA done).
*   3. Initialises the LCD.
*   4. Initialises the PrISM with 1Mhz clock.
*   5. Initialises the two SAR ADCs.
*   6. Displays the results of ADC_SAR_1 when DmaDone ISR rises.
*      The results are read from PrISM pulse density register.
*   7. Displays the results of ADC_SAR_2 when internal EOC ISR rises.
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
    char freq0Disp[16], freq1Disp[16];
    char usbRx[USBUART_BUFFER_SIZE], usbTx[USBUART_BUFFER_SIZE];
    
    
    /* Initializes the LCD. */
    LCD_Start();
    LCD_Position(1u,0u);
    LCD_Position(0u,0u);
    LCD_PrintString("F1=");
    
    WaveDAC_0_Clock_Start();
    WaveDAC_1_Clock_Start();
    
    // Needed for WaveDACs to operate concurrently
    // I think this might be a bug with PSoC
    WaveDAC_0_Start();
    WaveDAC_1_Start(); 
    WaveDAC_0_Stop();
    WaveDAC_1_Stop();

    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    USBUART_CDC_Init();
    
    CyGlobalIntEnable;

    while (1) {
        if (USBUART_IsConfigurationChanged()) {
            if (USBUART_GetConfiguration()) {
                USBUART_CDC_Init();
            }
        }
        
        if (USBUART_GetConfiguration()) {
            if (USBUART_DataIsReady()) {
                int numArgs;
                int desiredFreq, newFreq, fnGenerator;
                char mode[USBUART_BUFFER_SIZE] = {0};
                
                Serial_GetString(usbRx);
                trimString(usbRx);
                numArgs = sscanf(usbRx, "%d %s %d", &fnGenerator, mode, &desiredFreq);
                if (numArgs == 3) {
                    if (!strcmp(mode, "square")) { 
                        newFreq = changeFrequency(desiredFreq, SQUARE, fnGenerator);
                        sprintf(usbTx, "fn = %d, mode = %s, newFreq = %d\r\n", fnGenerator, mode, newFreq);
                    } else if (!strcmp(mode, "sine")) { 
                        newFreq = changeFrequency(desiredFreq, SINE, fnGenerator);
                        sprintf(usbTx, "fn = %d, mode = %s, newFreq = %d\r\n", fnGenerator, mode, newFreq);
                    } else if (!strcmp(mode, "triangle")) { 
                        newFreq = changeFrequency(desiredFreq, TRIANGLE, fnGenerator);
                        sprintf(usbTx, "fn = %d, mode = %s, newFreq = %d\r\n", fnGenerator, mode, newFreq);
                    } else if (!strcmp(mode, "sawtooth")) { 
                        newFreq = changeFrequency(desiredFreq, SAWTOOTH, fnGenerator);
                        sprintf(usbTx, "fn = %d, mode = %s, newFreq = %d\r\n", fnGenerator, mode, newFreq);
                    } else if (!strcmp(mode, "dc")) { 
                        newFreq = changeFrequency(desiredFreq, DC, fnGenerator);
                        sprintf(usbTx, "fn = %d, mode = %s, newFreq = %d\r\n", fnGenerator, mode, newFreq);
                    } else {
                        sprintf(usbTx, "Invalid mode: %s\r\n", mode);
                    }
                    
                    
                } else if (numArgs == 2) {
                    if (!strcmp(mode, "off")) {
                        if (fnGenerator == 0) {
                            stopWaveDac(WAVEDAC_LOW_0);
                        } else if (fnGenerator == 1) {
                            stopWaveDac(WAVEDAC_LOW_1);   
                        }
                        sprintf(usbTx, "Stopped WaveDAC %d\r\n", fnGenerator);
                    } else {
                        sprintf(usbTx, "Invalid mode: %s\r\n", mode);
                    }
                } else {
                    sprintf(usbTx, "Invalid command: %s\r\n", usbRx);
                }
                
                Serial_PutString(usbTx);
            }
        }
    }
}


/* [] END OF FILE */
