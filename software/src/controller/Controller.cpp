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
	// Add mutex here
	envData = newData;
	/*
	printf("\n");
	printf("Controller Thread: LUX: %f\n",envData.LightIntensity);
	printf("SamplerHasData: Temperature: %f\n",envData.Temperature);
	printf("Controller Thread: Humidity: %f\n",envData.Humidity);
	printf("Controller Thread: TVOC: %d ppb\n", envData.TVOC);
	printf("Controller Thread: eCO2: %d ppm\n", envData.CO2);
	printf("Controller Thread: RawEthanol: %d ppb\n", envData.RawEthanol);
	printf("Controller Thread: RawH2: %d ppm\n", envData.RawH2);
	*/
	//std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "Controller Thread " << this_id << "\n";
	ActuatorHandler();
	SendEnvData();
}


void Controller::SendEnvData()
{
	SendDataToWebApp("LIGHT_INTENSITY", envData.LightIntensity);
	SendDataToWebApp("TEMPERATURE", envData.Temperature);
	SendDataToWebApp("HUMIDITY", envData.Humidity);
	SendDataToWebApp("TVOC", envData.TVOC);
	SendDataToWebApp("ECO2", envData.CO2);
	SendDataToWebApp("ETHANOL", envData.RawEthanol);
	SendDataToWebApp("H2", envData.RawH2);
}


void Controller::SendDataToWebApp(std::string variable_type, float value)
{
	//envData  "/measurement" http://192.168.178.41:5050
	httplib::Client cli("http://127.0.0.1:5050");

	std::string url = "/measurements?type=" + variable_type + "&value=" + std::to_string(value);
	const char * urlStr = url.c_str();
	if(auto res = cli.Get(urlStr)){
		//printf("Response status from web app: %f\n", res->status);
		//printf("Response body from web app: %f\n", res->body);
	}

}

void Controller::MessageHandler(uint8_t opcode, float value)
{
	printf("Operation %d Value: %f\n", opcode, value);
	switch(opcode)
  {
		case LIGHT_INTENSITY_UPPER_TARGET_CHANGE:
			targets.LightIntensityUpperThreshold = value; 
			printf("LIGHT_INTENSITY_TARGET_CHANGE\n");
  	break;

  	case LIGHT_INTENSITY_LOWER_TARGET_CHANGE:
	  	targets.LightIntensityLowerThreshold = value;
			printf("LIGHT_INTENSITY_TARGET_CHANGE\n");
  	break;

  	case TEMPERATURE_UPPER_TARGET_CHANGE:
	  	targets.TemperatureUpperThreshold = value; 					
			printf("TEMPERATURE_TARGET_CHANGE\n");
  	break;

  	case TEMPERATURE_LOWER_TARGET_CHANGE:
  		targets.TemperatureLowerThreshold = value; 	
			printf("TEMPERATURE_TARGET_CHANGE\n");
  	break;

  	case HUMIDITY_UPPER_TARGET_CHANGE:
	  	targets.HumidityUpperThreshold = value; 				
			printf("HUMIDITY_TARGET_CHANGE\n");	
  	break;

		case HUMIDITY_LOWER_TARGET_CHANGE:			
  		targets.HumidityLowerThreshold = value; 
			printf("HUMIDITY_TARGET_CHANGE\n");	
  	break;

  	case TVOC_UPPER_TARGET_CHANGE:	
  		targets.TVOCUpperThreshold = value;
			printf("TVOC_TARGET_CHANGE\n"); 	
  	break;

	  case TVOC_LOWER_TARGET_CHANGE:	
  		targets.TVOCLowerThreshold = value;
			printf("TVOC_TARGET_CHANGE\n"); 	
  	break;

		case ECO2_UPPER_TARGET_CHANGE:
			targets.CO2UpperThreshold = value; 	
			printf("ECO2_TARGET_CHANGE\n");
		break;

		case ECO2_LOWER_TARGET_CHANGE:
			targets.CO2LowerThreshold = value; 	
			printf("ECO2_TARGET_CHANGE\n");
		break;

		case ETH_UPPER_TARGET_CHANGE:
			targets.RawEthanolUpperThreshold = value; 
			printf("ETHANOL_TARGET_CHANGE\n");	
		break;

		case ETH_LOWER_TARGET_CHANGE:
			targets.RawEthanolUpperThreshold = value; 
			printf("ETHANOL_TARGET_CHANGE\n");	
		break;

		case H2_UPPER_TARGET_CHANGE:
			targets.RawH2UpperThreshold = value; 
			printf("H2_TARGET_CHANGE\n");		
		break;

		case H2_LOWER_TARGET_CHANGE:
			targets.RawH2UpperThreshold = value; 
			printf("H2_TARGET_CHANGE\n");		
		break;

		case FORCE_HEATING:
			(value > 0) ? actuationForceFlags.Heating  = true : actuationForceFlags.Heating = false;
			printf("FORCE_HEATING\n");		
		break;
		
		case FORCE_AIRFLOW:
			(value > 0) ? actuationForceFlags.Airflow  = true : actuationForceFlags.Airflow = false;
			printf("FORCE_AIRFLOW\n");
		break;
		
		case FORCE_LIGHTS:
			(value > 0) ? actuationForceFlags.Lighting  = true : actuationForceFlags.Lighting = false;
			printf("FORCE_LIGHTS\n");		
		break;
	
		case FORCE_WATER_PUMP:
			(value > 0) ? actuationForceFlags.Watering  = true : actuationForceFlags.Watering = false;
			printf("FORCE_WATER_PUMP\n");		
		break;

  default:
		printf("Unknown Opcode!\n");
    break;
  }
}

