#pragma once
#include "pthread.h"

#if defined _PLATFORM_WINDOWS_
#include <windows.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

struct event_t {
#if defined _PLATFORM_WINDOWS_
	HANDLE hEvent;
#else
	int flag;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
#endif
};

extern void event_init(event_t *event);
extern void event_destroy(event_t *event);
extern void event_set(event_t *event);
extern void event_reset(event_t *event);
extern void event_wait(event_t *event);
extern int event_timedwait(event_t *event, int msec);

#ifdef __cplusplus
}
#endif
