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
#include "SGP30.h"
//#include "Camera.h"
#include "Controller.h"


/**
 * Callback for new samples which needs to be implemented by the main program.
 * The function hasSample needs to be overloaded in the main program.
 **/
class ControllerCallback {
public:
	/**
	 * Called after a sample has arrived.
	 **/
	void SamplerHasData(EnvironmentData data);
};


/**
 * @brief Controller Class
 * @author Kamil Rog
 *
 * This class is responsible for handling all measurements and controll. 
 */
class Sampler : public CppTimer {

	void timerEvent() {
		Gather_Env_Data();
		std::thread::id this_id = std::this_thread::get_id();
    std::cout << "timerEvent() " << this_id << "\n";
		if (nullptr != samplerCallback) 
		{
			samplerCallback->SamplerHasData(envData);
  	}

	}

public:
	Sampler(Controller* cb) {
		setCallback(cb);
		Initialize();
	}

	~Sampler() {
		stop();
	}

	/**
	 * Sets the callback which is called whenever there is a sample
	 **/
	void setCallback(Controller* cb) {
		samplerCallback = cb;
	}

	/**
	* Stops the data acquistion
	**/
	void stopSampler() {
		stop();
	}


private:
	int Initialize();
	int Gather_Env_Data();
	int Print_Env_Data();

	I2CDriver i2cDriver;              		/*!< I2C driver used for peripherials */
	VEML7700 	lightSensor; 				        /*!< VEML7700 Light Sensor Object */
	SHT31D  	temperatureHumiditySensor;  /*!< SHT31D Temperature & Humidity Sensor Object */
	SGP30			gasSensor;  				        /*!< SGP30 Gas Sensor Object */
	//Camera 		camera; 					          /*!< Camera Sensor Object */
	EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
	Controller* samplerCallback = nullptr;
};

#endif


