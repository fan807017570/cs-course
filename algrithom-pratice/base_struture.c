/*===================================================
 *	Copyright(c) 2023All rights reserved.
 *	
 * file   name:base_struture.c
 *      Author: miracle
 * crete  date:20230202/07/23
 * description:
 *
 =========================================================*/
#include "base_struture.h"
#include <errno.h>
#include<string.h>
Slink* newLinkInstance(const char *datas){
    int size = strlen(datas);
    int ind =0;
    Slink *link = (Slink*) malloc(sizeof(struct Link));
    if(link==NULL){
        printf("allocate memory error:%s\n",strerror(errno));
        return NULL;
    }
    link->size =0;
    for(ind=0;ind<size;ind++){
        Lnode *newNode =(Lnode*)malloc(sizeof(struct Node));
        if(newNode==NULL){
            printf("allocate memory for newNode error:%s\n,strerror(errno)");
            return NULL;
        }
        newNode->next=NULL;
        newNode->data=datas[ind];
        if(link->size==0){
            link->head = link->tail=newNode;
        } 
        link->tail->next = newNode;
        link->tail = newNode;
        link->size++;
    }
    return link;
}

void addNode(Slink *link,const char data){
    if(link==NULL){
        printf("parameter is error.");
        return;
    }
    Lnode *node = (Lnode*)malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = data;
    link->tail->next = node;
    link->tail=node;
    link->size++;
}

char* toString(Slink *link){
    int ind =0;
    char *str = (char*)malloc(sizeof(char)*link->size);
    Lnode *node = link->head;
    while((ind<link->size) && node!=NULL){
        str[ind++] = node->data;
        node=node->next;
    }
    return str;
}

void reverse(Slink *link){
    if(link==NULL){
        printf("parameter is error.");
        return ;
    }
    Lnode *slow,*fast;
    fast=link->head;
    slow=NULL;
    do{
        Lnode *tmp = fast;
        fast=fast->next;
        tmp->next=slow;
        slow=tmp;
    }while(fast!=NULL);
    Lnode *tmp = link->head;
    link->head = link->tail;
    link->tail = tmp;
}
/*int main(int argc,char **argv){
    char *datas = "abcdef";
    Slink *l = newLinkInstance(datas);
    printf("link :%s\n",toString(l));
    printf("size:%d\n",l->size);
    addNode(l,'r');
    addNode(l,'m');
    printf("size:%d,link:%s\n",l->size,toString(l));
    reverse(l);
    printf("size:%d,link:%s\n",l->size,toString(l));
}*/

