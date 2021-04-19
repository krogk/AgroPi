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
#include "Controller.h"
#include <stdio.h>
#include <string>
#include <iostream>


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
	ActuatorHandler();
}

/**
* Handle Messages from the web server.
*
* @param	opcode ID of the operation, this has been defined in CONTROL_OP_CODES enumeration.
* @param 	value  value to assign to the variable
*
* @return Zero On Sucess 
*/
void Controller::MessageHandler(uint8_t opcode, float value)
{
	printf("Operation %d Value: %f\n", opcode, value);
	// Switch with OP CODE
	switch(opcode)
  {
		// Target Values change 
		// Light Intensity
		case LIGHT_INTENSITY_UPPER_TARGET_CHANGE:
			targets.LightIntensityUpperThreshold = value; 
			printf("LIGHT_INTENSITY_TARGET_CHANGE\n");
  	break;

  	case LIGHT_INTENSITY_LOWER_TARGET_CHANGE:
	  	targets.LightIntensityLowerThreshold = value;
			printf("LIGHT_INTENSITY_TARGET_CHANGE\n");
  	break;

		// Temperature
  	case TEMPERATURE_UPPER_TARGET_CHANGE:
	  	targets.TemperatureUpperThreshold = value; 					
			printf("TEMPERATURE_TARGET_CHANGE\n");
  	break;

  	case TEMPERATURE_LOWER_TARGET_CHANGE:
  		targets.TemperatureLowerThreshold = value; 	
			printf("TEMPERATURE_TARGET_CHANGE\n");
  	break;

		// Humidity
  	case HUMIDITY_UPPER_TARGET_CHANGE:
	  	targets.HumidityUpperThreshold = value; 				
			printf("HUMIDITY_TARGET_CHANGE\n");	
  	break;

		case HUMIDITY_LOWER_TARGET_CHANGE:			
  		targets.HumidityLowerThreshold = value; 
			printf("HUMIDITY_TARGET_CHANGE\n");	
  	break;

		// TVOC
  	case TVOC_UPPER_TARGET_CHANGE:	
  		targets.TVOCUpperThreshold = value;
			printf("TVOC_TARGET_CHANGE\n"); 	
  	break;

	  case TVOC_LOWER_TARGET_CHANGE:	
  		targets.TVOCLowerThreshold = value;
			printf("TVOC_TARGET_CHANGE\n"); 	
  	break;

		// Carbon Dioxide
		case ECO2_UPPER_TARGET_CHANGE:
			targets.CO2UpperThreshold = value; 	
			printf("ECO2_TARGET_CHANGE\n");
		break;

		case ECO2_LOWER_TARGET_CHANGE:
			targets.CO2LowerThreshold = value; 	
			printf("ECO2_TARGET_CHANGE\n");
		break;

		// Ethanol
		case ETH_UPPER_TARGET_CHANGE:
			targets.RawEthanolUpperThreshold = value; 
			printf("ETHANOL_TARGET_CHANGE\n");	
		break;

		case ETH_LOWER_TARGET_CHANGE:
			targets.RawEthanolUpperThreshold = value; 
			printf("ETHANOL_TARGET_CHANGE\n");	
		break;

		// H2 
		case H2_UPPER_TARGET_CHANGE:
			targets.RawH2UpperThreshold = value; 
			printf("H2_TARGET_CHANGE\n");		
		break;

		case H2_LOWER_TARGET_CHANGE:
			targets.RawH2UpperThreshold = value; 
			printf("H2_TARGET_CHANGE\n");		
		break;

		// Force flags
		case FORCE_HEATING:
			(value > 0) ? actuationForceFlags.Heating  = true : actuationForceFlags.Heating = false;
			(actuationForceFlags.Heating  == true ) ? relay.Heating(0) : relay.Heating(1);
			printf("FORCE_HEATING\n");		
		break;
		
		case FORCE_AIRFLOW:
			(value > 0) ? actuationForceFlags.Airflow  = true : actuationForceFlags.Airflow = false;
			(actuationForceFlags.Airflow  == true ) ? relay.Airflow(0) : relay.Airflow(1);
			printf("FORCE_AIRFLOW\n");
		break;
		
		case FORCE_LIGHTS:
			(value > 0) ? actuationForceFlags.Lighting  = true : actuationForceFlags.Lighting = false;
			(actuationForceFlags.Lighting  == true ) ? relay.Lighting(0) : relay.Lighting(1);
			printf("FORCE_LIGHTS\n");		
		break;
	
		case FORCE_WATER_PUMP:
			(value > 0) ? actuationForceFlags.Watering  = true : actuationForceFlags.Watering = false;
			(actuationForceFlags.Watering  == true ) ? relay.Watering(0) : relay.Watering(1);
			printf("FORCE_WATER_PUMP\n");		
		break;

		// Heuristics flags
		case ENABLE_HEATING_HEURISTIC:
			(value > 0) ? actuationHeuristicsFlags.Heating  = true : actuationHeuristicsFlags.Heating = false;
			printf("ENABLE_HEATING_HEURISTIC\n");		
		break;
		
		case ENABLE_AIRFLOW_HEURISTIC:
			(value > 0) ? actuationHeuristicsFlags.Airflow  = true : actuationHeuristicsFlags.Airflow = false;
			printf("ENABLE_AIRFLOW_HEURISTIC\n");
		break;
		
		case ENABLE_LIGHTS_HEURISTIC:
			(value > 0) ? actuationHeuristicsFlags.Lighting  = true : actuationHeuristicsFlags.Lighting = false;
			printf("ENABLE_LIGHTS_HEURISTIC\n");		
		break;
	
		case ENABLE_WATER_PUMP_HEURISTIC:
			(value > 0) ? actuationHeuristicsFlags.Watering  = true : actuationHeuristicsFlags.Watering = false;
			printf("ENABLE_WATER_PUMP_HEURISTIC\n");		
		break;

		default:
			printf("Unknown Opcode!\n");
		break;
  }
}

