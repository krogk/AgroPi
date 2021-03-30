/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the class for the I2C Driver
*
*/
#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "utils.h"


/**
* Return Status Enumeration
*/
typedef enum {
	I2C_OK 				  	=  0,
	I2C_IOCTL_FAILED	= -1,
	I2C_WRITE_FAILED 	= -2,
	I2C_READ_FAILED		= -3,
	I2C_CRC_FAILED		= -4, 
	I2C_FAIL					= -5
} I2C_Return;

/**
* @brief I2C Driver class
* @author Kamil Rog
*
* This is class is responsilbe for handling I2C communication.
* 
*/
class I2CDriver {

public:
	/* Setup I2C fd*/
	int I2C_Setup_File(int addres);
	int I2C_Close_File(int fd);

	/* Plain I2C Functions*/
	I2C_Return Plain_I2C_Write_Read(int fd, uint16_t command, uint8_t *buffer, uint8_t readLength, uint16_t delay=10);
	I2C_Return Plain_I2C_Write_Read_CRC8(int fd, uint16_t command, uint16_t *buffer, uint8_t readlen, uint16_t delay=10);
	//I2C_Return Plain_I2C_Write_CRC8(int fd, uint16_t *command, uint8_t writelength, uint16_t *buffer, uint8_t readlength, uint16_t delay=10);
	

	void Delay(unsigned int timeMs);


	/* SMBUS Functions*/
	int I2C_Read_Byte(int fd);
	int I2C_Read_8bitReg(int fd, int command);
	int I2C_Read_16bitReg(int fd, int command);
	int I2C_Write_Byte(int fd, int data);
	int I2C_Write_8bitReg(int fd, int command, int data);
	int I2C_Write_16bitReg(int fd, int command, int data);
	int I2C_Write_Block(int fd, int command, uint8_t length, uint8_t *buff);
	int I2C_Read_Block(int fd, int command, uint8_t *buff);
	//int I2C_Write_Read_Blocks(int fd, int command, uint8_t writeLength, uint8_t *writeBuff, uint8_t readLength, uint8_t *readBuff);
};

#endif
