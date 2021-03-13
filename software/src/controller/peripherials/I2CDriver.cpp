/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for I2C Driver Class.
* Essentially this is a wrapper for the API provided for I2C Linux Driver.
* Conatins functions for plain I2C and SMBUS
*
* https://www.kernel.org/doc/html/latest/driver-api/i2c.
* https://www.i2c-bus.org/smbus/ 
*/

#include "I2CDriver.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
// SMBUS & I2C are written in C
extern "C" {
#include "i2c/smbus.h"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
}


/**
* Dealy Function Pausing Executaion for specified amount of time.
*
* @param timeMs  Time to wait in miliseconds.
* 
* @return none
*/
void Delay(unsigned int timeMs) {
  struct timespec sleeper, dummy ;

  sleeper.tv_sec  = (time_t)(timeMs / 1000);
  sleeper.tv_nsec = (long)(timeMs % 1000) * 1000000;

  nanosleep (&sleeper, &dummy);
}


/** 
* Open I2C File descriptor for target slave device.
*
* @param addr Address of the slave device.
* 
* @return I2C File descriptor for specified slave device.
*
* @todo: Add function to detect board revision
*/
 int I2CDriver::I2C_Setup_File(int addr) {
	int boardRevison = 0, fd = 0;
	const char *device = NULL;

  //  Wirte 
	//if((boardRevison = () < 0) {
		//printf( "I2CSetup: Unknown RPi Board Revision");
		//return -1;
	//}

	if(boardRevison == 1) {
    device = "/dev/i2c-0";
  }

  // RPI 3 and newer use /dev/i2c-1
	else {
    device = "/dev/i2c-1";
  }

  // Try to open device 
	if((fd = open(device, O_RDWR)) < 0) {
		printf("I2C Setup: Unable to open %s: %s", device, strerror(errno));
		return I2C_IOCTL_FAILED;
	}

	if(ioctl(fd, I2C_SLAVE, addr) < 0) {
		printf("I2C Setup: Unable to set %s to slave mode: %s", device, strerror(errno));
		return I2C_IOCTL_FAILED;
	}

  // If no errors occured return the file descriptor
	return fd;
}


/**
* Clode file descriptor 
*
* @param fd File descriptor of the device.
* 
* @return fd for specified slave device.
*/
 int I2CDriver::I2C_Close_File(int fd) {
  return close(fd);
}


/**
* Use Plain I2C to read n-bytes a using a 2byte command.
* Pass 0 for readLength to just write.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address.
* @param buffer   Buffer to read the data to.
* 
* @return Zero on success else error number
*
* @todo: Appopriate command bytes
*/
I2C_Return I2CDriver::Plain_I2C_Write_Read(int fd, uint16_t command, uint8_t *buffer, uint8_t readLength) {
  int ret;
  int sendLength = sizeof(command);
  uint8_t sendBuffer[sendLength];
  sendBuffer[0]=(command >> 8);
  sendBuffer[1]=(command & 0xff); 
  
  // Write Data
  ret = write(fd, sendBuffer, sizeof(sendBuffer));
  // Check if write was sucessfull by inspecting the number of bytes written
  if ( ret != sendLength ) {
    printf("I2C: ERROR sending command %d :- %s\n", ret, strerror (errno));
    return I2C_WRITE_FAILED;
  } 

  // If read length is non-zero
  if (readLength > 0) {
    // 10ms delay between write and read
    Delay(10);
    // Read data
    ret = read(fd, buffer, readLength);
    // Check if read was sucessfull by inspecting the number of bytes read
    if ( ret < readLength) {
      return I2C_READ_FAILED;
    }
  }
  // No known errors encountered 
  return I2C_OK;
}


/**
* Use SMBUS to read one byte.
*
* @param fd       File descriptor of the device.
* 
* @return         A data byte received from the device elese negative errno.
*/
int I2CDriver::I2C_Read_Byte(int fd) {
 return i2c_smbus_read_byte(fd);
}

/**
* Use SMBUS to Write a byte word and read one byte from.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address. 
* 
* @return         A data byte received from the device elese negative errno.
*/
 int I2CDriver::I2C_Read_8bitReg(int fd, int command) {
	return i2c_smbus_read_byte_data(fd, command);
}


/**
* Use SMBUS to Write a byte word and read 2 bytes.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address.
* 
* @return A 16-bit unsigned word received from the device else negative errno 
*/
 int I2CDriver::I2C_Read_16bitReg(int fd, int command) {
	return i2c_smbus_read_word_data(fd, command);
}

/**
* Use SMBUS to Write a byte word.
* 
* @param fd       File descriptor of the device.
* @param data     Data to be written.
* 
* @return         Zero on success else negative errno
*/
 int I2CDriver::I2C_Write_Byte(int fd, int data) {
	return i2c_smbus_write_byte(fd, data);
}

/**
* Use SMBUS to Write a byte word uing a command / addressing specific register.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address.
* @param data     Data to be written.
* 
* @return         Zero on success else negative errno
*/
 int I2CDriver::I2C_Write_8bitReg(int fd, int command, int data) {
	return i2c_smbus_write_byte_data(fd, command, data);
}

/**
* Use SMBUS to Write a 2-byte word using a command / addressing specific register.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address. 
* @param data     Data to be written.
* 
* @return         Zero on success else negative errno 
*/
 int I2CDriver::I2C_Write_16bitReg(int fd, int command, int data) {
	return i2c_smbus_write_word_data(fd, command, data);
}


/**
* Use SMBUS to Write n-bytes using a command / addressing specific register.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address.
* @param length   Number of bytes to be written from the data buffer.
* @param buffer   Buffer containing data to be written.
* 
* @return         Zero on success else negative errno 
*/
int I2CDriver::I2C_Write_Block(int fd, int command, uint8_t length, uint8_t *buffer) {

  return i2c_smbus_write_block_data( fd, command, length, buffer);
}


/**
* Use SMBUS to Read n-bytes using a command / addressing specific register.
*
* @param fd       File descriptor of the device.
* @param command  Command / Register to address.
* @param buffer   Buffer to read the data to.
* 
* @return The number of read bytes
*/
int I2CDriver::I2C_Read_Block(int fd, int command, uint8_t *buffer) {
  return i2c_smbus_read_block_data( fd, command, buffer);
}


/**
* Use SMBUS to 
* Pass 0 for readsize if you only want to write
*
* @param fd           File descriptor of the device.
* @param command      Command / Register to address.
* @param writeLengt   Number of bytes to write from input data buffer.
* @param writeBuff    Buffer to write the data from.
* @param readLength   Number of bytes to read to data buffer.
* @param readBuff     Buffer to read the data to.
* 
* @return 
*
* @todo: implement
*/
/*
int I2CDriver::I2C_Write_Read_Blocks(int fd, int command, uint8_t writeLength, uint8_t *writeBuff, uint8_t readLength, uint8_t *readBuff) {
  return i2c_smbus_write_block_data( fd, command, writeLength, writeBuff);
}
*/