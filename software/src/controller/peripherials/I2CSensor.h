#ifndef __GENERIC_I2C_SENSOR_H_
#define __GENERIC_I2C_SENSOR_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "I2CDriver.h"


/**
 * Generic Sensor Class which implements function for peripherial. 
 **/
class I2CSensor {


public:

	/**
	 * Initialize sensor
	 * Assign I2C Driver
   * Open file descriptor 
   * Initial write to sensor to set it up using appropriate driver 
 	 **/
	virtual int Initialize(I2CDriver &i2c) = 0;


	/**
	 * Resets the sensor
 	 **/
  virtual int Reset() = 0;


	/**
	 * Read Data from the sensor and 
 	 **/
  //virtual int Get_Data() = 0;


	/**
	* Reset Sensor 
	* Close File Descriptor
	**/
	virtual int Close_Device() = 0;


private:

  //m_pDriver = nullptr;
};


#endif