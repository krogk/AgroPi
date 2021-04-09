/**
* @file SGP30.cpp
* @author Kamil Rog
* @version 0.1
* 
* This file contains the functions for SGP30 class.
*
*/

#include <stdio.h>
#include "I2CDriver.h"
#include "SGP30.h"


/**
* Initialize SHT31D 
* Open file descriptor
* 
* @return None
*/
int SGP30::Initialize(I2CDriver &i2c)
{
  m_pI2Cdriver = &i2c;
  // Open fd to SHT31D
  m_fd = m_pI2Cdriver->I2C_Setup_File(I2C_ADDRESS);

  uint8_t readLen = 3;
  // Get Serial Number of the device
  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SGP30_GET_SERIAL_ID, m_serialnum,  readLen, 10);
  //Wait 10ms
  m_pI2Cdriver->Delay(10);

  uint16_t featureset = 0;
  // Get Feature Version Set
  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SGP30_GET_FEATURESET_VERSION, &featureset,  1, 10);

  // If feature set version do not match
  if ((featureset & 0xF0) != 0x0020)
  {
    // Error
    printf(" (featureset & 0xF0) != SGP30_FEATURESET \n");
    return -1;
  }
  m_pI2Cdriver->Delay(10);
  if (m_initSensor)
  {
    IAQ_Initialize();
    m_initSensor = 0;
    m_pI2Cdriver->Delay(15000);
  }
  return 0;
}


/**
* Start IAQ algorithm. Must be called in initalization stage.
*
* @return  Zero on success else negative errno 
*/ 
int SGP30::IAQ_Initialize(void) {
  uint16_t command = SGP30_INIT_AIR_QUALITY;

  int rtn = m_pI2Cdriver->Plain_I2C_Write_Read(m_fd, command, NULL, 0);
  if (rtn != 0) {
    printf("IAQ_Initialize Error: Write Read Unsuccesful");
    return -1;
  } 

  return 0;
}


/**
* Closes device 
* Firstly Resets the sensor and then closes file descriptor
*
* @return Status of close operation
*/
int SGP30::Close_Device() {
  Reset();
  return close(m_fd);
}


/**
* Soft Reset SGP30  
* 
* @return Zero on success else negative error number
* 
*/
int SGP30::Reset(void) {
  uint8_t buf[1];
  int rtn = m_pI2Cdriver->Plain_I2C_Write_Read(m_fd, SGP30_SOFT_RESET, buf, 0);
  if (rtn != 0) {
    return -1;
  }
  return 0;
}

 
/**
* Take a single eCO2 & TVOC raw measurement
* 
* @param tvoc     Address of the tvoc variable to modify.
* @param eCO2     Address of the eco2 variable to modify
* 
* @return Zero on success else negative error number
* 
*/
int SGP30::IAQ_Measure(uint16_t &tvoc, uint16_t &eCO2) {
  uint16_t buffer[2];
  uint8_t readlength = 2;
  uint8_t delay = 12;

  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SGP30_MEASURE_AIR_QUALITY, buffer, readlength, delay);

  tvoc =  buffer[1];
  eCO2 =  buffer[0];  

  return 0;
}


/**
* Take a single H2 & ethanol raw measurement.
* 
* @param rawEthanol  Address of the rawEthanol variable to modify.
* @param rawH2       Address of the rawH2 variable to modify
* 
* @return Zero on success else negative error number
*/
int SGP30::IAQ_Measure_Raw( uint16_t &rawEthanol, uint16_t &rawH2) {
  uint16_t buffer[2];
  uint8_t readlen = 2;
  uint8_t delay = 12;
  // Read using command
  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SGP30_MEASURE_AIR_QUALITY, buffer, readlen, delay);
  // Put into passed adresses
  rawH2 = buffer[0];
  rawEthanol = buffer[1];

  return 0;
}

