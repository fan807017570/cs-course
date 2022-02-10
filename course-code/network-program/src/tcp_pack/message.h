/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:tcp_server.h
*	  创建者: 范安然
*	创建日期:2022年02月09日
*      描述:
*
=========================================================*/
#include<stdint.h>
struct message {
    uint32_t message_length;
    uint32_t message_type;
    char data[128];
};
#define MSG_PING 1
#define MSG_PANG 2
