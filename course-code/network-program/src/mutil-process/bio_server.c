/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:bio_server.c
*      Author: miracle
* crete  date:20220303/10/22
* description:
*
=========================================================*/
#include<stdio.h>
#include<sys/types.h>
#include<stddef.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<wait.h>
#include<errno.h>
#include "../common/afnet.h"

#define MAX_LINE 4096 
void child_run(int fd){
    char outbuf[MAX_LINE+1];
    while(1){
        printf("child:%d start running !",getpid());
        //read data from socket 
        int rc =read(fd,outbuf,MAX_LINE);
        if(rc<0){
            printf("read data from socket error:%s \n",strerror(errno));
            break;
        }else if(rc==0){
            printf("peer connection had closed !");
            exit(-1);
        }
        outbuf[rc]='\n';
        printf("receive content is :%s ",outbuf);
        int wc = write(fd,outbuf,strlen(outbuf));
        if(wc <0){
            printf("have write data bytes :%d\n",wc);
            break;
        }
    }
    
}
void sigchld_handler(int signal){
    while(waitpid(-1,0,WNOHANG)>0){
        return;
    }
}
int main(int argc,char **argv){
    if(argc!=2){
        printf("useage error,argument number error");
        exit(-1);
    } 
    printf("input socket port is :%s\n",argv[1]);
    int listen_fd = tcp_server_listen(argv[1]);
    signal(SIGCHLD,sigchld_handler);
    
    while(1){
        struct sockaddr_in cli_addr;
        socklen_t len = sizeof(cli_addr);
        int fd= accept(listen_fd,(struct sockaddr*)&cli_addr,&len);
        if(fd<0){
            printf("accept failed :%s\n",strerror(errno));
            exit(-1);
        }
        if(fork()==0){
            close(listen_fd); // child processor should not pay attention to the listen fd
            child_run(fd); // execute the child processor`s logic 
        }else{
            close(fd);
        }
    }
        
    
}


