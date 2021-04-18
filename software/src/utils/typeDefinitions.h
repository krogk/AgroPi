#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins all enviroment data read from sensors as well as target values
 */
 typedef struct{
  /// Alternativley use triple slash for the comments
	// Env Data
  float LightIntensity; /*!< Light Intensity of the envieronment (in Lux) */	
  float Temperature; 					/*!< Temperature of the envirnoment (in Degrees Celsius)*/
	float Humidity;     /*!< Humidity of the environment (in Percent %)*/
  uint16_t CO2; 					  /*!< Carbon Dioxide in air (in )*/
  uint16_t TVOC; 					/*!< Total Volatile Organic Compounds in air (in )*/
	uint16_t RawEthanol; 
	uint16_t RawH2; 
} EnvironmentData;


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins all enviroment data read from sensors as well as target values
 */
 typedef struct{
  /// Alternativley use triple slash for the comments
	// Env Data
  float LightIntensityUpperThreshold;       /*!< Light Intensity of the envieronment (in Lux) */
  float LightIntensityLowerThreshold;       /*!< Light Intensity of the envieronment (in Lux) */	
  float TemperatureUpperThreshold; 					/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  float TemperatureLowerThreshold; 					/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  float HumidityUpperThreshold; 					  /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  float HumidityLowerThreshold; 					  /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t CO2UpperThreshold; 					    /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t CO2LowerThreshold; 					    /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t TVOCUpperThreshold; 					    /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t TVOCLowerThreshold; 					    /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawEthanolUpperThreshold; 				/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawEthanolLowerThreshold; 				/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawH2UpperThreshold; 					  /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawH2LowerThreshold; 					  /*!< Temperature of the envirnoment (in Degrees Celsius)*/

} TargetEnvironmentData;


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins actuator Force flags.
 * If a flag is set the actuator enables the device
 * regardless of everything else. 
 */
 typedef struct{
  bool Heating;        /*!< Force Heating on actuation handler */
	bool Lighting;					
	bool Airflow;
	bool Watering;						
} ActuationForceFlags;


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins actuator Heuristics flags.
 * If a flag is set the actuator enables the control through Heuristics
 *
 */
 typedef struct{
  bool Heating;
	bool Lighting;
	bool Airflow;
	bool Watering;
} ActuationHeuristicsFlags;