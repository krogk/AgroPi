#define BOOST_TEST_MODULE AgroPiTest
#include <boost/test/unit_test.hpp>

#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "SGP30.h"
#include "Camera.h"
#include "GPIODriver.h"
#include "RelayBoard.h"

// Define



/**
 * Environment Data Struct Definition
 * 
 * This struct conatins actuator Heuristics flags.
 * If a flag is set the actuator enables the control through Heuristics
 *
 */
 /*
 typedef struct{

    float LUX_MIN = 0;
    float LUX_MAX 120000;
    float LUX_MIN_REASONABLE 20;
    float LUX_MAX_REASONABLE 10000;

    float TEMPERATURE_MIN -40;
    float TEMPERATURE_MAX 125;
    float TEMPERATURE_MIN_REASONABLE 15;
    float TEMPERATURE_MAX_REASONABLE 25;

    float HUMDIITY_MIN 0;
    float HUMIDITY_MAX 100;
    float HUMDIITY_MIN_REASONABLE 45;
    float HUMIDITY_MAX_REASONABLE 65;
    
    float HUMDIITY_MIN 0;
    float HUMIDITY_MAX 100;
    float HUMDIITY_MIN_REASONABLE 45;
    float HUMIDITY_MAX_REASONABLE 65;


} TargetValues;
*/


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
    
    close(fd);
}
BOOST_AUTO_TEST_SUITE_END()


// Test Light Sensor
BOOST_AUTO_TEST_SUITE(LIGHT_SENSOR)

/**
* Test VEML7700 Sensor Driver 
*
* Open File Descriptor and check if it is non-zero
* Get a reading and make sure it is not below zero(minimum) or above 120k(maximum) and not equal to 
*/
BOOST_AUTO_TEST_CASE(VEML770_LUX_READ)
{
    float lux = 0.0;
    I2CDriver driver;
    VEML7700 lightsensor;
    // Initialize sensor
    lightsensor.Initialize(driver);
    //BOOST_CHECK_MESSAGE( fd != 0, "File descriptor:  " << fd << "  Incorrect Value" );
    // Attempt to read lux
    lightsensor.Get_ALS_Lux( lux );
    // If lux is 0 it means the I2C communication wasn't effective.
    BOOST_CHECK_MESSAGE( lux > 0.0,    "Lux measured by light sensor is: " << lux << " Zero" );
    // If lux is above 120000, it is highly likely the value obtained is incorrect.
    BOOST_CHECK_MESSAGE( lux < 120000, "Lux measured by light sensor is: " << lux << " - Above Maximum(120000)" );
    lightsensor.Close_Device();
}
BOOST_AUTO_TEST_SUITE_END()


// Test Temperature and Humidity Sensor
BOOST_AUTO_TEST_SUITE(TEMP_HUM_SENSOR)
/**
* Test SHT31D Sensor Driver 
*
* Open File Descriptor and check if it is non-zero
* Get a remperature reading and make sure it is not below zero(unlikley) or above 50(unlikley)
* Get a remperature reading and make sure it is not below zero(minimum) or above 100(maxiumum)
*/
BOOST_AUTO_TEST_CASE( SHT31D_READ )
{
    I2CDriver driver;
    SHT31D temperatureHumiditySensor;
    float temp = 0, humidity = 0;
    temperatureHumiditySensor.Initialize(driver);
    temperatureHumiditySensor.Get_Temperature_Humidity(temp, humidity);
    BOOST_CHECK_MESSAGE( temp > 10.0f,   "Temperature measured by SHT31D: " << temp << " C - Too Low" );
    BOOST_CHECK_MESSAGE( temp < 60.0f,  "Temperature measured by SHT31D: " << temp << " C - Too High" );
    BOOST_CHECK_MESSAGE( humidity > 0.0f,   "Temperature measured by SHT31D: " << humidity << " % - Too Low" );
    BOOST_CHECK_MESSAGE( humidity < 100.0f,  "Temperature measured by SHT31D: " << humidity << " % - Too High" );
    temperatureHumiditySensor.Close_Device();

}
BOOST_AUTO_TEST_SUITE_END()

// Test Gas Sensor
BOOST_AUTO_TEST_SUITE(GAS_SENSOR)
/**
* Test SGP30 Gas Sensor Driver 
*
* Open File Descriptor and check if it is non-zero
* Get a remperature reading and make sure it is not below zero(unlikley) or above 50(unlikley)
* Get a remperature reading and make sure it is not below zero(minimum) or above 100(maxiumum)
*/
BOOST_AUTO_TEST_CASE( SGP30_READ )
{
    I2CDriver driver;
    SGP30 gasSensor;
    uint16_t tvoc = 0, eco2 = 0;
    gasSensor.Initialize(driver);
    gasSensor.IAQ_Measure(tvoc,eco2);
    BOOST_CHECK_MESSAGE( tvoc >= 0.0f, "TVOC measured by SHT31D: " << tvoc << " ppb - Too Low" );
    BOOST_CHECK_MESSAGE( eco2 > 0.0f,  "eCO2 measured by SHT31D: " << eco2 << " ppm - Too Low" );
    gasSensor.Close_Device();
}
BOOST_AUTO_TEST_SUITE_END()


// Test Relay Board
BOOST_AUTO_TEST_SUITE(Relays)
/**
* Test Relay Board 
* Turn on 
*/
BOOST_AUTO_TEST_CASE( ElegoRelayBoard )
{
    GPIODriver driver;
    RelayBoard relay;
    relay.Initialize(driver);

    // Turn On Each Actuator for 1 Second.
    relay.Heating(0);
    //BOOST_CHECK_MESSAGE( eco2 > 0.0f,  "Temperature measured by SHT31D: " << eco2 << " ppm - Too Low" );
    sleep(1);
    relay.Heating(1);
    relay.Lighting(0);
    sleep(1);
    relay.Lighting(1);
    relay.Airflow(0);
    sleep(1);
    relay.Airflow(1);
    relay.Watering(0);
    sleep(1);
    relay.Watering(1);
    sleep(1);

    // Turn all actuators for 5 seconds.
    relay.Lighting(0);
    relay.Heating(0);
    relay.Airflow(0);
    relay.Watering(0);
    sleep(5);
    relay.Lighting(1);
    relay.Heating(1);
    relay.Airflow(1);
    relay.Watering(1);

    // Close Device
    relay.Turn_Relays_Off();

}
BOOST_AUTO_TEST_SUITE_END()


/*// Test Camera
BOOST_AUTO_TEST_SUITE(CAMERA)
BOOST_AUTO_TEST_CASE( Camera ) {
}
BOOST_AUTO_TEST_SUITE_END()
*/

