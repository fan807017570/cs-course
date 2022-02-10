/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:client_test.c
*	  创建者: 范安然
*	创建日期:2022年01月19日
*      描述:
*
=========================================================*/
#include<sys/socket.h>
#include<sys/select.h>
#include<string.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#define MAX_LINE 4096
int main(){
   int fd = socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in server_addr;
   server_addr.sin_family =AF_INET;
   server_addr.sin_port=htons(8090);
   inet_pton(AF_INET,"10.12.196.157",&server_addr.sin_addr);

   socklen_t len = sizeof(server_addr);
   int rt1=connect(fd,(struct sockaddr*)&server_addr,len);
   if(rt1<0){
       printf("connect socket error:%s\n",strerror(errno));        
       return 0;
   }
   fd_set readmask;
   fd_set allreads;
   FD_ZERO(&allreads);
   FD_SET(0,&allreads);
   FD_SET(fd,&allreads);
   char send_line[MAX_LINE],recv_line[MAX_LINE];
   while(true){
       readmask = allreads;
       int srt = select(fd+1,&readmask,NULL,NULL,NULL);
       if(srt<0){
            printf("select error :%S\n",strerror(errno));   
       }
       if(FD_ISSET(fd,&readmask)){
            // receive data from server ,and print the receive message in stdout            
            int rc=read(fd,recv_line,MAX_LINE);
            if(rc<0){
                printf("read from socket error:%s\n",strerror(errno));
            }
            recv_line[rc]=0;

            fputs(recv_line,stdout);
            fputs("\n",stdout);
       }
      
       if(FD_ISSET(0,&readmask)){
           // input from the stdin and determine the input message if "close" or "shutdown"
            if(fgets(send_line,MAX_LINE,stdin)==NULL){
                 printf("fgets from stdin error  :%s\n",send_line);
            }
            if(strncmp(send_line,"close",5)==0){
                FD_CLR(fd,&allreads);
                if(close(fd)){
                    printf("close socket error:%s\n",strerror(errno)); 
                }
            }
            if(strncmp(send_line,"shutdown",8)==0){
                FD_CLR(fd,&allreads);
                if(shutdown(fd,1)){
                    printf("shutdown error:%s\n",strerror(errno));
                }
            }
            int slen = strlen(send_line);
            if(send_line[slen-1]=='\n'){
                send_line[slen-1]=0;
            }
            int wr_count= write(fd,send_line,strlen(send_line));
            if(wr_count<0){
                 printf("write data error :%s\n",strerror(errno));
            }
       }

   }
}
