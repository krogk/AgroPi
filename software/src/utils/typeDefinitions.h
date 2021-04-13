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
  uint16_t TVOCUpperThreshold; 					    /*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawEthanolUpperThreshold; 				/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  uint16_t RawH2UpperThreshold; 					  /*!< Temperature of the envirnoment (in Degrees Celsius)*/
} TargetEnvironmentData;


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins actuaytor 
 */
 typedef struct{
  bool ForceHeating;        /*!< Force Heating on actuation handler */
	bool ForceLighting;					
	bool ForceAirflow;
	bool ForceWaterPump;						
} ActuationForceFlags;
