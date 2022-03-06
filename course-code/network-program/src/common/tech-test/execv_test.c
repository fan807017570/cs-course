/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:execv_test.c
*      Author: miracle
* crete  date:20220202/17/22
* description:
*
=========================================================*/
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
int main(){
    pid_t pid ;

    int fd = open("test.txt",O_CREAT|O_APPEND|O_RDWR|O_TRUNC,777);
    if(fd<0){
        printf("open file error:%s\n",strerror(errno));
        exit(0);
    }
    char* print_line = "hello  c program !";
    int r=fcntl(fd,F_SETFD,1);
    if(r<0){
        printf("set file descriptor execv-close_flag error:%s\n",strerror(errno));
        exit(0);
    } 
    int ret ;
    ret= write(fd,print_line,strlen(print_line));
    if(ret<0){
        printf("write file string error:%s\n",strerror(errno));
        exit(0);
   }
    pid = fork();
    if(pid<0){
        printf("fork error :%s \n",strerror(errno));
        exit(0);
    }
    if(pid == 0){
        printf("fd = %d\n",fd);
        int ret = execl("./print_file","./print_file",(char*)&fd,NULL);
        //int ret = execl("./print_file","./print_file","3",NULL);
        if(ret<0){
            printf("execl error :%s\n",strerror(errno));
            exit(0);
        } 
        exit(0);
    }
    wait(NULL);
    char *parent_line = "hello c++ progam";
    ret = write(fd,parent_line,strlen(print_line));
    if(ret<0){
        printf("write file string error:%s\n",strerror(errno));
        exit(0);
    }
    close(fd);
}
