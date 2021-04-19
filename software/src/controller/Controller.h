/**
* @file Controller.h
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "typeDefinitions.h"
#include "RelayBoard.h"
#include "GPIODriver.h"
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
* @brief Controller class
* @author Kamil Rog
*
* This is class is responsilbe for the SHT31D temperature and humidity sensor.
* 
* @section PROTOCOL
* 
* WATER PUMP - ANALOG - GPIO x
* HEATER     - ANALOG - GPIO x
* 
*/
class Controller {

public:
	Controller()
	{
	/* Initialize EnvData Structure*/
	envData.LightIntensity = 0.0; 
	envData.Temperature = 0.0; 
	envData.Humidity = 0.0; 
	envData.CO2 = 0; 
	envData.TVOC = 0; 
	envData.RawEthanol = 0; 
	envData.RawH2 = 0; 

	//
	relay.Initialize(gpiodriver);

	// Initialize Targets for EnvData Structure
	targets.LightIntensityUpperThreshold = 1000.0; 
  targets.LightIntensityLowerThreshold = 2.0; 
  targets.TemperatureUpperThreshold = 30.0; 					
  targets.TemperatureLowerThreshold = 18.0; 					
  targets.HumidityUpperThreshold = 60.0; 				
  targets.HumidityLowerThreshold = 30.0; 				
  targets.CO2UpperThreshold = 700; 
	targets.CO2LowerThreshold = 0;				
  targets.TVOCUpperThreshold = 700; 
	targets.TVOCLowerThreshold = 0;
  targets.RawEthanolUpperThreshold = 700; 
	targets.RawEthanolLowerThreshold = 0; 				
  targets.RawH2UpperThreshold = 700; 
	targets.RawH2LowerThreshold = 0;		
	// Force Flags off by default
	actuationForceFlags.Heating = false;
	actuationForceFlags.Lighting = false;
	actuationForceFlags.Airflow = false;
	actuationForceFlags.Watering = false;
	// Heuristics Flags on by default
	actuationHeuristicsFlags.Heating = false;
	actuationHeuristicsFlags.Lighting = false;
	actuationHeuristicsFlags.Airflow = false;
	actuationHeuristicsFlags.Watering = false;
	}

	void SamplerHasData(EnvironmentData newData);

	int Update_Targets(uint8_t opcode, float vlaue);
	void StartListenerServer();
	void MessageHandler(uint8_t opcode, float value );

	EnvironmentData envData; 				      			/*!< Current Enviroment Conditions Read Froms the sensors */
	TargetEnvironmentData targets; 				      /*!< Target Enviroment Conditions */
	ActuationForceFlags actuationForceFlags;		/*!< Actuatuion force flags ignoring hu Enviroment Conditions */
	ActuationHeuristicsFlags  actuationHeuristicsFlags; /*!< Actuatuion Heuristics flags if this is disabled the actuator doesn't run against hueristics */

private:
	void ActuatorHandler();
	void SendEnvData();
  void SendDataToWebApp(std::string variable_type, float value);

  void LightActuator();
	void HeatActuator();
	void AirflowActuator();
	void WateringActuator();

private:

	enum CONTROL_OP_CODES {
	LIGHT_INTENSITY_UPPER_TARGET_CHANGE 	= 1,
	LIGHT_INTENSITY_LOWER_TARGET_CHANGE 	= 2,
	TEMPERATURE_UPPER_TARGET_CHANGE 			= 3,
	TEMPERATURE_LOWER_TARGET_CHANGE 			= 4,
	TVOC_UPPER_TARGET_CHANGE 							= 5,
	TVOC_LOWER_TARGET_CHANGE 							= 6,
	ECO2_UPPER_TARGET_CHANGE 						  = 7,
	ECO2_LOWER_TARGET_CHANGE 						  = 8,
	ETH_UPPER_TARGET_CHANGE								= 9,
	ETH_LOWER_TARGET_CHANGE								= 10,
	H2_UPPER_TARGET_CHANGE								= 11,
	H2_LOWER_TARGET_CHANGE								= 12,
	HUMIDITY_UPPER_TARGET_CHANGE          = 13,
	HUMIDITY_LOWER_TARGET_CHANGE 					= 14,

	FORCE_HEATING													= 128,
	FORCE_AIRFLOW													= 129,
	FORCE_LIGHTS													= 130,
	FORCE_WATER_PUMP											= 131,
	ENABLE_HEATING_HEURISTIC							= 132,
	ENABLE_AIRFLOW_HEURISTIC							= 133,
	ENABLE_LIGHTS_HEURISTIC								= 134,
	ENABLE_WATER_PUMP_HEURISTIC						= 135
	};

	GPIODriver gpiodriver;
	RelayBoard relay;
};

#endif
