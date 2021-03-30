/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the class for the Actuator
* 
*/
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "typeDefinitions.h"
#include "RelayBoard.h"


/**
* @brief Sht class
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
  targets.LightIntensityLowerThreshold = 100.0; 
  targets.TemperatureUpperThreshold = 30.0; 					
  targets.TemperatureLowerThreshold = 18.0; 					
  targets.HumidityUpperThreshold = 70.0; 				
  targets.HumidityLowerThreshold = 30.0; 				
  targets.CO2UpperThreshold = 1000; 				
  targets.TVOCUpperThreshold = 300; 				
  targets.RawEthanolUpperThreshold = 300; 				
  targets.RawH2UpperThreshold = 300; 				
	}


	
	void SamplerHasData(EnvironmentData newData);


private:
	void SendDataToWebApp();
	void ActuatorHandler();

private:
	//WaterPump pump; /*!< Water Pump Object */
	//Heater heater; /*!< Heater Actuator Object */
		EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
		TargetEnvironmentData targets; 				      /*!< Current and Target Enviroment Data Struct */
		RelayBoard relay;

};

#endif
