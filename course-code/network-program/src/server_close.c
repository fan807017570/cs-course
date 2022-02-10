/*===================================================
*	Copyright(c) 2022All rights reser.
*	
*  文件名称:server_close.c
*	  s i创建者: 范安然
*	创建日期:2022年01月17日
*      描述:
*
=========================================================*/
#include "./include/common.h"
static int count;
static void sig_int(int signo){
    printf("\n received %d datagrams \n",count);
    exit(0);
}


void run_server(){
    int listenfd ;
    listenfd= socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in  server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family =AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    server_addr.sin_port = htons(SERVER_PORT);
    
    int rt1 = bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(rt1<0){
        printf("bind failed %s \n",strerror(errno));
    }
    int rt2 = listen(listenfd,15);
    if(rt2<0){
        printf("listen error %s",strerror(errno));
    }

    // regist a SIGINT  AND SIGPIPE 
    //signal(SIGINT,sig_int); // 
    //signal(SIGPIPE,SIG_IGN);// ignore the sigpipi singal 
    


    while(true){
        int connfd ;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(sockaddr_in);
        if(connfd =accept(listenfd,(struct sockaddr*)&client_addr,&client_len)<0){
            printf("accept error :%s",strerror(errno));
        }
        printf("have accept the client :%d",connfd); 

        char message[MAX_LEN];
        count = 0;
        int n = read(connfd,message,MAX_LEN);
        if(n<0){
            printf("read buffer error:%s",strerror(errno));
        }else if(n==0){
            printf("client closed :%s",strerror(errno));
        }    
        message[n] =0;
        printf("received %d bytes:%s \n",n,message);
        count++;

        char send_line[MAX_LEN];
        sprintf(send_line,"Hi,%s",message);

        sleep(5);

        int write_nc = send(connfd,send_line,strlen(send_line),0);
        printf("send bytes:%d",write_nc);
        if(write_nc<0){
            printf("error write:%s",strerror(errno));
        }
    
    }
}
int main(int argc,char **argv){
    run_server();
}

