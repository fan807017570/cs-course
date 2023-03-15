/*===================================================
*	Copyright(c) 2022All rights reserved.
* file   name:thread_pool.c
*      Author: miracle
* crete  date:20220303/21/22
* description
=========================================================*/
#include"./thread_pool.h"
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
/**
 *every thread wait for not empty_cond,if notified by not_empty_cond ,thread will pop the queue a task ,and send not_full_cond to add_job thread.
 * */
void *function_pool(void *arg){
    thread_pool_t *pool = (struct thread_pool*)arg;
    int m_ret ,c_ret;
    
    while(1){
        m_ret=pthread_mutex_lock(&pool->mutex);
        if(m_ret!=0){
            log(TPOOL_ERROR,"get lock error:%s",strerror(errno));
            return -1;
        }
        // task queue is not empty and thread pool is not shutdwon 
        while((pool->shutdown!=1) && (pool->cur_num==0)){
        c_ret=pthread_cond_wait(&pool->not_empty_cond,&pool->mutex);
        if(c_ret!=0){
            log(TPOOL_ERROR,"wait for the not empty condition error:%s",strerror(errno));
            return -1;
            }
        }
        // if the threadpool is shutdown ,exit the current thread
        if(pool->shutdown==1){
            int retVal=0;
            pthread_mutex_unlock(&pool->mutex);
            pthread_exit(&retVal);
        }
        // 
        pool->cur_num--;
        if(pool->cur_num<pool->task_num-1){
            pthread_cond_signal(&pool->not_full_cond);
        }
        // execute the job's task 
        task_t *task =pool-> head;
        // if the size of the task queue is 0 ,head = tail = NULL
        if(pool->cur_num ==0){
            pool->head = pool->tail = NULL;
        }else {
            pool->head = pool->head->next;
        }
        // pop from the task queue 
        // execute the job_run logic 
        (*(task->job_run))(task->arg);
        // free the executed task 
        pthread_mutex_unlock(&pool->mutex);
        free(task);
    }
}
thread_pool_t *thread_pool_init(int max_thread,int task_num){/*{{{*/
    thread_pool_t *pool = (thread_pool_t*)malloc(sizeof(struct thread_pool));
    if(pool==NULL){
        log(TPOOL_ERROR,"allocate for thread pool error:%s\n",strerror(errno));
        return NULL;
    }
    pool->max_thread_num = max_thread;
    pool->task_num = task_num;
    pool->shutdown =0 ;
    pool->cur_num =0;
    if(pthread_mutex_init(&pool->mutex,NULL)!=0){
        log(TPOOL_ERROR,"pthread mutex  init error:%s",strerror(errno));
        return NULL;
    }
    if(pthread_cond_init(&pool->empty_cond,&pool->mutex)!=0){
        log(TPOOL_ERROR,"empty conditon init error :%s",strerror(errno));
        return NULL;
    }
    if(pthread_cond_init(&pool->not_empty_cond,&pool->mutex)!=0){
        log(TPOOL_ERROR,"not empty condition init error:%s",strerror(errno));
        return NULL;
    }
    if(pthread_cond_init(&pool->not_full_cond,&pool->mutex)!=0){
        log(TPOOL_ERROR,"not full condition init error:%s",strerror(errno));
        return NULL;
    }
    // init the task queue's head 
    //task_t *task = (struct job*)malloc(sizeof(struct job));
    //if(task!=NULL){
    //    log(TPOOL_ERROR,"allocate for thread task error:%s",strerror(errno));
    //    return NULL;
    //}
    pool->head = pool->tail = NULL;
    int i =0;
    pool->works = (pthread_t *)malloc(sizeof(pthread_t)*pool->max_thread_num);
    for(i=0;i<pool->max_thread_num;i++){
        if(pthread_create(pool->works+i,NULL,function_pool,(void*)pool)!=0){
            log(TPOOL_ERROR,"create thread error:%s",strerror(errno));
        }
        log(TPOOL_INFO,"create thread success ,thread id is :%p\n",*(pool->works+i));
    }    
    return pool;
}
/*
 * thread pool add task to the task queue ,should gurantee muti thread secruty .
 * **/
void add_job(thread_pool_t *pool,void* (*run_logic)(void *arg),void *arg ){
    assert(run_logic!=NULL);
    assert(arg!=NULL);
    assert(pool!=NULL);
    if(pool!=NULL){
        // get lock 
        pthread_mutex_lock(&pool->mutex);
        // need to consider wether the queue if full ,if the queue is full ,
        // you should wait for not full condition 
        while(pool->cur_num>=pool->task_num){
            pthread_cond_wait(&pool->not_full_cond,&pool->mutex);
        }
        // if the pool is empty ,need to handle 
        task_t *task = (struct job*)malloc(sizeof(struct job));
        if(task==NULL){
            log(TPOOL_ERROR,"local memory for new task error:%s",strerror(errno));
            return -1;
        }
        task->job_run =run_logic;
        task->arg = arg;
        task->next =NULL;

        if(pool->cur_num == 0){
            pool->head = pool->tail= task;
        }else{
            // push the task into the head of the queue 
            task->next = pool->head;
            pool->head = task;
        }
        pool->cur_num++;
        pthread_cond_signal(&pool->not_empty_cond);// notify the job function
        pthread_mutex_unlock(&pool->mutex);
        // 

    }else{
        log(TPOOL_ERROR,"add task is NULL");
        exit(-1);
    }

}
/**
 *destroy the thread pool 
 * */
void thread_pool_destroy(thread_pool_t *pool){

}




