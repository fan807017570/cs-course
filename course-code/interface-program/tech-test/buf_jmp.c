/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:buf_jmp.c
*      Author: miracle
* crete  date:20220202/28/22
* description:
*
=========================================================*/
#include<setjmp.h>
#include<stdio.h>
jmp_buf buf;
void save_point(){
    printf("in save_point\n");
    longjmp(buf,1);
    printf("after save point \n");
}
int tim =0;
int main(){
    if(setjmp(buf)){
        printf("back in main\n");
        tim++;
    }else{
        printf("first time through\n");
        save_point();
    }
    if(tim<3) longjmp(buf,1);
    return 0;
}
