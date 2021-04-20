/**
* @file GPIODriver.h
* @author Kamil Rog
* @version 0.1
* 
* This header file contains the class for the GPIO Driver.
* 
*/
#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

/**
* @brief GPIO Driver Class
* @author Kamil Rog
*
* This is class is responsilbe for handling GPIO Pins.
*
*/
class GPIODriver {

public:
	GPIODriver(void) {}

	int SetGPIOState(int gpioPinNumber, int value);
  int GPIORead(int gpioPinNumber);
  int SetUpPin(int gpioPinNumber);
	
private:
  int ExportGPIO(int gpioPinNumber);
  int UnexportGPIO(int gpioPinNumber); 
  int SetGPIODirection(int gpioPinNumber, int direction);
};
#endif
