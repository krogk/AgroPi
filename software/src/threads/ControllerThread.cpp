/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for Server Thread class.
*
*/
#include "ControllerThread.h"
#include "Sampler.h"
#include "Controller.h"
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <fcntl.h>
#include <iostream>
#include <cstring>


void ControllerThread::run(void) 
{
	printf("Controller Thread Running\n");
	// Initialize Controller
	Controller controller;

	// Initialize Sampler
	Sampler sampler(&controller);

	// Start Sampler Timer
	sampler.start(samplePeriod);

	while(isRunning) 
	{
		sleep(1);
	}
	// Stop Sampler Timer
	sampler.stop();
	// delete
}