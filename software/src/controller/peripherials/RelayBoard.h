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
#include "GPIODriver.h"

/**
* @brief Relay Board class
* @author Kamil Rog
*
* This is class is responsilbe for the Elego Relay Board.
*
*/
class RelayBoard {

public:
	RelayBoard() {
    // Change this list to enum or defines
		m_heaterGPIO = 17;
    m_lightsGPIO = 27;
    m_fanGPIO = 22;
    m_waterPumpGPIO = 23;
    m_heaterGPIOState = 1;
    m_lightsGPIOState = 1;
    m_fanGPIOState = 1;
    m_waterPumpGPIOState = 1;
	}

  ~RelayBoard(void)
  {
    //Close_Device();
  }

  int Initialize(GPIODriver &driver);
  int Lighting(int state);
  int Heating(int state);
  int Airflow(int state);
  int Watering(int state);
  int Turn_Relays_Off();
  int Close_Relay_Board();

  int GetWateringState();
  int GetAirflowState();
  int GetHeatingState();
  int GetLightingState();
  
  int m_heaterGPIOState;
  int m_lightsGPIOState;
  int m_fanGPIOState;
  int m_waterPumpGPIOState;

private:
	int m_heaterGPIO;
  int m_lightsGPIO;
  int m_fanGPIO;
  int m_waterPumpGPIO;
  GPIODriver* m_pGPIODriver = nullptr;
};

#endif
