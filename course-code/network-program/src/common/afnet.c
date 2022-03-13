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

}

int tcp_server_listen(const char *port){
    int srv_fd;
    struct addrinfo hints;
    struct addrinfo *results,*rp;

    if(getaddrinfo(NULL,port,&hints,&results)!=0){
        printf("get addrinfo error:%s \n",sterror(errno));
        exit(-1);
    }

    for(rp = results;rp!=NULL;rp= rp=rp->ai-next){
         
    }
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
