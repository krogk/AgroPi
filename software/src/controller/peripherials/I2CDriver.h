#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


/* I2CDriver
 * 
 * Iheritance: CppThread 
 * Childs: 
 * 
 *  */
class I2CDriver : {

public:
	I2CDriver(void) {
		
	}

    void I2CDriver::I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data);
    uint8_t I2CDriver::I2CreadByte(uint8_t address, uint8_t subAddress);
    uint8_t I2CDriver::I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count)
    
private:
	void run();

private:
	int offset;
};

#endif
