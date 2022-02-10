/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:tcp_server.h
*	  创建者: 范安然
*	创建日期:2022年02月09日
*      描述:
*
=========================================================*/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include "./message.h"
int read_msg(int fd,char* buf,int len);
int readn(int fd,char* buf,int len);
