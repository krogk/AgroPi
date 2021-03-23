/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the definition for server thread for 
*
* 
*/
#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "CppThread.h"


/**
 * Environment Data Struct Definition
 * 
 * This struct conatins all enviroment data read from sensors as well as target values
 */
 typedef struct{
  /// Alternativley use triple slash for the comments
	// Env Data
  float LightIntensity; /*!< Light Intensity of the envieronment (in Lux) */	
  float Temperature; 					/*!< Temperature of the envirnoment (in Degrees Celsius)*/
	float Humidity;     /*!< Humidity of the environment (in Percent %)*/
  float CO2; 					  /*!< Carbon Dioxide in air (in )*/
  float TVOC; 					/*!< Total Volatile Organic Compounds in air (in )*/
	float RawEthanol; 
	float RawH2; 
} EnvironmentDataContr;



/**
 * @brief Server Thread class
 * @author Kamil Rog
 *
 * This is a simple class that is responsible for data handling for server and files.
 * 
 */
class ServerThread : public CppThread {

public:
	/**
	 * Constructor that sets the offset for the thread to a given value.
	 *
	 * @param _offset  offset value
	 * 
	 */
	ServerThread(int wPipe, int rPipe) {
		writePipe = wPipe;
		ReadPipe = rPipe;
	}

private:
	void run();

private:
	int writePipe;
	int ReadPipe;
	EnvironmentDataContr envData; 				      /*!< Current and Target Enviroment Data Struct */
};

#endif
