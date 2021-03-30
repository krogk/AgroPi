/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for SGP30 class.
*
*/

#include <stdint.h>
#include <linux/i2c-dev.h>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <elf.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "SHT31D.h"
#include "I2CDriver.h"
#include "SGP30.h"
#include <sys/ioctl.h>

#include <iostream>
#include <string>


/**
* Initialize SHT31D 
* Open file descriptor
* 
* @return None
*/
int SGP30::Initialize(I2CDriver &i2c)
{
  i2cdriv = i2c;
  // Open fd to SHT31D
  fd = i2cdriv.I2C_Setup_File(I2C_ADDRESS);
  initSensor = 1;

  uint8_t readLen = 3;
  // Get Serial Number of the device
  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SGP30_GET_SERIAL_ID, serialnum,  readLen, 10);
  //Wait 10ms
  i2cdriv.Delay(10);

  uint16_t featureset = 0;
  readLen = 2;
  // Get Feature Version Set
  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SGP30_GET_FEATURESET_VERSION, &featureset,  1, 10);

  // If feature set version do not match
  if ((featureset & 0xF0) != 0x0020)
  {
    // Error
    printf(" (featureset & 0xF0) != SGP30_FEATURESET \n");
    return -1;
  }
  i2cdriv.Delay(10);
  if (initSensor)
  {
    IAQ_Initialize();
    initSensor = 0;
    i2cdriv.Delay(15000);
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

  int rtn = i2cdriv.Plain_I2C_Write_Read(fd, command, NULL, 0);
  if (rtn != 0) {
    printf("IAQ_Initialize Error: Write Read Unsuccesful");
    return -1;
  } 

  return 0;
}


/**
* Close file descriptor
* 
* @param fd filde descriptor to close.
*
* @return Status of close operation
*/
int SGP30::Close_Device() {
  Soft_Reset();
  return close(fd);
}


/**
* Soft Reset SGP30  
*
* 
* @return Zero on success else negative error number
* 
*/
int SGP30::Soft_Reset(void) {
  uint8_t buf[1];
  int rtn = i2cdriv.Plain_I2C_Write_Read(fd, SGP30_SOFT_RESET, buf, 0);
  if (rtn != 0) {
    return -1;
  }
  return 0;
}

 
/**
* Take a single eCO2 & TVOC measurement
* 
* @param tvoc     Address of the tvoc variable to modify.
* @param eco2     Address of the eco2 variable to modify
* 
* @return Zero on success else negative error number
* 
*/
int SGP30::IAQ_Measure(uint16_t &tvoc, uint16_t &eCO2) {
  uint16_t buffer[2];
  uint8_t readlength = 2;
  uint8_t delay = 12;

  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SGP30_MEASURE_AIR_QUALITY, buffer, readlength, delay);
 
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
  uint16_t  raweth = 0, rawh2 = 0;
  // Read using command
  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SGP30_MEASURE_AIR_QUALITY, buffer, readlen, delay);
  // Put into passed adresses
  rawH2 = buffer[0];
  rawEthanol = buffer[1];

  return 0;
}

