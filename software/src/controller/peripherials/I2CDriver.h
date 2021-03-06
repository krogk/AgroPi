#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


/**
* @brief CCS811 class
* @author Kamil Rog
*
* This is class is responsilbe for handling I2C communication.
* 
*/
class I2CDriver : {

public:
	I2CDriver(void) {
		
	}


private:
	void run();

private:
	int offset;
};

#endif
