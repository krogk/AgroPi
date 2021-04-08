/**
* @file SHT31D.h
* @author Kamil Rog
* @version 0.1
* 
* This header file contains the class for the SH31D Sensor
* 
* This is a Temperature and Humidity sensor
* Currently The sensors must be written to in order to respond.
* A Hack has been implemented to write dummy data during initalization to overcome this issue
*
*/
#ifndef SHT31D_H
#define SHT31D_H

#include "I2CDriver.h"
#include "I2CSensor.h"

// Overcome first write fail 
#define SHT31D_HACK 1


/**
* @brief SHT31D class
* @author Kamil Rog
*
* This is class is responsilbe for the SHT31D temperature and humidity sensor.
* 
* PROTOCOL - I2C
* 
* 
*/
class SHT31D : public I2CSensor {

public:
	SHT31D() {
		m_fd = 0;
		
	}

  int Initialize(I2CDriver &i2c) override;
	int Close_Device() override;
	int Reset() override;


	int Get_Temperature_Humidity(float &temperature, float &humidity);
	int Get_Status(uint16_t &returnBuffer);
	int Clear_Status(void);
	
private:

	enum { SHT31D_I2C_ADDRESS = 0x44};
	enum { SHT31D_READ_SERIALNO = 0x3780};
	enum { SHT31D_MEAS_MEDREP = 0x240B };
	enum { SHT31D_READ_STATUS = 0xF32D };
	enum { SHT31D_CLEAR_STATUS = 0x3041 };
	enum { SHT31D_SOFT_RESET = 0x30A2 }; 

	void run();
	int m_fd;

	I2CDriver *m_pI2Cdriver = nullptr;
};

#endif
