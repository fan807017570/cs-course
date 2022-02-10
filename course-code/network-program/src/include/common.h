/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:common.h
*	  创建者: 范安然
*	创建日期:2022年01月17日
*      描述:
*
=========================================================*/
#include<stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<sys/time.h>
#define SERVER_PORT 8090
#define MAX_LEN 4096
#define LISTENQ 10
