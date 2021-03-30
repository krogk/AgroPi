/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This is main entry for the program.
*
* 
*/
#include "ControllerThread.h"

int main(int argc, const char* argv[] ){

	/* Initialize thread objects */ 
	ControllerThread controllerThread;

	/* Run Controller Thread */ 
	controllerThread.start();
  
	/* Join to the thread */
	controllerThread.join();
  
	return 0;
}

