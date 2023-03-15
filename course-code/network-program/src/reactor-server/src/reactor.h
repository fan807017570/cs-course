/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:reactor.h
*      Author: miracle
* crete  date:20220909/13/22
* description:
*
=========================================================*/
#ifndef __REACTOR_H__ 
#define __REACTOR_H__
typedef void  processEvent();
typedef struct _reactor_loop{
    int epollFd;
    processEvent *handleRead;
    processEvent *handlerWrite;
    int rbuf_len;
    int wbuf_len;
    char[] recv_buf;
    char[] send_buf;
    int is_stop;
}reactorLoop;

typedef struct _reactor_event{
    int epoll_fd;
    reactor_event_item *event_item;
}reactorEvent;

void processEvent()
#endif
