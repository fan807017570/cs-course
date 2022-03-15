/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:except-client.c
*      Author: miracle
* crete  date:20220303/06/22
* description:
*
=========================================================*/
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<errno.h>

int tcp_client(const char *ip,const char *port){
    int conn_fd;
    conn_fd= socket(AF_INET,SOCK_STREAM,0);
    if(conn_fd<0){
        printf("get client socket error :%s\n",strerror(errno));
        exit(-1);
    }
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(8090);
    inet_pton(AF_INET,ip,&srv_addr.sin_addr);
    socklen_t len = sizeof(srv_addr);
    int ret =connect(conn_fd,(struct sockaddr*)&srv_addr,len);
    if(ret<0){
        printf("connect to server error :%s\n",strerror(errno));
        exit(-1);
    }
    return conn_fd;
}
void sig_handler(int sig){
    printf("signal handle \n");
    exit(-1);
}
void count_send(const char *ip,const char *port){
    int sock_fd = tcp_client(ip,port);
    signal(SIGPIPE,sig_handler);

    char *msg = "network programming";

    ssize_t n_written;

    int count = 10000000;
    while(count>0){
        n_written = write(sock_fd,msg,strlen(msg));
        fprintf(stdout,"send into buffer:%ld \n",n_written);
        if(n_written<=0){
            printf("send error:%s \n",strerror(errno));
            exit(-1);
        }
        count--;
    }
}

int main(int argc,char **argv){
    if(argc!=3){
        printf("error number of input argument \n");
        exit(-1);
    }
    count_send(argv[1],argv[2]);
}
