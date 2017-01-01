#include "log.h"

#include "../globals.h"
void log_update(log_t* log)
{
	log->y += 1;
	if(log->y > (ScreenHeight + LOG_HEIGHT))
		log->y = -(LOG_HEIGHT);
}
