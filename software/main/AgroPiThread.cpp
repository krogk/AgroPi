#include "AgroPiThread.h"
#include <chrono>
#include <thread>


void AgroPiThread::run(void) {
	//printf("Testing Thread %d\n",offset);
	for(int i=0;i<10;i++) {
		printf("AgroPiThread: %d\n",i+offset);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
