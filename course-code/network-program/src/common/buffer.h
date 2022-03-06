/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:buffer.h
*      Author: miracle
* crete  date:20220202/15/22
* description:
*
=========================================================*/
#ifndef __BUFFER_H__
#define __BUFFER_H__
#define INIT_BUFFER_SIZE 4096*4
#define READ_BATCH_SIZE 4096
struct buffer{
    char *data;
    int write_index;
    int read_index;
    int total_size;
};
struct buffer *alloc_buffer();
void *free_buffer(struct buffer* buf);
int buffer_writable_size(struct buffer *buf);
int buffer_readable_size(struct buffer *buf);
int buffer_font_spare_size(struct buffer *buf);
int buffer_append_data(struct buffer *buf,void *data,int size);
int buffer_append_char(struct buffer *buf,char data);
int buffer_append_string(struct buffer *buf,char *data);
/*append to socket */
int buffer_socket_read(struct buffer* buf,int fd);
char buffer_read_char(struct buffer* buf);
int make_room(struct buffer *buf,int size);

#endif 
