#pragma once


#include <stdio.h>
#include <stdlib.h>

#include "pthread.h"
#include "semaphore.h"
#include "Common.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	BOOL flag;                                                                                     // 触发标志
	pthread_cond_t cond;                                                                           // 条件量
	pthread_mutex_t mutex;                                                                         // 互斥量
} event_t;


void event_init(event_t *event);                                                                   // 初始化
void event_destroy(event_t *event);                                                                // 销毁
void event_set(event_t *event);                                                                    // 触发
void event_reset(event_t *event);                                                                  // 重置
void event_wait(event_t *event);                                                                   // 等待
void event_timedwait(event_t *event, int sec, int nsec);                                           // 等待


#ifdef __cplusplus
}
#endif
