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
	printf("envData.TempTarget: %f\n",envData.TempTarget);
	printf("envData.HumidityTarget : %f\n",envData.HumidityTarget);
	
	float lux;
	
	printf("VEML7700 TEST");		
	while(1) {
		lightSensor.Get_ALS_Lux(lux);
		printf("Get_ALS_LUX: %f\n",lux);
		uint16_t x = 0; 
		for(int i = 0; i<2500000; i++) {
			x++;
		} 
		
	}
}

