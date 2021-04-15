/**
* @file
* @author Kamil Rog
* @version 0.1
* 
* This header file contains the Elego relay board class.
* 
*/
#ifndef RELAY_H
#define RELAY_H


/**
* @brief Relay Board class
* @author Kamil Rog
*
* This is class is responsilbe for the Elego Relay Board.
*
*/
class RelayBoard {

public:
	RelayBoard(void) {
    // Change this list to enum or defines
		heaterGPIO = 17;
    lightsGPIO = 27;
    fanGPIO = 22;
    waterPumpGPIO = 23;
    lightsGPIOState = 1;
    Initialize();
	}

  ~RelayBoard(void)
  {
    //CloseDevice();
  }

  int SetGPIOState(int gpioPinNumber, int value);
  int SetGPIODirection(int gpioPinNumber, int direction);
  int GPIORead(int gpioPinNumber);
  int UnexportGPIO(int gpioPinNumber);
  int ExportGPIO(int gpioPinNumber);
  int Initialize();

private:
	int SetUpPin(int gpioPinNumber);
  int UnexportPin(int gpioPinNumber); 
  
  int CloseDevice();
  
private:
	int heaterGPIO;
  int lightsGPIO;
  int lightsGPIOState;
  int fanGPIO;
  int waterPumpGPIO;

};

#endif
