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
  float CO2; 					  /*!< Carbon Dioxide in air (in )*/
  float TVOC; 					/*!< Total Volatile Organic Compounds in air (in )*/
	float RawEthanol; 
	float RawH2; 
} EnvironmentData;



/**
 * @brief Controller Class
 * @author Kamil Rog
 *
 * This class is responsible for handling all measurements and controll. 
 */
class Sampler : public CppTimer {

	void timerEvent() {
		Gather_Env_Data();
		Print_Env_Data();
		Send_Env_Data();
		std::thread::id this_id = std::this_thread::get_id();
    std::cout << "timerEvent() " << this_id << "\n";

	}

public:
	/**
	* Constructor that sets the offset for the thread to a given value.
	*
	* @param wPipe Write pipe to server thread
	*/
	Sampler(int wPipe) {
		writePipe = wPipe;
		Initialize();
	}


private:
	int Initialize();
	int Gather_Env_Data();
	int Print_Env_Data();
	int Send_Env_Data();
	int Create_Pipe_Message(const char *variableString, float value );

	I2CDriver i2cDriver;              		/*!< I2C driver used for peripherials */
	VEML7700 	lightSensor; 				        /*!< VEML7700 Light Sensor Object */
	SHT31D  	temperatureHumiditySensor;  /*!< SHT31D Temperature & Humidity Sensor Object */
	SGP30			gasSensor;  				        /*!< SGP30 Gas Sensor Object */
	Camera 		camera; 					          /*!< Camera Sensor Object */
	Actuator 	actuator; 					        /*!< Actuator Object */
	EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
	
	int writePipe;
};

#endif
