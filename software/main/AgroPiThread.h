#ifndef AGROPI_THREAD_H
#define AGROPI_THREAD_H

#include "CppThread.h"

/* AgroPiThread
 * 
 * Iheritance: CppThread 
 * Childs: 
 * 
 *  */
class AgroPiThread : public CppThread {

public:
	AgroPiThread(int _offset) {
		offset = _offset;
	}

private:
	void run();

private:
	int offset;
};

#endif
