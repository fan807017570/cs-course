/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
*  文件名称:test.c
*	  创建者: 范安然
*	创建日期:2022年02月08日
*      描述:
*
=========================================================*/
#include"add.h"
#include"sub.h"
#include"mul.h"
#include"div.h"
#include<stdio.h>
int main(){
    int x =10,y =3;
    printf("x + y = %d\n" ,add(x,y));
    printf("x - y = %d\n" ,sub(x,y));
    printf("x * y = %d\n" ,mul(x,y));
    printf("x / y = %d\n" ,div(x,y));
    printf("hello world\n");
}
