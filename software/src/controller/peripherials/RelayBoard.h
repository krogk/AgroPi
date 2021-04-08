/**
* @file RelayBoard.h
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
		heaterGPIO = 0;
    fanGPIO = 0;
    waterPumpGPIO = 0;
    lightsGPIO = 0;
	}

  
  int SetGPIO();
  int ClearGPIO();

private:
	
  int Initialize();

private:
	int heaterGPIO;
  int fanGPIO;
  int waterPumpGPIO;
  int lightsGPIO;
};

#endif
