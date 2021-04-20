#define BOOST_TEST_MODULE AgroPiTest
#include <boost/test/unit_test.hpp>

#include "I2CDriver.h"
#include "VEML7700.h"
#include "SHT31D.h"
#include "SGP30.h"
#include "Camera.h"
#include "GPIODriver.h"
#include "RelayBoard.h"


// Define tolerable ranges for sensors reads
// VEML7700
#define LUX_MIN 0
#define LUX_MAX 120000
#define LUX_MIN_REASONABLE 20
#define LUX_MAX_REASONABLE 10000

// SHT31D
#define TEMPERATURE_MIN -40
#define TEMPERATURE_MAX 125
#define TEMPERATURE_MIN_REASONABLE 15
#define TEMPERATURE_MAX_REASONABLE 30
#define HUMDIITY_MIN 0
#define HUMIDITY_MAX 100
#define HUMDIITY_MIN_REASONABLE 45
#define HUMIDITY_MAX_REASONABLE 65

// SGP30
#define TVOC_MIN 0
#define TVOC_MAX 60000
#define TVOC_MIN_REASONABLE 0
#define TVOC_MAX_REASONABLE 1000

#define ECO2_MIN 0
#define ECO2_MAX 60000
#define ECO2_MIN_REASONABLE 0
#define ECO2_MAX_REASONABLE 2000

#define ETH_MIN 0
#define ETH_MAX 60000
#define ETH_MIN_REASONABLE 0
#define ETH_MAX_REASONABLE 1000

#define H2_MIN 0
#define H2_MAX 60000
#define H2_MIN_REASONABLE 0
#define H2_MAX_REASONABLE 1000

