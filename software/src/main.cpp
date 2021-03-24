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

#include <stdio.h>
#include "ControllerThread.h"
#include <unistd.h>
#include <fcntl.h>


int main(int argc, const char* argv[] ){

	/* Initialize thread objects */ 
	ControllerThread controller;
  
	/* Run Controller Thread */ 
	controller.start();
  
	/* Join to the thread */
	controller.join();
  
	return 0;
}

