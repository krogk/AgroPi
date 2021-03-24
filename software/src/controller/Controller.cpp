/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for actuator class.
*
* 
*/

#include "Controller.h"
#include <stdio.h>


void Controller::SamplerHasData(EnvironmentData newData)
{
	envData = newData;
	printf("\n");
	printf("Controller Thread: LUX: %f\n",envData.LightIntensity);
	printf("Controller Thread: Temperature: %f\n",envData.Temperature);
	printf("Controller Thread: Humidity: %f\n",envData.Humidity);
	printf("Controller Thread: TVOC: %d ppb\n", envData.TVOC);
	printf("Controller Thread: eCO2: %d ppm\n", envData.CO2);
	printf("Controller Thread: RawEthanol: %d ppb\n", envData.RawEthanol);
	printf("Controller Thread: RawH2: %d ppm\n", envData.RawH2);
	//std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "Controller Thread " << this_id << "\n";
	ActuatorHandler();
}


void Controller::SendDataToWebApp()
{

	//envData 

}


void Controller::ActuatorHandler()
{
	// Light
	if( envData.LightIntensity < targets.LightIntensityLowerThreshold )
	{
		printf("Light Intensity:%f Too Low\n", envData.LightIntensity);
		// turn lights on
	}
	else if( envData.LightIntensity > targets.LightIntensityUpperThreshold )
	{
		printf("Light Intensity :%f - Sufficient To Turn Lights off\n", envData.LightIntensity);
		// turn lights off if On
	}
}