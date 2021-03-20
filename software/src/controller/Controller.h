/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the thread for Controller of the AgroPi sensors and actuators 
*
* 
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H



#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "CppTimer.h"
#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "Actuator.h"
#include "SGP30.h"
#include "Camera.h"





 
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
  
	/// Targets
  float LightIntensityTarget; /*!< Threshold Light Intensity - Set by user */
  float TemperatureTarget;    /*!< Target Temperature - Set by user */		 
  float HumidityTarget;		  /*!< Target Humidity - Set by user */	
  
} EnvironmentData;


/**
 * @brief Controller Class
 * @author Kamil Rog
 *
 * This class is responsible for handling all measurements and controll. 
 */
class Controller : public CppTimer {

	void timerEvent() {
		Gather_Env_Data();
		Print_Env_Data();
	}

public:
	int Initialize();

private:
	int Gather_Env_Data();
	int Print_Env_Data();

	I2CDriver i2cDriver;              		/*!< I2C driver used for peripherials */
	VEML7700 	lightSensor; 				        /*!< VEML7700 Light Sensor Object */
	SHT31D  	temperatureHumiditySensor;  /*!< SHT31D Temperature & Humidity Sensor Object */
	SGP30			gasSensor;  				        /*!< SGP30 Gas Sensor Object */
	Camera 		camera; 					          /*!< Camera Sensor Object */
	Actuator 	actuator; 					        /*!< Actuator Object */
	EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
	
};

#endif
