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

#include "serial.h"

extern int USBUART_GetChar();
extern void USBUART_PutString(char *str);
extern int USBUART_DataIsReady();
extern int USBUART_CDCIsReady();
extern int USBUART_GetConfiguration();

void Serial_PutString(char *str)
{
    //while (!USBUART_GetConfiguration());
    while (!USBUART_CDCIsReady());
    USBUART_PutString(str);
}

void Serial_GetString(char *str)
{
    int count = 0;
    while (1) {
        //while (!USBUART_GetConfiguration());
        while (!USBUART_DataIsReady());
        char c = USBUART_GetChar();
        str[count] = c;
        
        if (c == '\r') {
            str[count + 1] = '\0'; // add null terminator
            return;
        }
        count++;
    }
}

/* [] END OF FILE */
