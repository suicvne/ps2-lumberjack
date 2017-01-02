#include "log.h"

#include "../globals.h"
void log_update(log_t* log)
{
	log->y += LOG_SPEED;
	if(log->y > ScreenHeight)
		log->y = -(LOG_HEIGHT) + 1;
}
