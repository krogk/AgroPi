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
#include "Controller.h"

/**
* @brief AgroPi Thread class
* @author Kamil Rog
*
* This Class is responsible for
*/
class AgroPiThread : public CppThread {

public:
	/**
	 * Constructor that sets the offset for the thread to a given value.
	 *
	 * @param _offset offset value
	 * 
	 */
	AgroPiThread(int _offset) {
		offset = _offset;
	}

private:

	
	void run();

private:
	int offset; /*!< Thread Offset */
	Controller controller; /*!< Controller Object */
};

#endif
