/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:server_test.c
*	  创建者: 范安然
*	创建日期:2022年01月19日
*      描述:
*
=========================================================*/
#include<sys/types.h>
#include<signal.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_LINE 4096
#define SERV_PORT 8090
#define LISTEN_QUE 20
static void sig_int(int signo){
    printf("\nreceived  datagram\n");
    exit(0);
}
static void sig_pipe(int signo){
    printf("\n received datagram\n");
    exit(0);
}
int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERV_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(server_addr);

    int ret = bind(sockfd,(struct sockaddr*)&server_addr,len);
    if(ret<0){
        printf("bind the socket error!");
        return 0;
    }

    int ret2=listen(sockfd,LISTEN_QUE);
    
    if(ret2<0){
        printf("listen the socket error!");
        return 0;
    }
    signal(SIGPIPE,SIG_IGN);
    signal(SIGINT,sig_int);
    struct sockaddr_in client_addr;
    socklen_t cli_len = sizeof(sockaddr_in);
    int acept_fd = accept(sockfd,(struct sockaddr*)&client_addr,&cli_len);
    if(acept_fd<0){
        printf("accept error");
        return 0;
    }
    printf("Have accept the socket :%d\n",acept_fd);
    while(true){
        char read_buf[MAX_LINE];
        printf("start receive data.\n");
        int read_count = read(acept_fd,read_buf,MAX_LINE);
        int count =0;
        if(read_count<0){
            printf("read from socket error");
        }else if(read_count ==0){
            printf("client have closed!");
        }
        count ++;
        printf("receive content :%s",read_buf);
        read_buf[read_count] = 0;
        sleep(10);
        char send_line [MAX_LINE] ;
        sprintf(send_line,"Hi ,%s",read_buf);
        int wt_rc = write(acept_fd,send_line,strlen(send_line));
        if(wt_rc<0){
            printf("write socket buffer error !,%s",strerror(errno));
        }
    }
    return 1;
}
