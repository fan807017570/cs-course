/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:epoll_server.c
*      Author: miracle
* crete  date:20220303/30/22
* description:
*
=========================================================*/
#include<sys/epoll.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include"../common/common.h"
#define MAX_EVENT 10 
#define MAX_LINE 4096
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
    
}
/***************************************** 
  This is 
*****************************************/
int main(int argc,char **argv){
    // 1. first step create socket ,bind address then listen socket
    // 2.create epoll_event  accept event and wr event 

    // 3. call epoll_wait to get the io event 

    // 4. check the event's fd if is listen socket,then doaccept

    // 5. handle read and write event 
    if(argc!=2){
        log(LOG_ERROR,"usage number of parameter is not 2");
        return -1;
    } 
    int lsn_sock ,epoll_fd;
    lsn_sock = tcp_server_listen("8090");
    struct epoll_event ev,events[MAX_EVENT];

    epoll_fd = epoll_create(1024);
    if(epoll_fd<0){
        log(LOG_ERROR,"Call epoll_create error:%s\n",strerror(errno));
        return -1;
    }
    ev.events = EPOLLIN|EPOLLOUT|EPOLLET;
    ev.data.fd= lsn_sock;
    int ret =epoll_ctl(epoll_fd,EPOLL_CTL_ADD,lsn_sock,&ev);
    if(ret<0){
        log(LOG_ERROR,"epoll add monitor events into epoll:%s\n",strerror(errno));
        exit(-1);
    }
    int i=0;
    int connfd=0;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    while(1){
        log(LOG_ERROR,"staring wait for ready");
        int readys =epoll_wait(epoll_fd,events,MAX_EVENT,-1);
        for(i=0;i<readys;i++){
            if(events[i].data.fd==lsn_sock){
                // the events.data = listen socket ,do accept 
                int conn_fd =accept(lsn_sock,(struct sockaddr*)&cli_addr,&len);  
                //add connfd to the epoll rdtree
                ev.events = EPOLLIN|EPOLLET;
                af_nonblock(conn_fd);
                ev.data.fd = conn_fd;
                ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connfd,&ev);
                if(ret<0){
                    log(LOG_ERROR,"epoll add monitor events into epoll:%s\n",strerror(errno));
                }
            }else if(events[i].events & EPOLLIN){
                loop_echo(events[i].data.fd);
            }else {
                log("other error :%s",strerror(errno));
            }

        }
        
    }
}

