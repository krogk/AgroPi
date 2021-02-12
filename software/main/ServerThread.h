#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "CppThread.h"

/* ServerThread
 * 
 * Iheritance: CppThread 
 * Childs: 
 * 
 *  */
class ServerThread : public CppThread {

public:
	ServerThread(int _offset) {
		offset = _offset;
	}

private:
	void run();

private:
	int offset;
};

#endif
