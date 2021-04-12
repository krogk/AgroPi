/**
* @file ControllerThread.h
* @author Kamil Rog
* @version 0.1
*
*
* 
* This header file contains the definition for server thread for 
*
* 
*/
#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "CppThread.h"
#include "Controller.h"

/**
 * @brief Server Thread class
 * @author Kamil Rog
 *
 * This is a simple class that is responsible for data handling for server and files.
 * 
 */
class ControllerThread : public CppThread {


public:
	/**
	 * Constructor that sets the offset for the thread to a given value.
	 *
	 * offset value
	 * 
	 */
	ControllerThread() {
		isRunning = true;
		samplePeriod = 250000000;
	}



private:
	void run();
	void StartListenerServer();


private:
	bool isRunning;
	int	samplePeriod;
	Controller controbj;

};

#endif
