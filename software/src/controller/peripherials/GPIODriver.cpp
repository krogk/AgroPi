/**
* @file GPIODriver.cpp
* @author Kamil Rog
* @version 0.1
* 
* This file contains the functions for GPIO driver class.
*
*/
#include "GPIODriver.h"
#include "RelayBoard.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/mman.h>

// Define Input & Output directions
#define IN  0
#define OUT 1
// Define High & Low value states 
#define LOW  0
#define HIGH 1
/// Define B
#define GPIO_STRING_LENGTH 3 
// Define maximum length for strings in formatting operations
#define DIRECTION_STRING_MAX_LENGTH 35
#define VALUE_STRING_MAX_LENGTH 30

/**
* Export GPIO Pin 
*
* @param gpioPinNumber GPIO Pin number to export.
*
* @return Zero on success error 
*/
int GPIODriver::ExportGPIO(int gpioPinNumber)
{
	char stringBuffer[GPIO_STRING_LENGTH];
	int nBytesToWrite;
	int fd = 0;

	// Open GPIO file descriptor for export gpio.
	fd = open("/sys/class/gpio/export", O_WRONLY);
	// If file description is -1 an error occured.
	if (fd == -1) 
	{
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Failed to open export for writing!\n");
		return -1;
	}
	// Format GPIO pin number to string.
	nBytesToWrite = snprintf(stringBuffer, GPIO_STRING_LENGTH, "%d", gpioPinNumber);
	// Write string containing GPIO number
	write(fd, stringBuffer, nBytesToWrite);
	// Close export GPIO file descriptor
	close(fd);
	return 0;
}

/**
* Unexport GPIO Pin 
*
* @param gpioPinNumber GPIO Pin number to unexport.
*
* @return Zero on success error 
*/
int GPIODriver::UnexportGPIO(int gpioPinNumber)
{
	char stringBuffer[GPIO_STRING_LENGTH];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd)
	{
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Failed to open unexport for writing!\n");
		return -1;
	}

	bytes_written = snprintf(stringBuffer, GPIO_STRING_LENGTH, "%d", gpioPinNumber);
	write(fd, stringBuffer, bytes_written);
	// Close unexport GPIO file descriptor
	close(fd);
	return 0;
}

/**
* Set Direction of GPIO Pin
* Input = 0
* Output = 1 
*
* @param gpioPinNumber GPIO Pin number to export.
* @param direction Direction of the pin.
*
* @return Zero on success error 
*/
int GPIODriver::SetGPIODirection(int gpioPinNumber, int direction)
{
	// Direction string used in ternary operation to c  
	static const char directionString[]  = "in\0out";
	char sysPath[DIRECTION_STRING_MAX_LENGTH];

	// Format direction string with the GPIO pin number
	snprintf(sysPath, DIRECTION_STRING_MAX_LENGTH, "/sys/class/gpio/gpio%d/direction", gpioPinNumber);

	// Open file descriptor 
	int fd = open(sysPath, O_WRONLY);
	// Check if file descriptor opened sucessfully
	if (fd == -1)
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Set GPIO Direction: Failed to open gpio direction for writing!\n");
		return -1;
	}

	// Use ternary operator to write appropriate direction
	// First Set the start of the string then number of bytes/characters
	if (-1 == write(fd, &directionString[IN == direction ? 0 : 3], IN == direction ? 2 : 3))
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Set GPIO Direction: Failed to set direction!\n");
		return -1;
	}

	close(fd);
	return 0;
}


/**
* Get the current state of the GPIO pin.
* Input = 0
* Output = 1 
*
* @param gpioPinNumber GPIO Pin number state to read.
*
* @return State of the GPIO Pin 
*/
int GPIODriver::GPIORead(int gpioPinNumber)
{	
	// Path for opening file descriptor to GPIO value
	char sysPath[VALUE_STRING_MAX_LENGTH];
	char valueString[3];

	// Format value string with the GPIO pin number into a path
	snprintf(sysPath, VALUE_STRING_MAX_LENGTH, "/sys/class/gpio/gpio%d/value", gpioPinNumber);
	// Open file descriptor
	int fd = open(sysPath, O_RDONLY);
	// Check if file descriptor has not oppened sucessfully.
	if (fd == -1)
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: GPIO Read: Failed To Open GPIO for State Reading!\n");
		return -1;
	}
	// Read the GPIO value
	if (read(fd, valueString, 3) == -1)
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: GPIO Read: Failed To Read State!\n");
		close(fd);
		return -1;
	}
	 // Close file descriptor
	close(fd);
	// return the value of the GPIO Pin 
	return(atoi(valueString));
}


/**
* Set state of the GPIO pin.
* LOW - value  = 0
* HIGH - value = 1 
*
* @param gpioPinNumber GPIO Pin number state to read.
* @param value State to set the pin to.
*
* @return Zero on success else negative error number 
*/
 int GPIODriver::SetGPIOState(int gpioPinNumber, int value)
{
	static const char valueString[] = "01";
	char path[VALUE_STRING_MAX_LENGTH];
	int fd;

  //Format value string to write
	snprintf(path, VALUE_STRING_MAX_LENGTH, "/sys/class/gpio/gpio%d/value", gpioPinNumber);

	fd = open(path, O_WRONLY);
	// Check if file descriptor has not oppened sucessfully.
	if (-1 == fd)
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Failed to open gpio value for writing!\n");
		return(-1);
	}
	// Choose between 0 and 1 from a valueString string using ternary operator and write it 
	// Check if other than one byte has been written
	if (write(fd, &valueString[LOW == value ? 0 : 1], 1) != 1)
  {
		// An error occured, print error
		fprintf(stderr, "GPIO Driver: Failed to write value!\n");
		return -1;
	}
  // Close file descriptor 
	close(fd);
	// No errors return Sucessfully
	return 0;
}


/**
* Initialize GPIO Pins for output use.
* Export Pin
* Set Direction to output
* Set GPIO state value to high
* 
* @param gpioPinNumber GPIO pin number to set up for output use.
*
* @return Zero on success error 
*/
int GPIODriver::SetUpPin(int gpioPinNumber)
{
  int ret = 0;
	// Export Pin
  if( ExportGPIO(gpioPinNumber) != 0)
  {
		// An error occured, print error
    printf("GPIO Driver: Exporting GPIO %d Failed!\n", gpioPinNumber);
    ret = -1;
  }
	// Set Direction to output
  if( SetGPIODirection(gpioPinNumber , 1) != 0)
  {
		// An error occured, print error
    printf("GPIO Driver: Setting GPIO %d Direction Failed!\n", gpioPinNumber);
    ret = -1;
  }
	// Set GPIO state value to high
  if( SetGPIOState(gpioPinNumber, 1) != 0 )
  {
		// An error occured, print error
    printf("GPIO Driver: Setting GPIO %d State Failed!\n", gpioPinNumber);
    ret = -1;
  }

  return ret;
}


