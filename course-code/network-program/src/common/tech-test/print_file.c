/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:print_file.c
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
int main(int argc,char **argv){
    int fd =int(*argv[1]);
    printf("fd = %d\n",fd);
    const char *print_line = "hello linux \n";
    int ret = write(fd,print_line,strlen(print_line));
    if(ret<0){
        printf("write file error :%s\n",strerror(errno));
        exit(0);
    }
    close(fd);
    return 0;
}
