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
#include <time.h>
#include <unistd.h>

//#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "Actuator.h"
#include "CCS811.h"
#include "Camera.h"

using namespace std;

 
/**
 * Environment Data Struct Definition
 * 
 * This struct conatins all enviroment data read from sensors as well as target values
 */
 typedef struct{
  // Alternativley use triple slash for the comments
  float LightIntensity; /*!< Light Intensity of the envieronment (in Lux) */	
  float Temp; 					/*!< Temperature of the envirnoment (in Degrees Celsius)*/
  float CO2; 					  /*!< Carbon Dioxide in air (in )*/
  float TVOC; 					/*!< Total Volatile Organic Compounds in air (in )*/
  uint8_t Humidity;     /*!< Humidity of the environment (in Percent %)*/
  
  float LightIntensityTarget; /*!< Threshold Light Intensity - Set by user */
  float TempTarget;           /*!< Target Temperature - Set by user */		 
  uint8_t HumidityTarget;		  /*!< Target Humidity - Set by user */	
  
} EnvironmentData;


/**
 * @brief Controller Class
 * @author Kamil Rog
 *
 * This class is responsible for handling all measurements and controll. 
 */
class Controller {

public:
	/**
	 * Constructor that sets the offset for the thread to a given value.
	 *
	 * @todo:@param filepath  filepath for settings file.
	 * 
	 */
	Controller() {
	
		/*Initialize Peripherials*/
		lightSensor.Initialize();
		
		
		/* Initialize EnvData Structure*/
		envData.LightIntensity = 0.0; 
		envData.Temp = 0.0; 
		envData.Humidity = 0; 
		envData.CO2 = 0; 
		envData.TVOC = 0; 
		
		envData.LightIntensityTarget = 30000; 		
		envData.TempTarget = 25.0; 		
		envData.HumidityTarget = 75; 	
	}
	
 /**
	* Run Function responsible for event hanlding.
	* 
	*/
	void Run();

private:

	//I2CDriver   i2cDriver;              /*!< I2C driver used for peripherials */
	VEML7700 	lightSensor; 				        /*!< VEML7700 Light Sensor Object */
	SHT31D  	temperatureHumiditySensor;  /*!< SHT31D Temperature & Humidity Sensor Object */
	CCS811		gasSensor;  				        /*!< CS811 Gas Sensor Object */
	Camera 		camera; 					          /*!< Camera Sensor Object */
	Actuator 	actuator; 					        /*!< Actuator Object */
	EnvironmentData envData; 				      /*!< Current and Target Enviroment Data Struct */
	
};

#endif
