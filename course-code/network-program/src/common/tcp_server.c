/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:tcp_server.c
*      Author: miracle
* crete  date:20220202/15/22
* description:
*
=========================================================*/
#include "./tcp_server.h"
#include "./common.h"
int set_nonblocking(int fd){
}

int tcp_nonblocking_server_listen(const char *port,const char *host){
    struct addrinfo hints,*result,*rp;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSEPC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE; 
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    int s = getaddrinfo(NULL,port,&hints,&results);
    if(s!=0){
        printf("getaddrinfo error:%s\n",strerror(errno));
        return -1;
    }
    int s_fd;
    for(rp=results,rp!=NULL;rp=rp->ai_next){
       s_fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol); 
       if(s_fd<0){
           continue;
       }
       int on =1;
       int srt = setsockopt(s_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
       if(srt!=0){
           close(fd);
           continue;
       }

       if(bind(s_fd,rp->ai_addr,rp->ai_addrlen)==0){
           break;
       }
       close(s_fd);
    }
    
}
