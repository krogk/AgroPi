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
#include "AgroPiThread.h"
#include "ServerThread.h"

int main(int argc, const char* argv[] ){
	/* Initialize thread objects */ 
	AgroPiThread  agroPiThread(0);
	ServerThread  serverThread(10);
  
	/* Run Agro Pi Thread */ 
	agroPiThread.start();
  
	/* Run Server Thread */
	serverThread.start();
  
	/* Join to the thread */
	agroPiThread.join();
	serverThread.join();
  
	return 0;
}

