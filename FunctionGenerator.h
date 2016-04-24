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

#include "Generated_Source/PSoC5/cytypes.h"
#include "Generated_Source/PSoC5/cyfitter.h"

// Waveform types
#define SQUARE   0
#define SINE     1
#define TRIANGLE 2
#define SAWTOOTH 3
#define DC       4

// Waveform data
#define MAX_NUM_SAMPLES 4000

// WaveDAC to select
#define WAVEDAC_LOW_0 0
#define WAVEDAC_HIGH_0 1
#define WAVEDAC_LOW_1 2
#define WAVEDAC_HIGH_1 3

// WaveDAC clocks
#define LOW_DIVIDER_REGISTER 119
#define HIGH_DIVIDER_REGISTER 5
#define WAVEDAC_CLOCK_LOW_FREQ 200000
#define WAVEDAC_CLOCK_HIGH_FREQ 4000000

#define FREQ_LOWER_LIMIT 50
#define FREQ_UPPER_LIMIT 100000

#define PI 3.14159265

// Function prototypes
void stopWaveDac(int fnGenerator);
void startWaveDac(int numSamples, int fnGenerator, uint8 *waveform);
void setSquare(int numSamples, uint8 *currentWaveform);
void setSine(int numSamples, uint8 *currentWaveform);
void setTriangle(int numSamples, uint8 *currentWaveform);
void setSawtooth(int numSamples, uint8 *currentWaveform);
void setDC(int numSamples, uint8 *currentWaveform);
void setWaveform(int numSamples, int mode, uint8 *currentWaveform);
uint8 *getCurrentWaveform(int fnGenerator);
int changeFrequency(int freq, int mode, int waveDacId);

/* [] END OF FILE */
