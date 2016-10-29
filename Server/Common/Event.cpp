#include "Event.h"


void event_init(event_t *event)
{
#if defined _PLATFORM_WINDOWS_
	event->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
#else
	event->flag = 0;
	pthread_cond_init(&event->cond, NULL);
	pthread_mutex_init(&event->mutex, NULL);
#endif
}

void event_destroy(event_t *event)
{
#if defined _PLATFORM_WINDOWS_
	CloseHandle(event->hEvent);
#else
	pthread_cond_destroy(&event->cond);
	pthread_mutex_destroy(&event->mutex);
#endif
}

void event_set(event_t *event)
{
#if defined _PLATFORM_WINDOWS_
	SetEvent(event->hEvent);
#else
	pthread_mutex_lock(&event->mutex);
	{
		event->flag = 1;
		pthread_cond_signal(&event->cond);
	}
	pthread_mutex_unlock(&event->mutex);
#endif
}

void event_reset(event_t *event)
{
#if defined _PLATFORM_WINDOWS_
	ResetEvent(event->hEvent);
#else
	pthread_mutex_lock(&event->mutex);
	{
		event->flag = 0;
	}
	pthread_mutex_unlock(&event->mutex);
#endif
}

void event_wait(event_t *event)
{
#if defined _PLATFORM_WINDOWS_
	WaitForSingleObject(event->hEvent, INFINITE);
#else
	pthread_mutex_lock(&event->mutex);
	{
		while (!event->flag) {
			pthread_cond_wait(&event->cond, &event->mutex);
		}
	}
	pthread_mutex_unlock(&event->mutex);
#endif
}

int event_timedwait(event_t *event, int msec)
{
	int rcode;

#if defined _PLATFORM_WINDOWS_
	rcode = WaitForSingleObject(event->hEvent, msec);
#else
	int nsec;
	struct timeval now;
	struct timespec abstime;

	gettimeofday(&now, NULL);
	nsec = now.tv_usec * 1000 + (msec % 1000) * 1000000;
	abstime.tv_nsec = nsec % 1000000000;
	abstime.tv_sec = now.tv_sec + nsec / 1000000000 + msec / 1000;

	pthread_mutex_lock(&event->mutex);
	{
		rcode = pthread_cond_timedwait(&event->cond, &event->mutex, &abstime);
	}
	pthread_mutex_unlock(&event->mutex);
#endif

	return rcode;
}
