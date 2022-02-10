/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:messageObject.h
*	  创建者: 范安然
*	创建日期:2022年01月25日
*      描述:
*
=========================================================*/
typedef struct {
    u_int32_t type;
    char data[1024];
} messageObject;

#define MSG_PING 1 
#define MSG_DONG 2
#define MSG_TYPE1 20
#define MSG_TYPE2 21

