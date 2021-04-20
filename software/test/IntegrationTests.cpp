#define BOOST_TEST_MODULE AgroPiIntegrationTest
#include <boost/test/unit_test.hpp>

#include "TestFunctions.h"
#include "Sampler.h"
#include "Controller.h"
#include "Camera.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "SGP30.h"
#include "Camera.h"
#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

// Definitions of Operation codes to test

// Target Update changes 
#define LIGHT_INTENSITY_UPPER_TARGET_CHANGE 	1
#define LIGHT_INTENSITY_LOWER_TARGET_CHANGE 	2
#define TEMPERATURE_UPPER_TARGET_CHANGE 			3
#define TEMPERATURE_LOWER_TARGET_CHANGE 			4
#define TVOC_UPPER_TARGET_CHANGE 							5
#define TVOC_LOWER_TARGET_CHANGE 							6
#define ECO2_UPPER_TARGET_CHANGE 						  7
#define ECO2_LOWER_TARGET_CHANGE 						  8
#define ETH_UPPER_TARGET_CHANGE								9
#define ETH_LOWER_TARGET_CHANGE								10
#define H2_UPPER_TARGET_CHANGE								11
#define H2_LOWER_TARGET_CHANGE								12
#define HUMIDITY_UPPER_TARGET_CHANGE          13
#define HUMIDITY_LOWER_TARGET_CHANGE 					14
// Force Flags
#define FORCE_HEATING													128
#define FORCE_AIRFLOW													129
#define FORCE_LIGHTS													130
#define FORCE_WATER_PUMP											131
// Heuristic Flags
#define ENABLE_HEATING_HEURISTIC							132
#define ENABLE_AIRFLOW_HEURISTIC							133
#define ENABLE_LIGHTS_HEURISTIC								134
#define ENABLE_WATER_PUMP_HEURISTIC						135

// RELAY BOARD
#define ACTUATOR_ON  0
#define ACTUATOR_OFF 1

// Test Sampler
BOOST_AUTO_TEST_SUITE(SAMPLER)

/**
* Test I2C Sampler
*
* This Test reads 40 samples (10 Seconds worth) of each enviroment 
* On each new Sample set Sampler uses callback which 
* checks whether the conditions are in reasonable range.
*
* @todo: Change the callback type in sampler to just contain a function, in the main program the functionality will remain unchanged but here it will allow for some testing
* 
*/
BOOST_AUTO_TEST_CASE(I2C_SAMPLER_READ)
{

  uint16_t sampleCount = 0;
  uint16_t CRCErrorCount = 0;
  // Define SampleRate of 250ms 
  int SamplePeriod = 250000000;
  // define callback here


  //std::cout << "Time difference: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time    - start_time).count() << " nanoseconds" << std::endl;

  // Sampler sampler(&samplerCallback);

  // sampler.start(SamplePeriod);
  /*
  // Start Timer to measure total execution time
  auto start_time = Clock::now();
  // Wait for sampler to read 40 samples
  while(sampleCount != 40) {}
  auto end_time = Clock::now();
  long int executionTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time    - start_time).count();
  float averageSampleTime = (executionTime/nSamples)
  BOOST_CHECK_MESSAGE( executionTime <= 40000.0,  "Execution Time: " <<  relay.m_fanGPIOState << " - Must Be 1 After Initialization" );

  */
    
  
}
BOOST_AUTO_TEST_SUITE_END()




// Test Sampler
BOOST_AUTO_TEST_SUITE(CONTROLLER)

