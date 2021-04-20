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


/**
 * @brief Sampler Class
 * @author Kamil Rog
 *
 * This class is responsible for taking measurements for all devices on I2C Bus. 
 * This is achiebed by inheriting functionality of CppTimer.
 * timerEvent() is executed when timer fires.
 * This sampler creates new thread 
 */
class Sampler : public CppTimer
{
	/**
	* Executes when timer fires. 
	* Firstly it takes measurements and runs the 
	* callback function defined in the controller object
	*/
	void timerEvent()
	{
		Gather_Env_Data();
		//std::thread::id this_id = std::this_thread::get_id();
    //std::cout << "timerEvent() " << this_id << "\n";
		if (nullptr != samplerCallback) 
		{
			samplerCallback->SamplerHasData(envData);
  	}

	}

public:
	Sampler(Controller* cb)
	{
		setCallback(cb);
		Initialize();
	}
  /// Destructor
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

	/// Test Functions
	int Gather_Env_Data();
	EnvironmentData GetEnvData();
	void CallbackTest();

private:
	// Initializes devices for communication
	int Initialize();
	// Debug function
	int Print_Env_Data();
	// Closes files descriptors and 
	int CloseDevices();

	/// I2C driver used for 
	I2CDriver i2cDriver;   
	/// Peripherials using I2C driver - instantiate new sensors here     		
	VEML7700 	lightSensor; 				        
	SHT31D  	temperatureHumiditySensor; 
	SGP30			gasSensor;  				        
	/// Current and Target Enviroment Data Struct
	EnvironmentData envData; 				  
	/// Pointer to conroller object.    
	Controller* samplerCallback = nullptr;
};

#endif


