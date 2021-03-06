/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the definition for server thread for 
*
* 
*/
#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "CppThread.h"

/**
 * @brief Server Thread class
 * @author Kamil Rog
 *
 * This is a simple class that is responsible for data handling for server and files.
 * 
 */
class ServerThread : public CppThread {

public:
	/**
	 * Constructor that sets the offset for the thread to a given value.
	 *
	 * @param _offset  offset value
	 * 
	 */
	ServerThread(int _offset) {
		offset = _offset;
	}

private:
	void run();

private:
	int offset; /*!< Thread Offset */
};

#endif
