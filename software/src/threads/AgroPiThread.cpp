/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for AgroPi Thread class.
*
*/
#include "AgroPiThread.h"
#include <chrono>
#include <thread>



/**
 * Run Function
 * 
 */
void AgroPiThread::run(void) {
	Controller controller;
	// Initialize sensors
	controller.Initialize();
	// Start Timer with event(sampling) occuring every 250ms
	controller.start(250000000);
	while(1){

	}
	// Stop Timer
	controller.stop();
	
}
