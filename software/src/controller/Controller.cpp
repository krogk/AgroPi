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


void Controller::Run() {
	printf("envData.LightIntensityTarget: %f\n",envData.LightIntensityTarget);
	printf("envData.TempTarget: %f\n",envData.TemperatureTarget);
	printf("envData.HumidityTarget : %f\n",envData.HumidityTarget);

	
	printf("VEML7700 TEST\n");		
	lightSensor.Get_ALS_Lux(envData.Temperature);
	printf("Get_ALS_LUX: %f\n",envData.Temperature);
	
	float white; 
	lightSensor.Get_White_Lux(white);
	printf("Get_ALS_White: %f\n",white);

}
