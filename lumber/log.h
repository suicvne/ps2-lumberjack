#ifndef _LOG_H_
#define _LOG_H_

#define LOG_HEIGHT 212

typedef struct log_t {

	float x;
	float y;

} log_t;

void log_update(log_t* log);

#endif //_LOG_H_
