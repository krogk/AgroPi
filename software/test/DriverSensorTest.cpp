#define BOOST_TEST_MODULE AgroPiTest
#include <boost/test/unit_test.hpp>

#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "CCS811.h"
#include "Camera.h"
//#include "Actuator.h"

// Test I2C Driver
BOOST_AUTO_TEST_SUITE(I2C_DRIVER)

/**
* Test I2C Driver 
*
* Open File Descriptor and check if it is non-zero
* @todo: Do a read or write and see check the reply is zero
* 
*/
BOOST_AUTO_TEST_CASE(I2C_PLAIN_WRITE_READ){
    //BOOST_TEST_MESSAGE( "Testing I2C Driver:" );
    //BOOST_TEST_MESSAGE( "Variable:" << variable );
    int fd = 0;
    int readCount = 1;
    uint8_t buffer[readCount];
    I2CDriver driver;

    // Setup file descriptor for unused address
    fd = driver.I2C_Setup_File(0x03);
    BOOST_CHECK_MESSAGE( fd != 0, "File descriptor:  " << fd << "  Initial Value Hasn't Changed" );
    // Do single by write using Plain I2C
    //driver.Plain_I2C_Write_Read(fd, 0x0303, buffer, 1);
    // Ensure no device replied
    //BOOST_CHECK_MESSAGE( buffer[0] == 0, "Buffer Was Modified: " << buffer[0] << " Unexpected Read" );
}
BOOST_AUTO_TEST_SUITE_END()


// Test Light Sensor
BOOST_AUTO_TEST_SUITE(LIGHT_SENSOR)

/**
* Test I2C Driver 
*
* Open File Descriptor and check if it is non-zero
* 
*/
BOOST_AUTO_TEST_CASE(VEML770_LUX_READ){
    float lux;
    VEML7700 lightsensor;
    // Initialize sensor
    lightsensor.Initialize();
    //BOOST_CHECK_MESSAGE( fd != 0, "File descriptor:  " << fd << "  Incorrect Value" );
    // Attempt to read lux
    lightsensor.Get_ALS_Lux( lux );
    // If lux is 0 it means the I2C communication wasn't effective.
    BOOST_CHECK_MESSAGE( lux > 0.0,    "Lux measured by light sensor is: " << lux << " Zero" );
    // If lux is above 120000, it is highly likely the value obtained is incorrect.
    BOOST_CHECK_MESSAGE( lux < 120000, "Lux measured by light sensor is: " << lux << " - Above Maximum(120000)" );
}
BOOST_AUTO_TEST_SUITE_END()

/*
// Test Temperature and Humidity Sensor
BOOST_AUTO_TEST_SUITE(LIGHT_SENSOR)
BOOST_AUTO_TEST_CASE( SHT31D ) {

}
BOOST_AUTO_TEST_SUITE_END()

// Test Camera
BOOST_AUTO_TEST_SUITE(CAMERA)
BOOST_AUTO_TEST_CASE( Camera ) {

}
BOOST_AUTO_TEST_SUITE_END()

// Test Gas Sensor
BOOST_AUTO_TEST_SUITE(SGP30)
BOOST_AUTO_TEST_CASE( SGP30 ) {

}
BOOST_AUTO_TEST_SUITE_END()
*/