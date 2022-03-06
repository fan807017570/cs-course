/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:buffer_test.c
*      Author: miracle
* crete  date:20220202/15/22
* description:
*
=========================================================*/
#include "./buffer.h"
#include "./common.h"
int main(){
    struct buffer *buf = alloc_buffer();
    buffer_append_string(buf,"hello world");    
    printf("buffer data is :%s\n",buf->data);
    buffer_append_string(buf,"who are you?");    
    printf("buffer data is :%s\n",buf->data);
}
