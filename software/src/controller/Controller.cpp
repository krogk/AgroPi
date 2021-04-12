/**
* @file Controller.cpp
* @author Kamil Rog
* @version 0.1
*
*
* 
* This file contains the functions for actuator class.
*
* 
*/
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "Controller.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "httplib.h"

void Controller::SamplerHasData(EnvironmentData newData)
{
	envData = newData;
	//printf("\n");
	//printf("Controller Thread: LUX: %f\n",envData.LightIntensity);
	//printf("Controller Thread: Temperature: %f\n",envData.Temperature);
	//printf("Controller Thread: Humidity: %f\n",envData.Humidity);
	//printf("Controller Thread: TVOC: %d ppb\n", envData.TVOC);
	//printf("Controller Thread: eCO2: %d ppm\n", envData.CO2);
	//printf("Controller Thread: RawEthanol: %d ppb\n", envData.RawEthanol);
	//printf("Controller Thread: RawH2: %d ppm\n", envData.RawH2);
	//std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "Controller Thread " << this_id << "\n";
	SendDataToWebApp("TEMPERATURE", envData.Temperature);
	SendDataToWebApp("HUMIDITY", envData.Humidity);
	SendDataToWebApp("LIGHT_INTENSITY", envData.LightIntensity);
	ActuatorHandler();
}


void Controller::SendDataToWebApp(std::string variable_type, float value)
{
	//envData  "/measurement" http://192.168.178.41:5050
	httplib::Client cli("http://127.0.0.1:5050");

	std::string url = "/measurements?type=" + variable_type + "&value=" + std::to_string(value);
	const char * urlStr = url.c_str();
	if(auto res = cli.Get(urlStr)){
		printf("Response status from web app: %f\n", res->status);
		printf("Response body from web app: %f\n", res->body);
	}

}

void Controller::ActuatorHandler()
{
	// Light
	if( envData.LightIntensity < targets.LightIntensityLowerThreshold )
	{
		printf("Light Intensity:%f Too Low\n", envData.LightIntensity);
		// turn lights on
		relay.SetGPIOState(27, 0);
	}

	else if( envData.LightIntensity > targets.LightIntensityUpperThreshold )
	{
		printf("Light Intensity :%f - Sufficient To Turn Lights off\n", envData.LightIntensity);
		// turn lights off if On
		
		relay.SetGPIOState(27, 1);

	}
}

int Controller::Update_Targets(uint8_t opcode, float value )
{
	printf("Operation %d Value: %f\n",opcode, value);
	switch(opcode)
  {
  case LIGHT_INTENSITY_TARGET_CHANGE:
	  targets.LightIntensityLowerThreshold = value;
		//targets.LightIntensityUpperThreshold = 1000.0; 
  break;

  case TEMPERATURE_TARGET_CHANGE:
	  //targets.TemperatureUpperThreshold = 30.0; 					
  	targets.TemperatureLowerThreshold = value; 	
  break;

  case HUMIDITY_TARGET_CHANGE:
	  //targets.HumidityUpperThreshold = 70.0; 				
  	targets.HumidityLowerThreshold = value; 	
  break;

  case TVOC_TARGET_CHANGE:	
  	targets.TVOCUpperThreshold = value; 	
  break;

 case ECO2_TARGET_CHANGE:
		targets.CO2UpperThreshold = value; 	
  break;

 case ETH_TARGET_CHANGE:
		targets.RawEthanolUpperThreshold = value; 	
  break;

	case H2_TARGET_CHANGE:
		targets.RawH2UpperThreshold = value; 	
  break;

  default:
    break;
  }

}