/**
* Handle Messages from the web server.
*
* @return Zero On Sucess 
*/
void Controller::LightActuator()
{
	// If Force Lighting is enabled
	if(( actuationForceFlags.Lighting) && (relay.m_lightsGPIOState == 1))
	{
		relay.Lighting(0);
	}
	// If Force Lighting is enabled
	else if(actuationHeuristicsFlags.Lighting)
	{
		// Ambient light level lower than thershold and lights not already on
		if( envData.LightIntensity < targets.LightIntensityLowerThreshold && relay.m_lightsGPIOState == 1)
		{
			printf("Light Intensity: %f Lower Than Threshold: %f - Turning Lights On \n", envData.LightIntensity, targets.LightIntensityLowerThreshold);
			// turn lights on
			relay.Lighting(0);
		}
		// Light Higher than The Thershold
		else if( envData.LightIntensity >= targets.LightIntensityUpperThreshold && relay.m_lightsGPIOState == 0 )
		{
			printf("Light Intensity: %f Higher Than Threshold: %f - Turning Lights Off \n", envData.LightIntensity, targets.LightIntensityUpperThreshold);
			relay.Lighting(1);
		}
	}
}

void Controller::HeatActuator()
{
	// If force heating is enabled
	if(actuationForceFlags.Heating && (relay.m_heaterGPIOState == 1))
	{
		relay.Heating(0);
	}
	// If heuristic for heating is enabled
	else if(actuationHeuristicsFlags.Heating)
	{
	// Temperature Lower Than Threshold and heating element not already on 
	if( envData.Temperature < targets.TemperatureLowerThreshold && relay.m_heaterGPIOState == 1)
		{
			printf("Temperature: %f Lower Than Threshold: %f - Turning Heater On \n", envData.Temperature, targets.TemperatureLowerThreshold);
			// turn heater on
			relay.Heating(0);
		}

		else if( envData.Temperature > targets.TemperatureUpperThreshold && relay.m_heaterGPIOState == 0)
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
	if( (actuationForceFlags.Airflow) && (relay.m_fanGPIOState == 1))
	{
		relay.Airflow(0);
	}
	// If Force Lighting is enabled
	else if(actuationHeuristicsFlags.Airflow)
	{
		// Airflow
	if( (envData.CO2 >= targets.CO2UpperThreshold) || (envData.TVOC >= targets.TVOCUpperThreshold )
			|| (envData.Humidity >= targets.HumidityUpperThreshold)  && (relay.m_fanGPIOState == 1 ) )
	{
		printf("Gases or Humidity Higher Than Threshold CO2: %f TVOC: %f Turning Fan On \n", envData.Temperature, targets.TemperatureUpperThreshold);
		// Turn Fan on
		relay.Airflow(0);
	}

	else if( (envData.Humidity <= targets.HumidityUpperThreshold) && envData.CO2 < targets.CO2UpperThreshold && envData.TVOC < targets.TVOCUpperThreshold  && (relay.m_fanGPIOState == 0 ) )
	{
		//printf("Gas: %f Higher Than Threshold: %f - Turning Heater Off \n", envData.Temperature, targets.TemperatureUpperThreshold);
		// Turn Fan off if On
		relay.Airflow(1);
	}
	}
}



void Controller::WateringActuator()
{
	// If Force Lighting is enabled
	if(actuationForceFlags.Watering  && (relay.m_waterPumpGPIO == 1))
	{
		relay.Watering(0);
	}
	// If Force Lighting is enabled
	//else if(actuationHeuristicsFlags.Watering)
	//{

	//}
}

/**
* Runs each actuator routine by turn.
* Lighting
* Heating
* Airflow
* Watering -
*
* @return Zero On Success 
*/
void Controller::ActuatorHandler()
{
	LightActuator();
	HeatActuator();
	AirflowActuator();
	WateringActuator();
}
