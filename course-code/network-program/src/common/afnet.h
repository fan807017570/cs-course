/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:afnet.h
*	  创建者: 范安然
*	创建日期:2022年02月10日
*      描述:
*
=========================================================*/
#ifndef __AFNET_H_
#define __AFNET_H_
#include<sys/types.h>

int af_create_socket(int domain);

int af_sendtimout(int fd,long ms);

int af_create_tcpserver(const char* port,int backlog,char* bindaddr);

int af_reuseaddr(int fd);

int af_listen(int fd,backlog);

#endif

