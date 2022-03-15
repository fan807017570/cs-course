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
int main(int argc,char **argv){
    if(argc!=3){
        printf("usage: reliable_client01");
        exit(-1);
    }
    int connfd = tcp_client(argv[1],argv[2]);
    char buf[1024];
    int len ;
    while(fgets(buf,sizeof(buf),stdin)!=NULL){
        len = strlen(buf);
        int rc = send(connfd,buf,len,0);
        if(rc<0){
            printf("write failed :%s\n",strerror(errno));
            exit(-1);
        }
        rc = read(connfd,buf,sizeof(buf));
        if(rc<0){
            printf("read data failed :%s\n",strerror(errno));
            exit(-1);
        }else if(rc==0){
            printf("peer connection has closed!");
            exit(-1);
        }else{
            fputs(buf,stdout);
        }
    } 
    exit(0);
}
