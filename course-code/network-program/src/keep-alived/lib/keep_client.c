/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:keep_client.c
*	  创建者: 范安然
*	创建日期:2022年01月25日
*      描述:
*
=========================================================*/
#include "../lib/common.h"
#include "../lib/messageObject.h"

#define MAXLINE 4096
#define KEEP_ALIVE_TIME 10 
#define KEEP_ALIVE_INTERVAL 3
#define KEEP_ALIVE_PROBETIMES 3
int main(int argc,char** argv){
    int cli_fd = socket(AF_INET,SOCK_STREAM,0);
    if(cli_fd<0){
        printf("init socket error :%s\n",strerror(errno));
        exit(0);
    }
    struct sockaddr_in cli_addr;
    bzero(&cli_addr,sizeof(cli_addr));
    cli_addr.sin_family =AF_INET;
    cli_addr.sin_port = htons(8090);
    inet_pton(AF_INET,"127.0.O.1",&cli_addr.sin_addr);
    int ret = connect(cli_fd,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
    if(ret<0){
        printf("connect server error:%s\n",strerror(errno));
        exit(0);
    }
    
  
    messageObject message;
    char recv_line[MAXLINE+1];
    fd_set readmask;
    fd_set readall;
    FD_ZERO(&readall); 
    
    struct timeval tv;

    tv.tv_sec = KEEP_ALIVE_TIME;
    tv.tv_usec =0;
    int heartbeats = 0;

    FD_SET(cli_fd,&readall);
    for(;;){
        readmask = readall;
        int rc = select(cli_fd+1,&readmask,NULL,NULL,&tv); if(rc<0){ printf("select error:%s\n",strerror(errno));
            exit(1);
        }
        if(rc==0){
            if(++heartbeats>KEEP_ALIVE_PROBETIMES){
               printf("this connection is dead :%s\n",strerror(errno));
               exit(1);
            } 
            printf("seading hearbeat #%d\n",heartbeats);
            message.type = htonl(MSG_PING);
            
            rc = send(cli_fd,(char *)&message,sizeof(message),0);
            if(rc< 0){
                printf("send failed :%s\n",strerror(errno));
                exit(0);
            }
            tv.tv_sec = KEEP_ALIVE_INTERVAL;
            continue; 
        }
        int rt = 0;
        char recv_line[MAXLINE];
        if(FD_ISSET(cli_fd,&readmask)){
            rt = read(cli_fd,recv_line,MAXLINE);
            if(rt<0){
               printf("read data error :%s\n",strerror(errno));
               exit(0); 
            }else if(rt ==0){
               printf("server terminated !"); 
                
            }
            printf("received heartbeat ,make heartbeat to 0 \n");
            heartbeats = 0;
            tv.tv_sec =KEEP_ALIVE_TIME;
        }
    }
}
