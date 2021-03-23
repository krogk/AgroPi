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
#include "SamplerThread.h"
#include "ServerThread.h"
#include <unistd.h>
#include <fcntl.h>


int main(int argc, const char* argv[] ){

	// Pipes between sampler and controller threads [0] is read and [1] is write end
	int samplerFileDescriptors[2];
	// Pipes between controller and sampler threads [0] is read and [1] is write end
	int controllerFileDescriptors[2];

	// Create Pipe 
	if( pipe(samplerFileDescriptors)  == -1)  {
		// If unsuccessufll
		printf("Main: Error: Coulnd't Create Pipe For Sampler");
	}

	if( pipe(controllerFileDescriptors) == -1 ){
		// If unsuccessufll
		printf("Main: Error: Coulnd't Create Pipe For Controller");
	}

	// Get file descriptor flags
	int samplerFlags = fcntl(samplerFileDescriptors[0], F_GETFL, 0);
	int controllerFlags = fcntl(controllerFileDescriptors[0], F_GETFL, 0);

	// Set pipe to non-block
	//fcntl(samplerFileDescriptors[0], F_SETFL, samplerFlags | O_NONBLOCK);
	//fcntl(controllerFileDescriptors[0], F_SETFL, controllerFlags | O_NONBLOCK);

	/* Initialize thread objects */ 
	SamplerThread  samplerThread(samplerFileDescriptors[1], controllerFileDescriptors[0] );
	ServerThread  serverThread(controllerFileDescriptors[1], samplerFileDescriptors[0] );

  
	/* Run Sampler Thread */ 
	samplerThread.start();
  
	/* Run Server Thread */
	serverThread.start();
  
	/* Join to the thread */
	samplerThread.join();
	serverThread.join();
  
	return 0;
}

