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
#include "SamplerThread.h"
#include <chrono>
#include <thread>

/**
 * Run Function
 * 
 */
void SamplerThread::run(void) {
	Sampler sampler(writePipe);
	// Start Timer with event(sampling) occuring every 250ms
	sampler.start(250000000);
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "SamplerThread thread " << this_id << "\n";

	while(1){
		
	}


	// Stop Timer
	sampler.stop();
	
}
