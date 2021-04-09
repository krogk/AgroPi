/**
* @file SGP30.h
* @author Kamil Rog
* @version 0.1
* 
* This header file contains the class for SGP30 gas sensor.
* 
*/
#ifndef SGP30_H
#define SGP30_H

#include "I2CSensor.h"

/**
* @brief SGP30 class
* @author Kamil Rog
*
* This is class is responsilbe for the SGP30 gas sensor.
* 
* PROTOCOL - I2C
* 
* I2C
*/
class SGP30 : public I2CSensor {

public:
	SGP30(void) {
			m_fd = 0;
			m_initSensor = 1;
			m_serialnum[0] = 0;
			m_serialnum[1] = 0;
			m_serialnum[2] = 0;
	}

	int Initialize(I2CDriver &i2c) override;
	int Reset(void) override;
	int Close_Device(void) override;
	
	int IAQ_Measure(uint16_t &tvoc, uint16_t &eCO2);
	int IAQ_Measure_Raw( uint16_t &rawEthanol, uint16_t &rawH2);

	

private:
	int IAQ_Initialize(void);

	enum { I2C_ADDRESS = 0x58 };       ///< SGP30 I2C Addres
	enum { SGP30_FEATURESET = 0x0020} ; ///< The required set for this library
	enum { SGP30_GET_SERIAL_ID  = 0x3682} ; ///< 
	enum { SGP30_GET_FEATURESET_VERSION  = 0x202F} ; ///< 
	enum { SGP30_INIT_AIR_QUALITY  = 0x2003 };
	enum { SGP30_MEASURE_AIR_QUALITY = 0x2008 }; 
	enum { SGP30_GET_IAQ_BASELINE = 0x2015 }; 
	enum { SGP30_SET_IAQ_BASELINE = 0x201e }; 
	enum { SGP30_SET_ABSOLUTE_HUMIDITY = 0x2061 }; 
	enum { SGP30_MEASURE_TEST = 0x2032 }; 
	enum { SGP30_GET_FEATURE_SET = 0x202f }; 
	enum { SGP30_MEASURE_RAW = 0x2050 }; 
	enum { SGP30_GET_TVOC_INCEPTIVE_BASELINE = 0x20b3 }; 
	enum { SGP30_SET_TVOC_BASELINE = 0x2077 }; 
	enum { SGP30_SOFT_RESET = 0x0006};

	int m_fd;
	uint16_t m_serialnum[3]; 
	I2CDriver *m_pI2Cdriver = nullptr;
	int m_initSensor;

};

#endif
