/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:afnet.c
*	  创建者: 范安然
*	创建日期:2022年02月10日
*      描述: 
*
=========================================================*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include"./afnet.h"
#include<netdb.h>
#include<errno.h>



/*
*method name:
*description: create socket 
*      param:
*     return:
*/
int af_create_socket(int domain,const char* port){
    struct addrinfo hints,*result,*rp;
    hints.ai_family= AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;

    int s = getaddrinfo(NULL,port,&hints,&result);
    if(s<0){
        printf("get addrinfo error:%s\n",strerror(errno));
        exit(0);
    }
    int fd=-1;
    for(rp=result;rp!=NULL;rp=rp->ai_next){
       fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
       if(fd==-1){
           continue;
       } 
       if(bind(fd,rp->ai_addr,rp->ai_addrlen)==0){
           break;
       }
    } 
    return fd;
}

int af_listen(int fd,int backlog){
    
}

int af_nonblock(int fd){
    int flag ;
    flag = fcntl(fd,F_GETFL);
    int ret = fcntl(fd,F_SETFL,flag|O_NONBLOCK);
    if(ret<0){
        log("Set socket nonblock by fcntl error:%s",strerror(errno));
        return -1;
    }
    return 1;
}

int tcp_server_listen(const char *port){
    int srv_fd;
    struct addrinfo hints;
    struct addrinfo *results,*rp;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol=0;
    hints.ai_addr= NULL;
    hints.ai_next = NULL;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo(NULL,port,&hints,&results)!=0){
        printf("get addrinfo error:%s \n",strerror(errno));
        exit(-1);
    }

    for(rp = results;rp!=NULL;rp= rp=rp->ai_next){
        srv_fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol); 
        if(srv_fd<0){
            printf("get socket error:%s\n",strerror(errno));
            continue;
        }
        int on =1;
        int sret=setsockopt(srv_fd,SOL_SOCKET,SO_REUSEADDR,&on,rp->ai_addrlen);
        if(sret<0){
            printf("set socket option error :%s\n",strerror(errno));
            close(srv_fd);
            continue;
        }
        if(bind(srv_fd,rp->ai_addr,rp->ai_addrlen)==0){
            break;
        }
        close(srv_fd);

    }
    printf("the initialized socket is :%d\n",srv_fd);
    int ret =listen(srv_fd,100);
    if(ret<0){
        printf("listen socket error:%s\n",strerror(errno));
        exit(-1);
    }
    return srv_fd;
}
//int main(int argc,char** argv){
//    struct addrinfo hints,rp,result;
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_flags = AI_PASSIVE;
//    hints.ai_protocol =0 ;
//    hints.ai_next =NULL;
//    hints.ai_addr=NULL;
//    int s ; 
//    s = getaddrinfo(NULL,argv[1],&hints,&result);
//    if(s<0){
//        printf("getaddrinfo error:%s\n",strerror(errno));
//        exit(0);
//    }
//    for(rp = result;rp!=NULL;rp=rp->next){
//        int fd =socket(rp->ai_family,rp->socktype,rp->protocol) ;
//        if(fd==-1){
//            continue;
//        }
//        
//    }
//}
