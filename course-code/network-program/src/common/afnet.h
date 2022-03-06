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

int af_create_socket(int domain,const char* port);

int af_nonblock(int fd);

int af_connect(const char* addr,const char* port ,int block_flag);

int af_create_tcpcli(const char* addr,cont char* port,int block_flag);

int af_sendtimout(int fd,long ms);

int af_create_tcpserver(const char* port,int backlog,char* bindaddr);

int af_reuseaddr(int fd);

int af_listen(int fd,int backlog);

int readn(int fd,char* buf,long len);

int read_msg(int fd,char* buf,long len);

int read_line(int fd,char* buf,long len);
#endif

