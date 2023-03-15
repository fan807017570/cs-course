/*===================================================
 *	Copyright(c) 2023All rights reserved.
 *	
 * file   name:base_struture.h
 *      Author: miracle
 * crete  date:20230202/07/23
 * description:
 *
 =========================================================*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define stdLog(...) printf(__VA_ARGS__)
#define printLog(...) fprintf(fp_log,__VA_ARGS__) 
typedef struct Node{
    char data;
    struct Node *next;
    struct Node *pre;
}Lnode;

typedef struct Link{
    Lnode *head;
    Lnode *tail;
    int size;
}Slink;
/**
 * create a empty link
 * 
 * */
Slink* newLinkInstance(const char *datas);

void addNode(Slink *link,const char data);
/*
 *method name:
 *description:
 *      param:
 *     return:
 */

void deleteNode(Slink *slink,int index);

void reverse(Slink *slink);

char* toString(Slink *link);
