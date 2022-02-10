/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:tcp_server.c
*	  创建者: 范安然
*	创建日期:2022年02月09日
*      描述:
*
=========================================================*/
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<stdlib.h>
#include<strings.h>
#include<stdio.h>
#include<unistd.h>
#define SERV_PORT  8090
#define MAX_LINE 4096
static void sig_int(int signo){
    printf("\nreceived datagrams \n");
    exit(0);
}
int main(int argc, char** argv){
    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0){
        printf("locate socket error:%s \n",strerror(errno));
        exit(0);
    }
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8090);

    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    int on = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = bind(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret<0){
        printf("bind tcp address error:%s\n",strerror(errno));
        exit(0);
    }
    signal(SIGPIPE,sig_int);
    int lst = listen(fd,10);
    if(lst<0){
        printf("listen error:%s\n",strerror(errno));
        exit(0);
    }
    int connfd ;
    struct sockaddr_in cli_addr;
    socklen_t sock_len = sizeof(cli_addr);
    bzero(&cli_addr,sizeof(cli_addr));
    connfd = accept(fd,(struct sockaddr*)&cli_addr,&sock_len);
    if(connfd<0){
        printf("accept error :%s\n",strerror(errno));
        exit(0);
    }
    char message[MAX_LINE];
    for(;;){
        int rtc = read(connfd,message,MAX_LINE);
        if(rtc<0){
            printf("read error:%s\n",strerror(errno));
            exit(0);
        }else if(rtc==0){
        
            printf("client has closed!");
            exit(0);
        }
        message[rtc]=0;
        printf("received %d bytes:%s",rtc,message);
        
    }
}
