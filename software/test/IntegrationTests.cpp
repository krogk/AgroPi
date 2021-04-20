#define BOOST_TEST_MODULE AgroPiIntegrationTest
#include <boost/test/unit_test.hpp>

#include "Sampler.h"
#include "Controller.h"
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
  while(sampleCount != 40)
  {
   
  }
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
*/
BOOST_AUTO_TEST_CASE(CONTROLLER_OPERATION_HANDLER)
{

  uint16_t sampleCount = 0;
  uint16_t CRCErrorCount = 0;

  // Initialize Controller
	Controller controller;

  EnvironmentData controllerDefaultEnvData         = controller.envData;
  TargetEnvironmentData controllerDefaultTargets   = controller.targets;
  ActuationForceFlags  controllerDefaultForceFlags = controller.actuationForceFlags;
  ActuationHeuristicsFlags controllerDefaultHeuristicsFlags = controller.actuationHeuristicsFlags;

  // New Values vector corresponds in sequence to the operation codes
  uint16_t NewTargetvalues[14] = { 300,
                                  100,
                                  50,
                                  10,
                                  1000,
                                  100,
                                  1000,
                                  100,
                                  1000,
                                  100,
                                  1000,
                                  100,
                                  90,
                                  30 };

  // int counter = 0;
  //controller.UpdateHandler(LIGHT_INTENSITY_UPPER_TARGET_CHANGE, NewTargetvalues[0]);
  // BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_OFF,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 1 After Initialization" );


}
BOOST_AUTO_TEST_SUITE_END()