#include "Event.h"


//
// 初始化
//
_ServerExport void event_init(event_t *event)
{
	event->flag = FALSE;
	pthread_cond_init(&event->cond, NULL);
	pthread_mutex_init(&event->mutex, NULL);
}

//
// 销毁
//
_ServerExport void event_destroy(event_t *event)
{
	pthread_cond_destroy(&event->cond);
	pthread_mutex_destroy(&event->mutex);
}

//
// 触发
//
_ServerExport void event_set(event_t *event)
{
	pthread_mutex_lock(&event->mutex);
	{
		event->flag = TRUE;
		pthread_cond_signal(&event->cond);
	}
	pthread_mutex_unlock(&event->mutex);
}

//
// 重置
//
_ServerExport void event_reset(event_t *event)
{
	pthread_mutex_lock(&event->mutex);
	{
		event->flag = FALSE;
	}
	pthread_mutex_unlock(&event->mutex);
}

//
// 等待
//
_ServerExport void event_wait(event_t *event)
{
	pthread_mutex_lock(&event->mutex);
	{
		while (!event->flag) {
			pthread_cond_wait(&event->cond, &event->mutex);
		}
	}
	pthread_mutex_unlock(&event->mutex);
}

_ServerExport void event_timedwait(event_t *event, int sec, int nsec)
{
	pthread_mutex_lock(&event->mutex);
	{
		struct timespec to;

		to.tv_sec = time(NULL) + sec;
		to.tv_nsec = nsec;

		pthread_cond_timedwait(&event->cond, &event->mutex, &to);
	}
	pthread_mutex_unlock(&event->mutex);
}
