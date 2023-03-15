/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:thread_pool.h
*      Author: miracle
* crete  date:20220303/21/22
* description:
*
=========================================================*/
#include<pthread.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
enum level{
    TPOOL_ERROR,
    TPOOL_WARN,
    TPOOL_INFO,
    TPOOL_DEBUG
};
#define log(level,...) do{if(level<TPOOL_DEBUG){\
        flockfile(stdout); \ 
        printf("###[%p][%s-%s].%s.%d: ",(void*)pthread_self(),__DATE__,__TIME__,__func__,__LINE__);\
        printf(__VA_ARGS__);\
        putchar('\n');\
        fflush(stdout);\
        funlockfile(stdout);\ 
    }\
}while(0)
typedef struct job {
    void* (*job_run)(void *);//the job handle functon pointer 
    struct job *next;
    void *arg;

}task_t;
typedef struct thread_pool{
    int max_thread_num;
    pthread_t *works; // the worker thread 
    pthread_mutex_t mutex;
    pthread_cond_t empty_cond;
    pthread_cond_t not_empty_cond;
    pthread_cond_t not_full_cond;
    struct job *head;
    struct job *tail;
    int cur_num; // current task number
    int task_num; // the max task number
    int shutdown;// whether the thread pool is shutdown
}thread_pool_t;
/**
  create thread and init the thread poll
 * */
thread_pool_t *thread_pool_init(int max_num,int task_num); 
/**
 *add the task to the queue 
 * */
void add_job(thread_pool_t *pool,void* (*run_logic)(void *arg),void *arg);
#endif
