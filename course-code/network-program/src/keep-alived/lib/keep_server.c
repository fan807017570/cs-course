/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:keep_server.c
*	  创建者: 范安然
*	创建日期:2022年02月08日
*      描述:
*
=========================================================*/
#include"./common.h"
#include "./messageObject.h"
int main(int argc,char** argv){
    if(argc != 2){
        printf("useage :tcpserver <sleepint time> "); 
    }
    int sleeptime = atoi(argv[1]);
    int listenfd;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(8090);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    size_t sock_len = sizeof(server_addr);
    int rt = bind(listenfd,(struct sockaddr *)&server_addr,sock_len);
    if(rt<0){
        printf("bind socket error:%s\n",strerror(errno));
        exit(1); 
    }
    int lrt = listen(listenfd,10);
    if(lrt<0){
        printf("listen error :%s\n",strerror(errno));
        exit(1);
    }
    int connfd;
    struct sockaddr_in cli_addr;
    socklen_t s_len =sizeof(sockaddr_in);
    connfd = accept(listenfd,(struct sockaddr *)&cli_addr,&s_len);
    if(argc <0){
        printf("accept socker error :%s\n",strerror(errno));
        exit(1); 
    }
    messageObject message;
    
    for(;;){
        int n = read(connfd,(char*)&message,sizeof(messageObject));
        if(n<0){
            printf("read error:%s\n",strerror(errno));
            exit(1);
        }else if(n==0){
            printf("client closed!") ;
            exit(1);
        } 
        printf("received %d bytes \n",n);
        printf("message type is :%d\n",ntohl(message.type));
        switch(ntohl(message.type)){
            case MSG_TYPE1:
               printf("process MSG_TYPE1 \n"); 
               break;
            case MSG_TYPE2:
               printf("process MSG_TYPE2 \n");
               break;
            case MSG_PING:{
               messageObject dong_msg;
               dong_msg.type =MSG_DONG;
               sleep(sleeptime);
               ssize_t rc =send(connfd,(char*)&dong_msg,sizeof(messageObject),0);
               if(rc<0){
                   printf("send message error:%s\n",strerror(errno));
                   exit(0);
               }
               break;
             }
            default:
               printf("unkown message type :%d\n",ntohl(message.type));
        }
        
    }
    

}
