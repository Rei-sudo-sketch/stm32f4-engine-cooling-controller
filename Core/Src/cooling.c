#include "cooling.h"
#include <stdint.h>

#define ADC_MIN_VALID  50U
#define ADC_MAX_VALID  4045U

static CoolingState currentState = NORMAL;
static uint8_t currentFanSpeed = 0;
static float currentTemperature = 0.0f; 


static CoolingState getCoolingState(float temperature, CoolingState previousState)
{
    if (previousState == OVERHEAT && temperature >= 100.0f)
    {
      return OVERHEAT;
    }
    else if (temperature < 90.0f)
    {
        return NORMAL;
    }
    else if (temperature < 110.0f)
    {
      return WARNING;
    }
    else 
    {
      return OVERHEAT;
    }
    
}

static uint8_t getFanSpeed(CoolingState state)
{
  if (state == NORMAL)
  {
    return 0; 
  }
  else if (state == WARNING)
  {
    return 50;
  }
  else  
  {
    return 100; 
  }
}

const char* coolingState_T(CoolingState state)
{
  switch (state) 
  {

    case NORMAL: return "NORMAL";
    case WARNING: return "WARNING";
    case OVERHEAT: return "OVERHEAT";
    case FAULT:       return "FAULT";
    default:            return "UNKNOWN";
  }
}

float adcToTemperature(uint32_t adcValue)
{
  float temperature;
  if(adcValue > 4095)
  {
    adcValue = 4095; 
  }
  temperature = (adcValue / 4095.0f ) * 150.0f;
  return temperature; 

}


void coolingUpdate(uint32_t adcValue)
{

  if (adcValue < ADC_MIN_VALID || adcValue > ADC_MAX_VALID)
  {
      currentState = FAULT; 
      currentFanSpeed  = getFanSpeed(FAULT); 
  }
  
  else
  {
  currentTemperature = adcToTemperature(adcValue);
  currentState = getCoolingState(currentTemperature, currentState);
  currentFanSpeed = getFanSpeed(currentState);
  }

}
CoolingState coolingGetState(void)
{
    return currentState;
}

uint8_t coolingGetFanSpeed(void)
{
    return currentFanSpeed;
}

float coolingGetTemperature(void)
{
  return currentTemperature; 
}