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


#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

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


	typedef enum
	{
	  SHT31_OK 					= 0,
	  SHT31_CRC_CHECK_FAILED 	= 1,
	  SHT31_BAD 				= 2,
	  SHT31_READ_FAILED 		= 3, 
	  SHT31_WRITE_FAILED 		= 4
	} SHT31_Return;


#define SHT31_INTERFACE_ADDR       1
#define SHT31_DEFAULT_ADDR         0x44
#define SHT31_READ_SERIALNO        0x3780
#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06 // Doesn't work on PI
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D // Seems to work on PI but shouldn't
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10 // Seems to work on PI but shouldn't
#define SHT31_MEAS_HIGHREP         0x2400 // Doesn't work on PI
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416
#define SHT31_READSTATUS           0xF32D
#define SHT31_CLEARSTATUS          0x3041
#define SHT31_SOFTRESET            0x30A2
#define SHT31_HEATER_ENABLE        0x306D
#define SHT31_HEATER_DISABLE       0x3066

#define SHT32_DEFAULT_READ         SHT31_MEAS_MEDREP

// Tempoary measure to fix the first write fail
#define SHT31D_FIX_INITIAL_FAIL 1



class SHT31D {

public:
	SHT31D() {
		
	}
	

private:
	void run();

	int sht31_open(int i2c_address, uint8_t sht31_address);
	int sht31_close(int file);

	void delay (unsigned int howLong);
	uint8_t crc8(const uint8_t *data, int len);

	SHT31_Return writeandread(int fd, uint16_t sndword, uint8_t *buffer, int readsize);
	SHT31_Return gettempandhumidity(int file, float *temp, float *hum);
	SHT31_Return getstatus(int file, uint16_t *rtnbuf);
	//SHT31_Return getserialnum(int file, uint8_t *buf);
	SHT31_Return getserialnum(int file, uint32_t *serialNo);
	SHT31_Return clearstatus(int file);
	SHT31_Return softreset(int file);
	SHT31_Return enableheater(int file);
	SHT31_Return disableheater(int file);


private:
	
};

#endif
