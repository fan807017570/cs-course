/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:exception.h
*      Author: miracle
* crete  date:20220202/28/22
* description:
*
=========================================================*/
#ifndef __EXCEPT_H__
#define __EXCEPT_H__
#include<setjmp.h>
#define T Except_T
typedef struct T {
    const char *reason;
} T;
typedef struct Except_Frame Except_frame;
struct Except_Frame{
    Except_Frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const T *exception;
};
extern Except_Frame *Except_stack;

void Except_raise(const T *e,const char *file,int line);
#define RAISE(e) Except_raise(&(e),__FILE__,__LINE__)
#endif
