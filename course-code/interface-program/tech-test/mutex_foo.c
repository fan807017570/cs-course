/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:mutex_foo.c
*      Author: miracle
* crete  date:20220303/15/22
* description:
*
=========================================================*/
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

struct foo{
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
};

struct foo * foo_alloc(int id){
    struct foo *fp;
    if((fp = (struct foo*)malloc(sizeof(struct foo)))!=NULL){
        fp->f_count =1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->f_lock,NULL)!=0){
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(struct foo *fp){
    pthread_mutex_lock(&fp->f_lock);
    printf("get lock of thread %d,with f_count %d\n",pthread_self(),fp->f_count);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
    printf("release lock of thread %d,with f_count %d\n",pthread_self(),fp->f_count);
}

void foo_rel(struct foo *fp){
    pthread_mutex_lock(&fp->f_lock);
    if(--fp->f_count==0){
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }else{
        pthread_mutex_unlock(&fp->f_lock);
    }
}
void *event_handler(void *param){
    struct foo *fp = (struct foo*)param; 
    printf("[before] thread of %d with foo's f_count is :%d\n",pthread_self(),fp->f_count);
    foo_hold(fp);
    sleep(5);
    foo_rel(fp);
    printf("[after] thread of %d with foo's f_count is :%d\n",pthread_self(),fp->f_count);
}
int main(int argc ,char **argv){
    int  total = 10,i=0,j=0;
    struct foo *fp = foo_alloc(1024);
    pthread_t *ths= (pthread_t*)malloc(sizeof(pthread_t)*total);
    if(fp!=NULL){
        for(i=0;i<total;i++){
            pthread_t th;
            pthread_create(&ths[i],NULL,event_handler,(void*)fp);
        }
        int err;
        for(j=0;j<total;j++){
            err=pthread_join(ths[j],NULL);
            if(err<0){
                printf("termial the thread error:%s\n,thread id is :%d\n",strerror(errno),ths[j]);
            }
        }
    }
}
