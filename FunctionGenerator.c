/* ========================================
 *
 * Copyright 2016 John Harkins and Li He
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <math.h>
#include "FunctionGenerator.h"

extern void WaveDAC_0_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart);
extern void WaveDAC_1_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart);
extern void WaveDAC_0_Stop();
extern void WaveDAC_1_Stop();
extern void WaveDAC_0_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, 
                                   const uint8 * wavePtr2, uint16 sampleSize2);
extern void WaveDAC_1_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, 
                                   const uint8 * wavePtr2, uint16 sampleSize2);

uint8 waveform0[MAX_NUM_SAMPLES];
uint8 waveform1[MAX_NUM_SAMPLES];

void stopWaveDac(int fnGenerator)
{
    switch (fnGenerator) {
        case WAVEDAC_LOW_0:
        case WAVEDAC_HIGH_0:
            WaveDAC_0_Stop();
            break;
        case WAVEDAC_LOW_1:
        case WAVEDAC_HIGH_1:
            WaveDAC_1_Stop();
            break;
    }   
}

void startWaveDac(int numSamples, int fnGenerator, uint8 *waveform)
{    
    switch (fnGenerator) {
        case WAVEDAC_LOW_0:
            WaveDAC_0_Clock_SetDividerRegister(LOW_DIVIDER_REGISTER, 1);
            WaveDAC_0_StartEx(waveform, numSamples, NULL, 0);
            break;
        case WAVEDAC_HIGH_0:
            WaveDAC_0_Clock_SetDividerRegister(HIGH_DIVIDER_REGISTER, 1);
            WaveDAC_0_StartEx(waveform, numSamples, NULL, 0);
            break;
        case WAVEDAC_LOW_1:
            WaveDAC_1_Clock_SetDividerRegister(LOW_DIVIDER_REGISTER, 1);
            WaveDAC_1_StartEx(waveform, numSamples, NULL, 0);
            break;
        case WAVEDAC_HIGH_1:
            WaveDAC_1_Clock_SetDividerRegister(HIGH_DIVIDER_REGISTER, 1);
            WaveDAC_1_StartEx(waveform, numSamples, NULL, 0);
            break;
    }    
}

void setSquare(int numSamples, uint8 *currentWaveform)
{
    int i;
    for (i = 0; i < numSamples; i++) {
        if (i < numSamples / 2) {
            currentWaveform[i] = 255;
        }
        else {
            currentWaveform[i] = 0;   
        }
    }
}

void setSine(int numSamples, uint8 *currentWaveform)
{
    int i;
    for (i = 0; i < numSamples; i++) {
        currentWaveform[i] = 128 + 127 * sin((2 * PI * i) / numSamples);   
    }
}

void setTriangle(int numSamples, uint8 *currentWaveform)
{
    int i;
    for (i = 0; i < numSamples; i++) {
        if (i < numSamples / 2) {
            currentWaveform[i] = 255.0 * (1.0 * i / (numSamples / 2.0));
        } else {
            currentWaveform[i] = 255.0 * (1.0 * (numSamples - i) / (numSamples / 2.0));
        }
    }
}

void setSawtooth(int numSamples, uint8 *currentWaveform)
{
    int i;
    for (i = 0; i < numSamples; i++) {
        currentWaveform[i] = 255.0 * (1.0 * i / numSamples);   
    }
}

void setDC(int numSamples, uint8 *currentWaveform)
{
    int i;
    for (i = 0; i < numSamples; i++) {
        currentWaveform[i] = 255;
    }    
}

void setWaveform(int numSamples, int mode, uint8 *currentWaveform) 
{
    switch (mode) {
        case SQUARE:
            setSquare(numSamples, currentWaveform);
            break;
        case SINE:
            setSine(numSamples, currentWaveform);
            break;
        case TRIANGLE:
            setTriangle(numSamples, currentWaveform);
            break;
        case SAWTOOTH:
            setSawtooth(numSamples, currentWaveform);
            break;
        case DC:
            setDC(numSamples, currentWaveform);
            break;
    }
}

uint8 *getCurrentWaveform(int fnGenerator)
{
    switch (fnGenerator) {
        case WAVEDAC_LOW_0:
        case WAVEDAC_HIGH_0:
            return waveform0;
        case WAVEDAC_LOW_1:
        case WAVEDAC_HIGH_1:
            return waveform1;
        default:
            return NULL;
    }
}

int changeFrequency(int freq, int mode, int waveDacId)
{
    int fnGenerator, numSamples;
    uint8 *currentWaveform;
    
    if (freq < FREQ_LOWER_LIMIT) {
        freq = FREQ_LOWER_LIMIT;
    } else if (freq > FREQ_UPPER_LIMIT) {
        freq = FREQ_UPPER_LIMIT;
    }
    
    if (freq < 2000) {
        if (waveDacId == 0) {
            fnGenerator = WAVEDAC_LOW_0;
        } else if (waveDacId == 1) {
            fnGenerator = WAVEDAC_LOW_1;
        }
        numSamples = WAVEDAC_CLOCK_LOW_FREQ / freq;
    } else {
        if (waveDacId == 0) {
            fnGenerator = WAVEDAC_HIGH_0;
        } else if (waveDacId == 1) {
            fnGenerator = WAVEDAC_HIGH_1;
        }
        numSamples = WAVEDAC_CLOCK_HIGH_FREQ / freq;
    }
    
    currentWaveform = getCurrentWaveform(fnGenerator);
    if (currentWaveform != NULL) {
        stopWaveDac(fnGenerator);
        setWaveform(numSamples, mode, currentWaveform);
        startWaveDac(numSamples, fnGenerator, currentWaveform);
        return freq;
    }
    
    return -1;
}

/* [] END OF FILE */
