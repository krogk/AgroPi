#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


void I2CDriver::initI2C()
{
}


/* Wire.h read and write protocols */
void I2CDriver::I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
    _fd = wiringPiI2CSetup(address);
    if (_fd < 0) {
        fprintf(stderr, "Error: I2CSetup failed\n");
        exit(EXIT_FAILURE);
    }
    wiringPiI2CWriteReg8(_fd, subAddress, data);
    close(_fd);
}


uint8_t I2CDriver::I2CreadByte(uint8_t address, uint8_t subAddress)
{
    _fd = wiringPiI2CSetup(address);
    if (_fd < 0) {
        fprintf(stderr, "Error: I2CSetup failed\n");
        exit(EXIT_FAILURE);
    }
    uint8_t data; // `data` will store the register data
    wiringPiI2CWrite(_fd, subAddress);
    data = wiringPiI2CRead(_fd);                // Fill Rx buffer with result
    close(_fd);
    // Return read data byte
    return data;                             
}


/* I2CreadBytes() -- Read a series of bytes, starting at a register via SPI
*	Input:
*		address = The 7-bit I2C address of the slave device.
*    	subAddress = The register to begin reading.
*     	* dest = Pointer to an array where we'll store the readings.
*    	count = Number of registers to be read.
*	Output: 
* 		No value is returned by the function, but the registers read are
*       all stored in the *dest array given.
*/
uint8_t I2CDriver::I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count)
{
    _fd = wiringPiI2CSetup(address);
    if (_fd < 0) {
        fprintf(stderr, "Error: I2C Setup\n");
        exit(EXIT_FAILURE);
    }
    wiringPiI2CWrite(_fd, subAddress);
    uint8_t temp_dest[count];
    if ((read(_fd, temp_dest, 6)) < 0) {
        //fprintf(stderr, "Error: read value\n");
        throw 999;
        return 0;
    }
    close(_fd);
    for (int i = 0; i < count; i++) {
        dest[i] = temp_dest[i];
    }
    return count;
}
