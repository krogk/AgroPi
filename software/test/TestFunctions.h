/**
* @file TestFunctions.h
* @author Kamil Rog
* @version 0.1
* 
* This file contains the functions that are used in testing cases
*
*/
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Define tolerable ranges for sensors reads
// VEML7700
#define LUX_MIN 0
#define LUX_MAX 120000
#define LUX_MIN_REASONABLE 20
#define LUX_MAX_REASONABLE 10000

// SHT31D
#define TEMPERATURE_MIN -40
#define TEMPERATURE_MAX 125
#define TEMPERATURE_MIN_REASONABLE 15
#define TEMPERATURE_MAX_REASONABLE 30
#define HUMDIITY_MIN 0
#define HUMIDITY_MAX 100
#define HUMDIITY_MIN_REASONABLE 45
#define HUMIDITY_MAX_REASONABLE 65

// SGP30
#define TVOC_MIN 0
#define TVOC_MAX 60000
#define TVOC_MIN_REASONABLE 0
#define TVOC_MAX_REASONABLE 1000

#define ECO2_MIN 400
#define ECO2_MAX 60000
#define ECO2_MIN_REASONABLE 400
#define ECO2_MAX_REASONABLE 2000

#define ETH_MIN 0
#define ETH_MAX 60000
#define ETH_MIN_REASONABLE 0
#define ETH_MAX_REASONABLE 1000

#define H2_MIN 400
#define H2_MAX 60000
#define H2_MIN_REASONABLE 400
#define H2_MAX_REASONABLE 1000

// RELAY BOARD
#define RELAY_ON  0
#define RELAY_OFF 1


/**
 * Return codes for CheckEnvironmentalVariableValue()
 */
	enum ENV_CHECK_STATUS {
	OK                                  = 0,
  MIN_VALUE_CHECK_FAILED 	            = -1,
  MAX_VALUE_CHECK_FAILED 	            = -2,
  LOWER_THRESHOLD_VALUE_CHECK_FAILED  = -3,
  UPPER_THRESHOLD_VALUE_CHECK_FAILED  = -4,
	};


/**
* Check environmental variable is within tolerable range.
* 
* return Zero when measurement is ok, else negative number ENV_CHECK_STATUS,
*
*/
int CheckEnvironmentalVariableValue(float measurement, float minValue, float maxValue, float lowerReasonableThreshold, float UpperReasonableThreshold )
{
  if(measurement < minValue )
  {
    return MIN_VALUE_CHECK_FAILED;
  }

  if(measurement > maxValue )
  {
    return MAX_VALUE_CHECK_FAILED;
  }

  if(measurement < lowerReasonableThreshold )
  {
    return LOWER_THRESHOLD_VALUE_CHECK_FAILED;
  }

  if(measurement > UpperReasonableThreshold)
  {
    return UPPER_THRESHOLD_VALUE_CHECK_FAILED;
  }

  return OK;
}

