/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:tcp_server.c
*	  创建者: 范安然
*	创建日期:2022年02月09日
*      描述:
*
=========================================================*/
#include "./tcp_server.h"

/*
* 函数名称: read_msg
* 描    述: read message body through  message length 
* 参    数: fd socket descriptor ,buffer ,length of the buffer
* 返    回: return real length of from read message
*/
int read_msg(int fd,char* buf,int len){
    u_int32_t message_len;
    u_int32_t message_type;
    int rc;
    rc = readn(fd,(char*)&message_len,sizeof(u_int32_t));
    if(rc!=sizeof(u_int32_t)){
        return rc<0?-1:0;
    }
    message_len = ntohl(message_len);
    rc =readn(fd,(char*)&message_type,sizeof(u_int32_t));
    if(rc!=sizeof(u_int32_t)){
        return rc<0?-1:0;
    }
    if(message_len>len){
        return -1;
    }
    rc = readn(fd,buf,message_len);
    if(rc!=message_len){
        return rc<0?-1:0;
    }
    return rc; 
}

/*
* 函数名称:
* 描    述:
* 参    数:
* 返    回:
*/
int readn(int fd,char* buf,int len){
    ssize_t rlen ; // ssize_t 是没有符号的size_t 
    size_t rcount=len;   // size_t 是跟操作系统有关系，int在所有的操作系统都是4个字节，size_t 在32位操作系统是2个自己，在64位操作系统是4个字节
    char * cptr=buf;
    while(rcount>0){
        rlen = read(fd,cptr,len);
        if(rlen<0){
            if(errno==EINTR){// EINTR 在read时收到中断信号
                continue; 
            }else{
                return -1;
            }
        }else if(rlen ==0){
            break;
        }
        rcount-=rlen;
        cptr+=rlen;
    }
    return len - rcount;
    
}
int main(int argc,char** argv){
    int sock_fd ;
    sock_fd =socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd<0){
       printf("get socket error:%s\n",strerror(errno));
       exit(0); 
    }
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(8090);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    
    int on =1;
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    int brt = bind(sock_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(brt<0){
       printf("bind server address error:%s\n",strerror(errno));
       exit(0); 
    }

    int lrt = listen(sock_fd,10);
    if(lrt<0){
        printf("listen error:%s\n",strerror(errno));
        exit(0);
    }

    int connfd;
    struct sockaddr_in cli_addr;
    bzero(&cli_addr,sizeof(cli_addr));

    socklen_t sock_len = sizeof(cli_addr);
    connfd  =accept(sock_fd,(struct sockaddr*)&cli_addr,&sock_len);
    if(connfd<0){
        printf("accept client connect error:%s\n",strerror(errno));
        exit(0);
    }
    char buf[128];
    while(true){
        int n = read_msg(connfd,buf,sizeof(buf));
        if(n<0){
            printf("read message error:%s\n",strerror(errno));
            exit(0);
        }else if(n==0){
            printf("client have closed!");
            exit(0); 
        }
        printf("received %d bytes:%s\n",n,buf);
        buf[n]=0;
    }
}
