/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:buffer.c
*      Author: miracle
* crete  date:20220202/15/22
* description:
*
=========================================================*/
#include"./buffer.h"
#include"./common.h"
/*init buffer by initial size */
struct buffer *alloc_buffer(){
    struct buffer *buf =(struct buffer*)malloc(sizeof(struct buffer));
    if(buf == NULL){
        printf("allocate local memory error:%s\n",strerror(errno));
        return NULL;
    }
    buf->data =(char*) malloc(INIT_BUFFER_SIZE);
    buf->write_index =0;
    buf->read_index=0;
    buf->total_size = INIT_BUFFER_SIZE;
    return buf;
}
void *free_buffer(struct buffer * buf){
    free(buf->data);
    free(buf);
}
int buffer_writable_size(struct buffer *buf){
    return buf->total_size -buf->write_index;
}
int buffer_readable_size(struct buffer *buf){
    return buf->write_index - buf->read_index;
}
int buffer_font_spare_size(struct buffer * buf){
    return buf->read_index;
}
int make_room(struct buffer *buf,int size){
    if(buffer_writable_size(buf)>size){
        return 1;
    }
    /*
     *              read_index  write_index
     * =================|--------------|^^^^^^^^^^^^^^^^^^^|
     */
    int readable= buffer_readable_size(buf);
    if(buffer_font_spare_size(buf)+buffer_writable_size(buf)>size){
        //it's enough capacity for now data
        int i=0;
        memcpy(buf->data,buf->data+buf->read_index,readable);
        buf->read_index=0;
        buf->write_index = readable;
    }else{
        char *tmp =(char*) realloc(buf->data,buf->total_size+size);
        if(tmp==NULL){
            return -1;
        }
        buf->data = tmp;
        buf->total_size +=size;
    }
}
int buffer_append(struct buffer *buf,void *data,int size){
    if(data!=NULL){
        make_room(buf,size);
        memcpy(buf->data+buf->write_index,data,size);
        buf->write_index+=size;
        return 1;
    }
    return -1;
}
int buffer_append_string(struct buffer* buf,char *data){
    if(data!=NULL){
        int len = strlen(data);
        return buffer_append(buf,data,len);
    }
    return -1;
}

int buffer_socket_read(struct buffer *buf,int fd){
    char read_data[READ_BATCH_SIZE];
    int ret =0;
    while(1){
        int ret = read(fd,read_data,sizeof(read_data));
        if(ret<=0){
            break;
        }
        buffer_append_string(buf,read_data)
    }
    if(ret == 0){
        return 0;
    }else if(ret <0){
        if(errno== EAGAIN){
            return -1;
        }
    }   
   return 0; 
}
