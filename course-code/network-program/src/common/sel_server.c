/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:sel_server.c
*      Author: miracle
* crete  date:20220202/14/22
* description:
*
=========================================================*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdli.h>
#define MAXLINE 4096
int main(int argc,char** argv){
    int s_fd ;
    struct addrinfo ,hints,*results,rp;
    addrinfo.ai_family = AF_UNSPEC;
    addrinfo.ai_socktype = SOCK_STREAM;
    addrinfo.ai_flags = 0;
    addrinfo.ai_protocol = 0;
    char recv_line[MAXLINE],send_line[MAXLINE];
    int ret  = getaddrinfo(NULL,"8090",&hints,&results);
    if(ret<0){
        printf("getaddrinfo error :%s\n",strerror(errno));
        exit(0);
    }
    for(rp = results;rp!=NULL;rp=rp->ai_next){
       s_fd =  socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
       if(s_fd==-1){
           continue;
       }

        int bret = bind(s_fd,rp->ai_addr,rp->ai_addrlen);
        if(bret <0){
           printf("bind error :%s\n",strerror(errno));
           exit(0) ;
        }
    }
    int lrt = listen(s_fd,10);
    if(lrt<0){
        printf("listen socket error:%s\n",strerror(errno));
        exit(0);
    }
    FD_SET allreads,readmask;
    FD_ZERO(&allreads);
    FD_SET(&allreads,s_fd);
    for(;;){
       readmask = allreads; 
       int srt = select(s_fd+1,&readmask,NULL,NULL,NULL);
       if(srt<0){
            printf("select error :%s\n",strerror(errno));
            exit(0);
       } 
       if(FD_ISSET(s_fd,&readmask)){ 
           int rc = read(s_fd,recv_line,MAXLINE);
           if(rc==0){
               printf("client has closed ！\n");
           }else if(rc <0){
           
           }
       }
    }

    
}
