/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:client_close.c
*	  创建者: 范安然
*	创建日期:2022年01月18日
*      描述:
*
=========================================================*/
#include "./include/common.h"
int main(int argc,char **argv){
    if(argc!=2){
        printf("useage : input parameter error");
        exit(0);
    }
    int socket_fd;
    socket_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family =AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET,argv[1],&server_addr.sin_addr);

    socklen_t server_len = sizeof(server_addr);

    int conn_rt = connect(socket_fd,(struct sockaddr*)&server_addr,server_len);
    if(conn_rt<0){
        printf("connect failed :%s",strerror(errno));
        exit(0);
    }
    printf("connect the server socket sucessfully!"); 
    char send_line[MAX_LEN],recv_line[MAX_LEN+1];
    int n;

    fd_set readmask;
    fd_set allreads;

    FD_ZERO(&allreads);
    FD_SET(0,&allreads);
    FD_SET(socket_fd,&allreads);
    while(true){
        readmask =  allreads;
        int rc = select(socket_fd+1,&readmask,NULL,NULL,NULL);
        if(rc<0){
            printf("select failed :%s",strerror(errno));
            exit(0);
        }
        if(FD_ISSET(socket_fd,&readmask)){
            n = read(socket_fd,recv_line,MAX_LEN);
            if(n<0){
                printf("read error:%s",strerror(errno));
            }else if(n==0){
                printf("server terminated \n"); 
                exit(0);
            }
            recv_line[n]=0;
            fputs(recv_line,stdout);
            fputs("\n",stdout);
        }
        if(FD_ISSET(0,&readmask)){
            if(fgets(send_line,MAX_LEN,stdin)!=NULL){
                if(strncmp(send_line,"shutdown",8)==0){
                    FD_CLR(0,&allreads);
                    if(shutdown(socket_fd,1)){
                        printf("shutdown error:%s\n",strerror(errno));
                        exit(0); 
                    }
                }else if(strncmp(send_line,"close",5)==0){
                    FD_CLR(0,&allreads);
                   if(close(socket_fd)){
                        printf("close socker error:%s\n",strerror(errno));
                   } 
                   sleep(6);
                   exit(0);
                }else{
                    int i = strlen(send_line);
                    if(send_line[i-1]=='\n'){
                        send_line[i-1]=0;
                    }
                    printf("now sending %s\n",send_line);
                    size_t rt = write(socket_fd,send_line,strlen(send_line));
                   if(rt<0){
                        printf("write failed:%s\n",strerror(errno));
                   } 
                   printf("send bytes :%d\n",rt);
                } 
            }
        }
    }
}
