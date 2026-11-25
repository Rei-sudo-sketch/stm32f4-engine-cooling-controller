#ifndef COOLING_H
#define COOLING_H

#include <stdint.h>


typedef enum{
  NORMAL,
  WARNING,                                                                 
  OVERHEAT,
  FAULT
} CoolingState;

const char* coolingState_T(CoolingState state);

float adcToTemperature(uint32_t adcValue);

void coolingUpdate(uint32_t adcvalue);

CoolingState coolingGetState(void);

uint8_t coolingGetFanSpeed(void);

float coolingGetTemperature(void);

#endif