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
#include "ServerThread.h"
#include <chrono>
#include <thread>
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <fcntl.h>
#include <iostream>



void ServerThread::run(void) {
	printf("Server Thread Running\n");
	char buffer[100]; 

	
		ssize_t nReadbytes = 0;
		

	while(1) {
		// Wait for child to send a string 
    wait(NULL); 
		//read( ReadPipe, concat_str, 100); 
    //printf("Server rx string %s\n", concat_str); 
 		nReadbytes = read(ReadPipe, reinterpret_cast<void *>(&envData), sizeof(EnvironmentDataContr));
		//printf("Read: %d\n Bytes", nReadbytes);

		if ( nReadbytes > 0 ) {
			printf("\n");
			printf("Server Thread: LUX: %f\n",envData.LightIntensity);
			printf("Server Thread: Temperature: %f\n",envData.Temperature);
			printf("Server Thread: Humidity: %f\n",envData.Humidity);
			printf("Server Thread: TVOC: %d ppb\n", envData.TVOC);
			printf("Server Thread: eCO2: %d ppm\n", envData.CO2);
			printf("Server Thread: RawEthanol: %d ppb\n", envData.RawEthanol);
			printf("Server Thread: RawH2: %d ppm\n", envData.RawH2);
			std::thread::id this_id = std::this_thread::get_id();
			std::cout << "ServerThread thread " << this_id << "\n";
		}
		//else {
			//printf("Read nothing\n");
			//perror("Error was");
		//}
	}
}