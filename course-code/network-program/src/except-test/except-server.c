/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:except-server.c
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
#include<errno.h>

#define SERV_PORT 8090

int tcp_server(const char *serv_port){
    int conn_fd=0;
    int ss_fd =0;
    struct addrinfo hints;
    struct addrinfo *results,*rp;// secondary pointer which point to addrinfo 
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = 0;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // for wildchar ip address 
    hints.ai_addr= NULL;
    hints.ai_next = NULL;
    int s = getaddrinfo(NULL,serv_port,&hints,&results);
    if(s<0){
        printf("call getaddrinfo error :%s \n",strerror(errno));
        exit(-1);
    }
    for(rp=results;rp!=NULL;rp=rp->ai_next){
        ss_fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        int on = 1;
        socklen_t len = sizeof(on);
        if(ss_fd<0){
            printf("get socket error :%s \n",strerror(errno));
            continue;
        }
        setsockopt(ss_fd,SOL_SOCKET,SO_REUSEADDR,&on,len);// set address enable reuse to avoid the time_wait
        if(bind(ss_fd,rp->ai_addr,rp->ai_addrlen)==0){
            break;
        }
    }
    if(listen(ss_fd,10)<0){
        printf("listen error:%s\n",strerror(errno));
        exit(-1);
    }
    struct sockaddr_in cli_addr;
    memset(&cli_addr,0,sizeof(cli_addr));
    
    socklen_t len = sizeof(cli_addr); 

    conn_fd = accept(ss_fd,(struct sockaddr*)&cli_addr,&len);

    if(conn_fd<0){
        printf("accept the socket error :%s\n",strerror(errno));
        exit(-1);
    }
    return conn_fd; 
}

int main(int argc,char **argv){
    int connfd ;
    char buf[1024];
    if(argc!=2){
        printf("input argument error !!\n");
        exit(-1);
    }
    connfd = tcp_server(argv[1]);
    int retc = 0;
    for(;;){
        retc = read(connfd,buf,1024);
        if(retc<0){
            printf("read error :%s\n",strerror(errno));
            exit(-1);
        }else if(retc==0){
            printf("client socket has closed :%s\n",strerror(errno));
            exit(-1);
        }
        printf("receive coontent is ：%s \n",buf);
        sleep(5);
        int write_rc  = write(connfd,buf,strlen(buf));
        printf("send bytes :%d\n",write_rc);
        if(write_rc<0){
            printf("write error:%s\n",strerror(errno));
            exit(-1);
        }
    }

}
