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

	/* Initialize Targets for EnvData Structure*/
	// This needs to be downloaded from website
	targets.LightIntensityUpperThreshold = 1000.0; 
  targets.LightIntensityLowerThreshold = 2.0; 
  targets.TemperatureUpperThreshold = 30.0; 					
  targets.TemperatureLowerThreshold = 18.0; 					
  targets.HumidityUpperThreshold = 70.0; 				
  targets.HumidityLowerThreshold = 30.0; 				
  targets.CO2UpperThreshold = 1000; 				
  targets.TVOCUpperThreshold = 300; 				
  targets.RawEthanolUpperThreshold = 300; 				
  targets.RawH2UpperThreshold = 300; 		

	actuationFlags.ForceHeating = false;
	actuationFlags.ForceLighting = false;
	actuationFlags.ForceAirflow = false;
	actuationFlags.ForceWaterPump = false;
	}

	void SamplerHasData(EnvironmentData newData);

	int Update_Targets(uint8_t opcode, float vlaue);
	void StartListenerServer();
	void MessageHandler(uint8_t opcode, float value );

	EnvironmentData envData; 				      			/*!< Current Enviroment Conditions Read Froms the sensors */
	TargetEnvironmentData targets; 				      /*!< Target Enviroment Conditions */
	ActuationForceFlags actuationFlags;					/*!< Actuatuion force flags ignoring hu Enviroment Conditions */

private:
	void SendDataToWebApp(std::string variable_type, float value);
	void ActuatorHandler();


private:

		enum TARGET_OP_CODES {
		LIGHT_INTENSITY_TARGET_CHANGE 	= 1,
		TEMPERATURE_TARGET_CHANGE 			= 2,
		HUMIDITY_TARGET_CHANGE 					= 3,
		TVOC_TARGET_CHANGE 							= 4,
		ECO2_TARGET_CHANGE 						  = 5,
		ETH_TARGET_CHANGE								= 6,
		H2_TARGET_CHANGE								= 7
		};

	RelayBoard relay;
};

#endif
