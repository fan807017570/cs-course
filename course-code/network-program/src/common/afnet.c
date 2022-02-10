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
int main(int argc,char** argv){
    struct addrinfo hints,rp,result;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol =0 ;
    hints.ai_next =NULL;
    hints.ai_addr=NULL;
    int s ; 
    s = getaddrinfo(NULL,argv[1],&hints,&result);
    if(s<0){
        printf("getaddrinfo error:%s\n",strerror(errno));
        exit(0);
    }
    for(rp = result;rp!=NULL;rp=rp->next){
        int fd =socket(rp->ai_family,rp->socktype,rp->protocol) ;
        if(fd==-1){
            continue;
        }
        
    }
}
