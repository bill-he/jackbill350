/*******************************************************************************
* File: main.c
*
* Description: 
*	The HelloWorld project prints the string 'Hello World' on the character LCD
*	and blinks an LED.
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
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Start the LCD and PWM
*   2. Print 'Hello World' on the LCD
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
	/* Start LCD and PWM */
	LCD_Char_Start();
	PWM_Start();
	
	/* Print Hello World on LCD */

    /* Loop forever */
    char vout[15] = {'\0'};
	for(;;)
    {
        // TODO: get voltage at pot and control period of PWM using
        // PWM_WritePeriod(period)
        sprintf(vout, "%f", ADC_SAR_1_GetResult16());
        LCD_Char_PrintString(vout);
        vout[0] = '\0';
        
    }
}
/* End of main */


/* [] END OF FILE */