// RELAY BOARD
#define RELAY_ON  0
#define RELAY_OFF 1


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
    printf("Testing I2C Driver...");
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
    BOOST_CHECK_MESSAGE( lux > LUX_MIN, "Lux measured by light sensor is: " << lux << " Zero" );

    // Take 10 Measurements 1 second apart
    for(int i = 0; i < 10; i++ )
    {
        lightsensor.Get_ALS_Lux( lux );
        // If lux is 0 it means the I2C communication wasn't effective.
        BOOST_CHECK_MESSAGE( lux > LUX_MIN, "Lux measured by VEML7700: " << lux << " Zero" );
        // If lux is above 120000, it is highly likely the value obtained is incorrect.
        BOOST_CHECK_MESSAGE( lux < LUX_MAX, "Lux measured by VEML7700: " << lux << " - Above Maximum(120000)" );
        // Check if it below reasonable level
        BOOST_CHECK_MESSAGE( lux > LUX_MIN_REASONABLE, "Lux measured by VEML7700: " << lux << " - Below Reasonable Threshold" );
        // If lux is above 120000, it is highly likely the value obtained is incorrect.
        BOOST_CHECK_MESSAGE( lux < LUX_MAX_REASONABLE, "Lux measured by VEML7700: " << lux << " - Above Reasonable Threshold" );
        sleep(1);
    }
    // Close Device
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

    for(int i = 0; i < 10 ; i++ )
    {
        temperatureHumiditySensor.Get_Temperature_Humidity(temp, humidity);
        BOOST_CHECK_MESSAGE( temp > TEMPERATURE_MIN, "Temperature measured by SHT31D: " << temp << " C - Below Minimum" );
        BOOST_CHECK_MESSAGE( temp < TEMPERATURE_MAX, "Temperature measured by SHT31D: " << temp << " C - Above Maximum" );
        BOOST_CHECK_MESSAGE( temp > TEMPERATURE_MIN_REASONABLE,  "Temperature measured by SHT31D: " << temp << " C - Below Reasonable Threshold" );
        BOOST_CHECK_MESSAGE( temp < TEMPERATURE_MAX_REASONABLE,  "Temperature measured by SHT31D: " << temp << " C - Above Reasonable Threshold" );

        BOOST_CHECK_MESSAGE( humidity > HUMDIITY_MIN, "Humidity measured by SHT31D: " << humidity << " C - Below Minimum" );
        BOOST_CHECK_MESSAGE( humidity < HUMIDITY_MAX, "Humidity measured by SHT31D: " << humidity << " C - Above Maximum" );
        BOOST_CHECK_MESSAGE( humidity > HUMDIITY_MIN_REASONABLE,  "Humidity measured by SHT31D: " << humidity << " C - Below Reasonable Threshold" );
        BOOST_CHECK_MESSAGE( humidity < HUMIDITY_MAX_REASONABLE,  "Humidity measured by SHT31D: " << humidity << " C - Above Reasonable Threshold" );
        temp = 0;
        humidity = 0;
        sleep(1);
    }
    // Close Device
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
    
    for(int i = 0; i < 10 ; i++ )
    {
        gasSensor.IAQ_Measure(tvoc,eco2);
        BOOST_CHECK_MESSAGE( tvoc >= TEMPERATURE_MIN, "TVOC measured by SGP30: " << tvoc << " ppb - Below Minimum" );
        BOOST_CHECK_MESSAGE( tvoc < TEMPERATURE_MAX, "TVOC measured by SGP30: " << tvoc << " ppb - Above Maximum" );
        BOOST_CHECK_MESSAGE( tvoc >= TEMPERATURE_MIN_REASONABLE,  "TVOC measured by SGP30: " << tvoc << " ppb - Below Reasonable Threshold" );
        BOOST_CHECK_MESSAGE( tvoc < TEMPERATURE_MAX_REASONABLE,  "TVOC measured by SGP30: " << tvoc << " ppb - Above Reasonable Threshold" );

        BOOST_CHECK_MESSAGE( eco2 >= HUMDIITY_MIN, "ECO2 measured by SGP30: " << eco2 << " ppm - Below Minimum" );
        BOOST_CHECK_MESSAGE( eco2 < HUMIDITY_MAX, "ECO2 measured by SGP30: " << eco2 << " ppm - Above Maximum" );
        BOOST_CHECK_MESSAGE( eco2 >= HUMDIITY_MIN_REASONABLE,  "ECO2 measured by SGP30: " << eco2 << " ppm - Below Reasonable Threshold" );
        BOOST_CHECK_MESSAGE( eco2 < HUMIDITY_MAX_REASONABLE,  "ECO2 measured by SGP30: " << eco2 << " ppm - Above Reasonable Threshold" );
        tvoc = 0;
        eco2 = 0;
        sleep(1);
    }
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
    
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_OFF,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_lightsGPIOState == RELAY_OFF,  "Lighting GPIO State is: " <<  relay.m_lightsGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_fanGPIOState == RELAY_OFF,  "Airflow GPIO State is: " <<  relay.m_fanGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_waterPumpGPIOState == RELAY_OFF,  "Watering GPIO State is: " <<  relay.m_waterPumpGPIOState << " - Must Be 1 After Initialization" );

    // Turn On Each Actuator for 1 Second.
    relay.Heating(0);
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_ON,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 0" );
    //BOOST_CHECK_MESSAGE( eco2 == relay,  "Temperature measured by SHT31D: " << eco2 << " ppm - Too Low" );
    sleep(1);
    relay.Heating(1);
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_OFF,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 0" );
    relay.Lighting(0);
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_OFF,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 0" );
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
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_ON,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_lightsGPIOState == RELAY_ON,  "Lighting GPIO State is: " <<  relay.m_lightsGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_fanGPIOState == RELAY_ON,  "Airflow GPIO State is: " <<  relay.m_fanGPIOState << " - Must Be 1 After Initialization" );
    BOOST_CHECK_MESSAGE( relay.m_waterPumpGPIOState == RELAY_ON,  "Watering GPIO State is: " <<  relay.m_waterPumpGPIOState << " - Must Be 1 After Initialization" );
    sleep(5);
    relay.Lighting(1);
    relay.Heating(1);
    relay.Airflow(1);
    relay.Watering(1);

    // Close Device
    relay.Turn_Relays_Off();
    BOOST_CHECK_MESSAGE( relay.m_heaterGPIOState == RELAY_OFF,  "Heating GPIO State is: " <<  relay.m_heaterGPIOState << " - Must Be 1 After Turn_Relays_Off Function Call" );
    BOOST_CHECK_MESSAGE( relay.m_lightsGPIOState == RELAY_OFF,  "Lighting GPIO State is: " <<  relay.m_lightsGPIOState << " - Must Be 1 After  Turn_Relays_Off Function Call" );
    BOOST_CHECK_MESSAGE( relay.m_fanGPIOState == RELAY_OFF,  "Airflow GPIO State is: " <<  relay.m_fanGPIOState << " - Must Be 1 After  Turn_Relays_Off Function Call" );
    BOOST_CHECK_MESSAGE( relay.m_waterPumpGPIOState == RELAY_OFF,  "Watering GPIO State is: " <<  relay.m_waterPumpGPIOState << " - Must Be 1 After  Turn_Relays_Off Function Call" );

}
BOOST_AUTO_TEST_SUITE_END()


/*// Test Camera
BOOST_AUTO_TEST_SUITE(CAMERA)
BOOST_AUTO_TEST_CASE( Camera ) {
}
BOOST_AUTO_TEST_SUITE_END()
*/

