/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:thread_server.c
*      Author: miracle
* crete  date:20220303/14/22
* description:
*
=========================================================*/
#include<pthread.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<netdb.h>
#include "../common/afnet.h"
#include "./thread_pool.h"
#define MAX_LINE 4096 

void* run_thread(void *arg){/*{{{*/
// the thread main logic 
    pthread_detach(pthread_self());// 一个分离的线程，其他的线程，不能对其销毁或者停止操作。
    printf("the thread`s thread id is :%d\n",pthread_self());
    int fd = (int)arg;
    loop_echo(fd);
}/*}}}*/
void loop_echo(int fd){/*{{{*//*{{{*//*}}}*/
    char buf[MAX_LINE+1];
    while(1){
        int rc = read(fd,buf,MAX_LINE);
        if(rc<0){
            printf("read from socket error:%s\n",strerror(errno));
            break;
        }
        if(rc==0){
            printf("peer connection closed!");
            break;
        }
        printf("receive content is :%s\n",buf);
        int len = strlen(buf);
        int wrc =write(fd,buf,len);
        if(wrc<0){
            printf("write data error :%s\n",strerror(errno));
            exit(-1);
        }
    }
    
}/*}}}*/

int main(int argc,char **argv){
    if(argc!=2){
        printf("usage error,not enough command paramenter!");
        exit(-1);
    }
    int srv_fd ;
    srv_fd = tcp_server_listen(argv[1]);
    thread_pool_t *pool = thread_pool_init(10,1000);
    while(1){
        struct sockaddr_in cli_addr;
        socklen_t len = sizeof(cli_addr);
        int fd = accept(srv_fd,(struct sockaddr*)&cli_addr,&len);
        if(fd<0){
            printf("accept error :%s \n",strerror(errno));
            exit(-1);
        }
        pthread_t thd ;
        //int ret =pthread_create(&thd,NULL,run_thread,(void*)fd);
        add_job(pool,run_thread,(void*)fd);
        if(ret<0){
            printf("create thread failed:%s \n",strerror(errno));
            exit(-1);
        }
    }
    return 1;

}
