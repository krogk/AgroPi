/**
* @file SHT31D.cpp
* @author Kamil Rog
* @version 0.1
* 
* This file contains the functions for SHT31D class.
*
*/

#include <stdio.h>
#include "SHT31D.h"
#include "I2CDriver.h"


/**
* Initialize SHT31D 
* Open file descriptor
* 
* @return None
*/
int SHT31D::Initialize(I2CDriver &i2c)
{
  m_pI2Cdriver = &i2c;
  // Open fd to SHT31D
  m_fd = m_pI2Cdriver->I2C_Setup_File(SHT31D_I2C_ADDRESS);

  // Do an initial read & write of no data as the first command issued always failes.
  #ifdef SHT31D_HACK
    uint8_t zeroByte = 0x00;
    write(m_fd, &zeroByte, 1);
    read(m_fd, &zeroByte, 1);
  #endif
return 0;
}

/**
* Close SHT31D file descriptor
* 
* @return None
*/
int SHT31D::Close_Device()
{
  Reset();
  return close(m_fd);
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
int SHT31D::Get_Temperature_Humidity(float &temperature, float &humidity)
{
  int rtn;
  uint16_t buffer[2]; 
  rtn =  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SHT31D_MEAS_MEDREP, buffer, 2);
  
  // If Read was not sucessfull 
  if (rtn != 0)
  {
    // Return error
    return -1;
  }
  else 
  {
    // Calculate temperature in celsius
    temperature = -45.0 + (175.0 * ((float) buffer[0] / (float) 0xFFFF));
    // Calculate humidity in %
    humidity = 100.0 * ((float)  buffer[1] / (float) 0xFFFF);
  }
  
  return 0;
}

/**
* Get SHT31D Status
*
* @param status       Address of status variable to update.
* 
* @return Zero on success else negative error number 
* 
*/
int SHT31D::Get_Status(uint16_t &status)
{
  uint16_t buffer[1];
  int rtn =  m_pI2Cdriver->Plain_I2C_Write_Read_CRC8(m_fd, SHT31D_READ_STATUS, buffer, 1);
 
  if (rtn != 0)
  {
    return -1;
  }
  else
  { 
   status = buffer[0];
  }
  return 0;
}

/**
* Clears status
* 
* @return Zero on success else negative error number 
* 
*/
int SHT31D::Clear_Status()
  {
  if( m_pI2Cdriver->Plain_I2C_Write_Read(m_fd, SHT31D_CLEAR_STATUS, NULL, 0) != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

/**
* Soft Reset 
*
* @return Zero on success else negative error number 
* 
*/
int SHT31D::Reset()
{
  if( m_pI2Cdriver->Plain_I2C_Write_Read(m_fd, SHT31D_SOFT_RESET, NULL, 0) != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}
