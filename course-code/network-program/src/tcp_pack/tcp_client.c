/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:tcp_client.c
*	  创建者: 范安然
*	创建日期:2022年02月09日
*      描述:
*
=========================================================*/
#include "./message.h"
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
int main(int argc,char** argv){
    int sock_fd;
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd<0){
        printf("get socket error:%s\n",strerror(errno));
        exit(0);
    }
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family =AF_INET;
    server_addr.sin_port = htons(8090);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    int crt= connect(sock_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(crt<0){
        printf("connect the server error:%s\n",strerror(errno));
        exit(0);
    }
    struct message msg;
    int n;
    while(fgets(msg.data,sizeof(msg.data),stdin)!=NULL){
       n = strlen(msg.data);
       msg.message_length= htonl(n);
       msg.message_type=1;

       int ret = send(sock_fd,(char*)&msg,sizeof(msg),0);
       if(ret<0){
           printf("send data error:%s\n",strerror(errno));
           exit(0);
       }
    }
}