void Controller::LightActuator()
{
	// If Force Lighting is enabled
	if(actuationForceFlags.Lighting)
	{
		relay.Lighting(0);
	}
	// If Force Lighting is enabled
	else if(actuationHeuristicsFlags.Lighting)
	{
		// Light Lower yhan The Thershold
		if( envData.LightIntensity < targets.LightIntensityLowerThreshold )
		{
			printf("Light Intensity: %f Lower Than Threshold: %f - Turning Lights On \n", envData.LightIntensity, targets.LightIntensityLowerThreshold);
			// turn lights on
			relay.Lighting(0);
		}
		// Light Higher than The Thershold
		else if( envData.LightIntensity >= targets.LightIntensityUpperThreshold )
		{
			printf("Light Intensity: %f Higher Than Threshold: %f - Turning Lights Off \n", envData.LightIntensity, targets.LightIntensityUpperThreshold);
			// turn lights off if On
			// if statement here
			relay.Lighting(1);
		}
	}
}

void Controller::HeatActuator()
{
	// If Force Lighting is enabled
	if(actuationForceFlags.Heating)
	{
		relay.Heating(0);
	}
	// If Force Lighting is enabled
	else if(actuationHeuristicsFlags.Heating)
	{
	// Heating
	if( envData.Temperature < targets.TemperatureLowerThreshold )
		{
			printf("Temperature: %f Lower Than Threshold: %f - Turning Heater On \n", envData.Temperature, targets.TemperatureLowerThreshold);
			// turn heater on
			relay.Heating(0);
		}

		else if( envData.Temperature > targets.TemperatureUpperThreshold )
		{
			printf("Temperature: %f Higher Than Threshold: %f - Turning Heater Off \n", envData.Temperature, targets.TemperatureUpperThreshold);
			// turn heater off if On
			relay.Heating(1);
		}
	}
}


void Controller::AirflowActuator()
{
	// If Force Lighting is enabled
	if(actuationForceFlags.Airflow)
	{
		relay.Airflow(0);
	}
	// If Force Lighting is enabled
	else if(actuationHeuristicsFlags.Airflow)
	{
		// Airflow
	if( envData.CO2 >= targets.CO2UpperThreshold || envData.TVOC >= targets.TVOCUpperThreshold || envData.Humidity >= targets.HumidityUpperThreshold )
	{
		printf("Gas or Humidity Higher Than Threshold CO2: %f TVOC: %f Turning Fan On \n", envData.Temperature, targets.TemperatureUpperThreshold);
		// Turn Fan on
		relay.Airflow(0);
	}

	else if( envData.CO2 < targets.CO2UpperThreshold && envData.TVOC < targets.TVOCUpperThreshold )
	{
		printf("Gas: %f Higher Than Threshold: %f - Turning Heater Off \n", envData.Temperature, targets.TemperatureUpperThreshold);
		// Turn Fan off if On
		relay.Airflow(1);
	}
	}
}


void Controller::ActuatorHandler()
{
	LightActuator();
	HeatActuator();
	AirflowActuator();
}
