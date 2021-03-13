#include "AgroPiThread.h"
#include <chrono>
#include <thread>

/**
 * Run Function
 * 
 */
void AgroPiThread::run(void) {
	//printf("Testing Thread %d\n",offset);

	printf("Controller.run:\n");
	controller.Run();
	
}
