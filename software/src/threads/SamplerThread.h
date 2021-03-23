/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the thread for embedded part of the AgroPi 
*
* 
*/
#ifndef AGROPI_THREAD_H
#define AGROPI_THREAD_H

#include "CppThread.h"
#include "Sampler.h"

/**
* @brief AgroPi Thread class
* @author Kamil Rog
*
* This Class is responsible for
*/
class SamplerThread : public CppThread {

public:
	/**
	* Constructor that sets the offset for the thread to a given value.
	*
	* @param writePipe Write pipe to server thread
	* @param ReadPipe  Read  pipe from server thread
	*/
	SamplerThread(int wPipe, int rPipe) {
		writePipe = wPipe;
		ReadPipe = rPipe;
	}

	int writePipe;
private:
	void run();

private:
	
	int ReadPipe;
};

#endif
