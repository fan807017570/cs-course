/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:common.h
*      Author: miracle
* crete  date:20220202/15/22
* description:
*
=========================================================*/
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#ifndef __COMMON_H__
#define __COMMON_H__
enum log_level {
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
};
#define log(level,...) do {if(level<LOG_DEBUG){\
        flockfile(stdout); \ 
        printf("###[%p][%s-%s].%s.%d: ",(void*)pthread_self(),__DATE__,__TIME__,__func__,__LINE__);\
        printf(__VA_ARGS__);\
        putchar('\n');\
        fflush(stdout);\
        funlockfile(stdout);\
    }\
}while(0)

#endif