/**
* Test I2C Sampler
*
* @todo: Change the callback type in sampler to just contain a function, in the main program the functionality will remain unchanged but here it will allow for some testing
* 
* actuatorsState
*	[0] = Heating state
*	[1] = Lighting state
*	[2] = Airflow state
*	[3] = Watering state
*/
BOOST_AUTO_TEST_CASE(CONTROLLER_OPERATION_HANDLER_FORCE_FLAGS)
{
  // Initialize Controller
	Controller controller;
  /*

	*/
  EnvironmentData controllerDefaultEnvData         = controller.envData;
  TargetEnvironmentData controllerDefaultTargets   = controller.targets;
  ActuationForceFlags  controllerDefaultForceFlags = controller.actuationForceFlags;
  ActuationHeuristicsFlags controllerDefaultHeuristicsFlags = controller.actuationHeuristicsFlags;

  // Test Force flags 
  for(int i = 0; i < 5; i++ )
  {
    BOOST_CHECK_MESSAGE( controller.actuatorsState[0] == ACTUATOR_OFF,  "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[1] == ACTUATOR_OFF,  "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[2] == ACTUATOR_OFF,  "Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[3] == ACTUATOR_OFF,  "Watering Actuator State is: " <<  controller.actuatorsState[3] << " - Must Be 1 After Initialization" );

    controller.UpdateHandler(FORCE_HEATING, 1);
    controller.UpdateHandler(FORCE_LIGHTS, 1);
    controller.UpdateHandler(FORCE_AIRFLOW, 1);
    controller.UpdateHandler(FORCE_WATER_PUMP, 1);
    controller.UpdateHandler(FORCE_WATER_PUMP, 1);
    controller.UpdateGPIOStates();

    BOOST_CHECK_MESSAGE( controller.actuatorsState[0] == ACTUATOR_ON,  "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 - OFF" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[1] == ACTUATOR_ON,  "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 - OFF" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[2] == ACTUATOR_ON,  "Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 - OFF" );
    BOOST_CHECK_MESSAGE( controller.actuatorsState[3] == ACTUATOR_ON,  "Watering Actuator State is: " <<  controller.actuatorsState[3] << " - Must Be 1 - OFF" );
    sleep(1);

    controller.UpdateHandler(FORCE_HEATING, 0);
    controller.UpdateHandler(FORCE_LIGHTS, 0);
    controller.UpdateHandler(FORCE_AIRFLOW, 0);
    controller.UpdateHandler(FORCE_WATER_PUMP, 0);
    controller.UpdateGPIOStates();
    sleep(1);
  }
}

//BOOST_AUTO_TEST_SUITE_END()


/**
* This test esentially tests sampler its callback and functionality of controller actuator handler  
*  1. Use Sampler to get data 
      Check measurments are within range
   2. Use callback For actuaction
   3. 
* 
*/
BOOST_AUTO_TEST_CASE(CONTROLLER_OPERATION_HANDLER_UPDATE_TARGETS)
{
  // Enable Heuristic flags
  
  // Initialize Controller
  Controller controller;
  // Initialize Sampler Sensor
  Sampler sampler(&controller);

  // Light Heuristics
  BOOST_CHECK_MESSAGE( controller.actuationHeuristicsFlags.Lighting  == 0,  "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  // Take Measurements
  sampler.Gather_Env_Data();
  // Get a copy of env data struct
  EnvironmentData samplerMeasurement = sampler.GetEnvData();
  // Check measurement is within range
  int luxCheck = CheckEnvironmentalVariableValue(  samplerMeasurement.LightIntensity, LUX_MIN, LUX_MAX, LUX_MIN_REASONABLE, LUX_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( luxCheck == 0,"Lux measured by sensor is outside valid range, Status Code: " << luxCheck << " Zero" );
  // Calculate new lower thershold by +large value to current reading and set new targets
  controller.UpdateHandler(LIGHT_INTENSITY_LOWER_TARGET_CHANGE, (LUX_MAX-10) );
  controller.UpdateHandler(LIGHT_INTENSITY_UPPER_TARGET_CHANGE, (LUX_MAX) );
  // Run Actuator, it will turn on if heuristic flag is on but is expected to be off by default.
  sampler.CallbackTest();
  // Update Actuator tests
  controller.UpdateGPIOStates(); 
  // Check target values changed
  BOOST_CHECK_MESSAGE( controller.targets.LightIntensityUpperThreshold == (LUX_MAX),   "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  BOOST_CHECK_MESSAGE( controller.targets.LightIntensityLowerThreshold == (LUX_MAX-10),"Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  // Check actuator is off
  BOOST_CHECK_MESSAGE( controller.actuatorsState[1] == ACTUATOR_OFF,  "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  // Turn Heuristic Flag on
  controller.UpdateHandler(ENABLE_LIGHTS_HEURISTIC, 1);
  // Run Actuator again
  sampler.CallbackTest();
  // Get States
  controller.UpdateGPIOStates(); 
  BOOST_CHECK_MESSAGE( controller.actuatorsState[1] == ACTUATOR_ON,  "Lighting Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  // Turn Heuristic Flag off
  controller.UpdateHandler(ENABLE_LIGHTS_HEURISTIC, 0);

  // Heating Heuristics
  BOOST_CHECK_MESSAGE( controller.actuationHeuristicsFlags.Heating  == 0,  "Heating Actuator State is: " <<  controller.actuatorsState[1] << " - Must Be 1 After Initialization" );
  // Take Measurements
  sampler.Gather_Env_Data();
  // Get a copy of env data struct
  samplerMeasurement = sampler.GetEnvData();
  // Check measurement is within range
  int tempeatureCheck = CheckEnvironmentalVariableValue(samplerMeasurement.Temperature, TEMPERATURE_MIN, TEMPERATURE_MAX, TEMPERATURE_MIN_REASONABLE, TEMPERATURE_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( tempeatureCheck == 0,"Temperature measured by sensor is outside valid range, Status Code: " << tempeatureCheck << " Zero" );
  // Calculate new lower thershold by +large value to current reading and set new targets
  controller.UpdateHandler(TEMPERATURE_UPPER_TARGET_CHANGE, (TEMPERATURE_MAX) );
  controller.UpdateHandler(TEMPERATURE_LOWER_TARGET_CHANGE, (TEMPERATURE_MAX-10) );
  // Run Actuator, it will turn on if heuristic flag is on but is expected to be off by default.
  sampler.CallbackTest();
  // Update Actuator tests
  controller.UpdateGPIOStates(); 
  // Check target values changed
  BOOST_CHECK_MESSAGE( controller.targets.TemperatureUpperThreshold == (TEMPERATURE_MAX),   "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
  BOOST_CHECK_MESSAGE( controller.targets.TemperatureLowerThreshold == (TEMPERATURE_MAX-10),"Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
  // Check actuator is off
  BOOST_CHECK_MESSAGE( controller.actuatorsState[0] == ACTUATOR_OFF,  "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
  // Turn Heuristic Flag on
  controller.UpdateHandler(ENABLE_HEATING_HEURISTIC, 1);
  // Run Actuator again
  sampler.CallbackTest();
  // Get States
  controller.UpdateGPIOStates(); 
  BOOST_CHECK_MESSAGE( controller.actuatorsState[0] == ACTUATOR_ON,  "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
  // Turn Heuristic Flag off
  controller.UpdateHandler(ENABLE_HEATING_HEURISTIC, 0);


  // Airflow Heuristics
  BOOST_CHECK_MESSAGE( controller.actuationHeuristicsFlags.Airflow  == 0,  "Heating Actuator State is: " <<  controller.actuatorsState[0] << " - Must Be 1 After Initialization" );
  // Take Measurements
  sampler.Gather_Env_Data();
  // Get a copy of env data struct
  samplerMeasurement = sampler.GetEnvData();
  // Check measurement is within range
  int HumidityCheck = CheckEnvironmentalVariableValue(samplerMeasurement.Humidity, HUMDIITY_MIN, HUMIDITY_MAX, HUMDIITY_MIN_REASONABLE, HUMIDITY_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( HumidityCheck == 0,"Humidity measured by sensor is outside valid range, Status Code: " << HumidityCheck << " Zero" );
  // Calculate new lower thershold by +large value to current reading and set new targets
  controller.UpdateHandler(HUMIDITY_UPPER_TARGET_CHANGE, (HUMDIITY_MIN+10));
  controller.UpdateHandler(HUMIDITY_LOWER_TARGET_CHANGE, (HUMDIITY_MIN) );
  // Run Actuator, it will turn on if heuristic flag is on but is expected to be off by default.
  sampler.CallbackTest();
  // Update Actuator tests
  controller.UpdateGPIOStates(); 
  // Check target values changed
  BOOST_CHECK_MESSAGE( controller.targets.HumidityUpperThreshold == (HUMDIITY_MIN+10),   "Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 After Initialization" );
  BOOST_CHECK_MESSAGE( controller.targets.HumidityLowerThreshold == (HUMDIITY_MIN),"Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 After Initialization" );
  // Check actuator is off
  BOOST_CHECK_MESSAGE( controller.actuatorsState[2] == ACTUATOR_OFF,  "Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 After Initialization" );
  // Turn Heuristic Flag on
  controller.UpdateHandler(ENABLE_AIRFLOW_HEURISTIC, 1);
  // Run Actuator again
  sampler.CallbackTest();
  // Get States
  controller.UpdateGPIOStates(); 
  BOOST_CHECK_MESSAGE( controller.actuatorsState[2] == ACTUATOR_ON,  "Airflow Actuator State is: " <<  controller.actuatorsState[2] << " - Must Be 1 After Initialization" );
  controller.UpdateHandler(ENABLE_AIRFLOW_HEURISTIC, 0);

  /*
  int co2Check = CheckEnvironmentalVariableValue(samplerMeasurement.CO2, ECO2_MIN, ECO2_MAX, ECO2_MIN_REASONABLE, ECO2_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( co2Check == 0,"Carbon Dioxide measured by sensor is outside valid range, Status Code: " << co2Check << " Zero" );

  int tvocCheck = CheckEnvironmentalVariableValue(samplerMeasurement.TVOC, TVOC_MIN, TVOC_MAX, TVOC_MIN_REASONABLE, TVOC_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( tvocCheck == 0,"tvoc measured by sensor is outside valid range, Status Code: " << tvocCheck << " Zero" );

  int ethCheck = CheckEnvironmentalVariableValue(samplerMeasurement.RawEthanol, ETH_MIN, ETH_MAX, ETH_MIN_REASONABLE, ETH_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( tvocCheck == 0,"Ethanol measured by sensor is outside valid range, Status Code: " << ethCheck << " Zero" );

  int h2Check = CheckEnvironmentalVariableValue(samplerMeasurement.RawH2, H2_MIN, H2_MAX, H2_MIN_REASONABLE, H2_MAX_REASONABLE);
  BOOST_CHECK_MESSAGE( tvocCheck == 0,"Hydrogen measured by sensor is outside valid range, Status Code: " << h2Check << " Zero" );
  */
  //samplerRead = sampler.GetEnvData();
}
BOOST_AUTO_TEST_SUITE_END()


// Web 
/*
BOOST_AUTO_TEST_SUITE(WEB_SERVER_TESTS)


BOOST_AUTO_TEST_CASE()
{

  
}
BOOST_AUTO_TEST_SUITE_END()
*/