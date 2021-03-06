/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the class for the Actuator
* 
*/
#ifndef ACTUATOR_H
#define ACTUATOR_H


/**
* @brief Sht class
* @author Kamil Rog
*
* This is class is responsilbe for the SHT31D temperature and humidity sensor.
* 
* @section PROTOCOL
* 
* WATER PUMP - ANALOG - GPIO x
* HEATER     - ANALOG - GPIO x
* 
*/
class Actuator {

public:
	Actuator() {
		
	}

private:
	void run();

private:
	//WaterPump pump; /*!< Water Pump Object */
	//Heater heater; /*!< Heater Actuator Object */
};

#endif
