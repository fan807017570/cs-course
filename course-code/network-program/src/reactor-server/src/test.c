/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:test.c
*      Author: miracle
* crete  date:20220909/14/22
* description:
*
=========================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
typedef void  event_handle(const char *buf);

void read_event(const char *buf){
    printf("this is the read event handler:%s\n",buf);
}
typedef struct _event_data{
    event_handle *read_handler;
    event_handle *write_handler;
    char *event_buf;
}event_data;
event_data *create_instance(){
    event_data *ed = (event_data*)malloc(sizeof(event_data));
    if(ed==NULL){
        printf("locate memory failed,%s\n",strerror(errno));
            return NULL;
    }
    ed->read_handler = read_event;

    ed->write_handler = read_event;
    return ed;
}

int main(int args, char **argv){
    char *buf= "hello world";
    event_data *ed = create_instance();
    if(ed!=NULL){
        ed->read_handler("reading");
        ed->read_handler("writing");
    } 
    return 1;
}
