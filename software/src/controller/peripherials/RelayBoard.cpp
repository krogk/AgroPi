/**
* @file RelayBoard.cpp
* @author Kamil Rog
* @version 0.1
* 
* This file contains the functions for the Relay Board class.
*
*/

#include "RelayBoard.h"
#include <stdio.h>
#include <stdlib.h>

/**
* Initializes actuation gpio pins 
* 
* @return   Zero on success else negative error number
*
*/
int RelayBoard::Initialize(GPIODriver &driver)
{
	m_pGPIODriver = &driver;

  // Set Up each pin connected to Realy board
  if (m_pGPIODriver->SetUpPin(m_heaterGPIO) != 0 )
  {
    printf("Relay Board: Error: Setting Up Heater GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetUpPin(m_lightsGPIO) != 0 )
  {
    printf("Relay Board: Error: Setting Up Ligts GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetUpPin(m_fanGPIO) != 0 )
  {
    printf("Relay Board: Error: Setting Up Fan GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetUpPin(m_waterPumpGPIO) != 0 )
  {
    printf("Relay Board: Error: Setting Up Water Pump GPIO\n");
    // return -1;
  }
  return 0; 

}


/**
* Changes the state of the lighting GPIO pin
*
* @param state        State to change the lighting GPIO pin to.
* 
* @return 						Zero on success else error number
*
*/
int RelayBoard::Lighting(int state)
{
	int ret = m_pGPIODriver->SetGPIOState(m_lightsGPIO, state);
	if( ret != 0)
	{
		printf("Relay Board: Error: Lighting GPIO state change unsuccessful!");
    return ret;
	}
  m_lightsGPIOState = state;
	return ret;
}


/**
* Wrapper for reading Lighting GPIO pin state
* 
* @return 						Value of the lighting pin, else negative error number
*/
int RelayBoard::GetLightingState()
{
	return m_pGPIODriver->GPIORead(m_lightsGPIO);
}


/**
* Changes the state of the Heating GPIO pin
*
* @param state        State to change the Heating GPIO pin to.
* 
* @return             Zero on success else error number
*
*/
int RelayBoard::Heating(int state)
{
	int ret = m_pGPIODriver->SetGPIOState(m_heaterGPIO, state);
	if( ret != 0)
	{
		printf("Relay Board: Error: Heating GPIO state change unsuccessful!");
    return ret;
	}
  m_heaterGPIOState = state;
	return ret;
}


/**
* Wrapper for reading heating GPIO state
* 
* @return 						Value of the lighting pin else negative error number
*/
int RelayBoard::GetHeatingState()
{
	return m_pGPIODriver->GPIORead(m_heaterGPIO);
}


/**
* Changes the state of the Airflow GPIO pin
* 
* @return 			    Zero on success else error number
*
*/
int RelayBoard::Airflow(int state)
{
	int ret = m_pGPIODriver->SetGPIOState(m_fanGPIO, state);
	if( ret != 0)
	{
		printf("Relay Board: Error: Airflow GPIO state change unsuccessful!");
    return ret;
	}
  m_fanGPIOState = state;
	return ret;
}


/**
* Wrapper for reading airflow GPIO pin state
* 
* @return 						Value of the lighting pin else negative error number
*/
int RelayBoard::GetAirflowState()
{
	return m_pGPIODriver->GPIORead(m_fanGPIO);
}


/**
* Changes the state of the Watering GPIO pin
*
* @param state        State to change the watering GPIO pin to.
* 
* @return 						Zero on success else error number
*
*/
int RelayBoard::Watering(int state)
{
	int ret = m_pGPIODriver->SetGPIOState(m_waterPumpGPIO, state);
	if( ret != 0)
	{
		printf("Relay Board: Error: Watering GPIO state change unsuccessful!");
    return ret;
	}
  m_waterPumpGPIOState = state;
	return ret;
}

/**
* Wrapper for reading airflow GPIO pin state
* 
* @return 						Value of the lighting pin else negative error number
*/
int RelayBoard::GetWateringState()
{
	return m_pGPIODriver->GPIORead(m_waterPumpGPIO);
}


/**
* Turns each Relay off by setting the GPIO pin high
* 
* @return 	Zero on success else error number
*
*/
int RelayBoard::Turn_Relays_Off()
{
	
  // 
  if (m_pGPIODriver->SetGPIOState(m_heaterGPIO, 1) != 0 )
  {
    printf("Relay Board: Error: Setting Up Heater GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetGPIOState(m_lightsGPIO , 1) != 0 )
  {
    printf("Relay Board: Error: Setting Up Ligts GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetGPIOState(m_fanGPIO, 1) != 0 )
  {
    printf("Relay Board: Error: Setting Up Fan GPIO\n");
    // return -1;
  }
   if (m_pGPIODriver->SetGPIOState(m_waterPumpGPIO, 1) != 0 )
  {
    printf("Relay Board: Error: Setting Up Water Pump GPIO\n");
    // return -1;
  }
  return 0; 
}

