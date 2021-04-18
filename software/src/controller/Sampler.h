/**
* @file Sampler.h
* @author Kamil Rog
* @version 0.1
*
* This header file contains the thread for Controller of the AgroPi sensors and actuators 
* 
*/
#ifndef SAMPLER_H
#define SAMPLER_H


#include "Controller.h"
#include <stdio.h>
#include "CppTimer.h"
#include "I2CDriver.h"
#include "I2CSensor.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "SGP30.h"
#include "Camera.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"


/**
 * @brief Sampler Class
 * @author Kamil Rog
 *
 * This class is responsible for taking measurements for all devices on I2C Bus. 
 * Inherits from CppTimer 
 */
class Sampler : public CppTimer
{

	void timerEvent()
	{
		Gather_Env_Data();
		//std::thread::id this_id = std::this_thread::get_id();
    //std::cout << "timerEvent() " << this_id << "\n";
		if (nullptr != samplerCallback) 
		{
			SendEnvData();
			samplerCallback->SamplerHasData(envData);
  	}

	}

public:
	Sampler(Controller* cb)
	{
		setCallback(cb);
		Initialize();
	}

	~Sampler()
	{
		stop();
		CloseDevices();
	}

	/**
	 * Sets the callback which is called whenever there is new data
	 **/
	void setCallback(Controller* cb)
	{
		samplerCallback = cb;
	}

	/**
	* Stops the data acquistion
	**/
	void stopSampler()
	{
		stop();
	}


private:
	int Initialize();
	int Gather_Env_Data();
	int Print_Env_Data();
	int CloseDevices();
	void SendEnvData();
	void SendDataToWebApp(std::string variable_type, float value);

	I2CDriver i2cDriver;              		/*!< I2C driver used for peripherials */
	VEML7700 	lightSensor; 				        /*!< VEML7700 Light Sensor Object */
	SHT31D  	temperatureHumiditySensor;  /*!< SHT31D Temperature & Humidity Sensor Object */
	SGP30			gasSensor;  				        /*!< SGP30 Gas Sensor Object */
	Camera 		camera; 					          /*!< Camera Sensor Object */
	EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
	Controller* samplerCallback = nullptr;

	int sampleCounter; 
};

#endif


