/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the function for controller class.
*
* 
*/
#include "Controller.h"
#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


/**
* Initialize all enviromental data struct variables and sensors.
*
* filepath filepath for settings file.
* 
*/
int Controller::Initialize(){

	/*Initialize Peripherials*/
	lightSensor.Initialize(i2cDriver);
	temperatureHumiditySensor.Initialize(i2cDriver);
	gasSensor.Initialize(i2cDriver);
	
	/* Initialize EnvData Structure*/
	envData.LightIntensity = 0.0; 
	envData.Temperature = 0.0; 
	envData.Humidity = 0.0; 
	envData.CO2 = 0.0; 
	envData.TVOC = 0.0; 
	envData.RawEthanol = 0.0; 
	envData.RawH2 = 0.0; 

	/* Set Initial Target Values */
	envData.LightIntensityTarget = 1000; 		
	envData.TemperatureTarget = 25.0; 		
	envData.HumidityTarget = 45;

	return 0;
}


/**
* Reads data from all sensors by turn.
*
* @return Zero On Sucess 
*/
int Controller::Gather_Env_Data() {
	lightSensor.Get_ALS_Lux(envData.LightIntensity);
	temperatureHumiditySensor.Get_Temperature_Humidity(envData.Temperature, envData.Humidity);
	gasSensor.IAQ_Measure( envData.TVOC, envData.CO2);
	gasSensor.IAQ_Measure_Raw( envData.RawEthanol, envData.RawH2);
	return 0;
}

/**
* Prints data read by sensors by turn.
*
* @return Zero On Sucess 
*/
int Controller::Print_Env_Data(){
	printf("\n");
	printf("Get_ALS_LUX: %f\n",envData.LightIntensity);
	printf("Temperature: %f\n",envData.Temperature);
	printf("Humidity: %f\n",envData.Humidity);
	printf("TVOC: %d ppb\n", envData.TVOC);
	printf("eCO2: %d ppm\n", envData.CO2);
	printf("RawEthanol: %d ppb\n", envData.RawEthanol);
	printf("RawH2: %d ppm\n", envData.RawH2);
	return 0;
}
