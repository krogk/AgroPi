#define BOOST_TEST_MODULE AgroPiIntegrationTest
#include <boost/test/unit_test.hpp>

#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "SGP30.h"
#include "Camera.h"
//#include "Actuator.h"

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
BOOST_AUTO_TEST_CASE(I2C_SAMPLER_READ){

  uint16_t sampleCount = 0;
  uint16_t CRCErrorCount = 0;
  int SamplePeriod = 250000000;
  // define callback here

  // Sampler sampler(&samplerCallback);

  // sampler.start(SamplePeriod);
  /*
  while(sampleCount != 40)
  {
    sleep(1);
  }*/
    
  
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
BOOST_AUTO_TEST_CASE(CONTROLLER_EVENT_HANDLER){

  uint16_t sampleCount = 0;
  uint16_t CRCErrorCount = 0;
  // define callback here

  /*
  while(sampleCount != 40)
  {
    sleep(1);
  }
  */
  
}
BOOST_AUTO_TEST_SUITE_END()