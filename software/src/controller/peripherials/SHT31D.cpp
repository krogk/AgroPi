/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for SHT31D class.
*
*/

#include <stdint.h>
#include <linux/i2c-dev.h>
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
#include "utils.h"
#include <sys/ioctl.h>


/**
* Initialize SHT31D 
* Open file descriptor
* 
* @return None
*/
void SHT31D::Initialize(I2CDriver &i2c) {
  i2cdriv = i2c;
  // Open fd to SHT31D
  fd = i2cdriv.I2C_Setup_File(SHT31D_I2C_ADDRESS);

// Do an initial read & write of no data as the first command issued failes.
#ifdef SHT31D_HACK
  uint8_t zeroByte = 0x00;
  write(fd, &zeroByte, 1);
  read(fd, &zeroByte, 1);
#endif
}

/**
* Close SHT31D file descriptor
* 
* @return None
*/
int SHT31D::Close_Device(int fd) {
  Soft_Reset();
  return close(fd);
}


/**
* Take a single Temperature & Humidity measurement 
*
* @param temperature  Pointer to the temperature variable to modify.
* @param humidity     Pointer to the humidity variable to modify
* 
* @return Zero on success else negative error number
* 
*/
SHT31_STATUS SHT31D::Get_Temperature_Humidity(float &temperature, float &humidity)
{
  int rtn;
  uint16_t temp, hum;
  uint16_t buffer[2]; 
  rtn =  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SHT31D_MEAS_MEDREP, buffer, 2);
  
  // If Read was not sucessfull 
  if (rtn != SHT31_OK) {
    // Return error
    return SHT31_BAD;
  }
  else {
    temp = buffer[0];
    hum = buffer[1];
    // Calculate temperature in celsius
    temperature = -45.0 + (175.0 * ((float) temp / (float) 0xFFFF));
    // Calculate humidity in %
    humidity = 100.0 * ((float) hum / (float) 0xFFFF);
  }
  
  return SHT31_OK;
}

/**
* Get SHT31D Status
*
* @param temperature  Pointer to the temperature variable to modify.
* @param humidity     Pointer to the humidity variable to modify
* 
* @return Zero on success else negative error number 
* 
*/
SHT31_STATUS SHT31D::Get_Status(uint16_t &status)
{
  uint16_t buffer[1];
  int rtn =  i2cdriv.Plain_I2C_Write_Read_CRC8(fd, SHT31D_READ_STATUS, buffer, 1);
 
  if (rtn != SHT31_OK) {
    return SHT31_BAD;
  }
  else { 
   status = buffer[0];
  }

  return SHT31_OK;
}

/**
* Clears status
* 
* @return Zero on success else negative error number 
* 
*/
SHT31_STATUS SHT31D::Clear_Status() {
  if( i2cdriv.Plain_I2C_Write_Read(fd, SHT31D_CLEAR_STATUS, NULL, 0) != 0) {
    return SHT31_BAD;
  }
  else {
    return SHT31_OK;
  }
}

/**
* Soft Reset 
*
* @return Zero on success else negative error number 
* 
*/
SHT31_STATUS SHT31D::Soft_Reset()
{
  if( i2cdriv.Plain_I2C_Write_Read(fd, SHT31D_SOFT_RESET, NULL, 0) != 0) {
    return SHT31_BAD;
  }
  else {
    return SHT31_OK;
  }
}
