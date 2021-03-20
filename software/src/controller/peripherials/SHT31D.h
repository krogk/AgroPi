/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the class for the 
* 
*/
#ifndef SHT31D_H
#define SHT31D_H

#include "I2CDriver.h"

// Overcome first write fail 
#define SHT31D_HACK 1


typedef enum
{
  SHT31_OK = 0,
  SHT31_CRC_CHECK_FAILED = 1,
  SHT31_BAD = 2,
  SHT31_READ_FAILED = 3, 
  SHT31_WRITE_FAILED = 4
} SHT31_STATUS;



/**
* @brief SHT31D class
* @author Kamil Rog
*
* This is class is responsilbe for the SHT31D temperature and humidity sensor.
* 
* @section PROTOCOL
* 
* I2C
*/
class SHT31D {

public:
	SHT31D() {
		
	}

  void Initialize(I2CDriver &i2c);
	int Close_Device(int fd);

	SHT31_STATUS Get_Temperature_Humidity(float &temperature, float &humidity);
	SHT31_STATUS Get_Status(uint16_t &returnBuffer);
	SHT31_STATUS Clear_Status(void);
	SHT31_STATUS Soft_Reset(void);

private:

	enum { SHT31D_I2C_ADDRESS = 0x44};
	enum { SHT31D_READ_SERIALNO = 0x3780};
	enum { SHT31D_MEAS_MEDREP = 0x240B };
	enum { SHT31D_READ_STATUS = 0xF32D };
	enum { SHT31D_CLEAR_STATUS = 0x3041 };
	enum { SHT31D_SOFT_RESET = 0x30A2 }; 

	void run();
	int fd;

private:
	I2CDriver i2cdriv;
};

#endif
