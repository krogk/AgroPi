#define BOOST_TEST_MODULE AgroPiTest
#include <boost/test/unit_test.hpp>

#include "VEML7700.h"
#include "SHT31D.h"
#include "CCS811.h"
#include "Camera.h"
//#include "Actuator.h"

/*
BOOST_AUTO_TEST_CASE(FailTest)
{
    BOOST_CHECK_EQUAL(5, sqr(2));
}

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, sqr(2));
}
*/   

BOOST_AUTO_TEST_CASE( test )
{
    float lux;
    VEML7700 lightsensor;
    lightsensor.Initialize();
    lightsensor.Get_ALS_Lux( lux );

    BOOST_CHECK_MESSAGE( lux = 0.0, "Lux measured by light sensor is: " << lux << "Couldn't communicate with sensor " );
}
