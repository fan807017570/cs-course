/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:back_word.c
*      Author: miracle
* crete  date:20220303/11/22
* description:
*
=========================================================*/
#include "base_struture.h"
#include <string.h>

/*
*method name:
*description:
*      param:
*     return:
*/
int longestPalindrom(const char *input){
   Slink *strLink = newLinkInstance(input);
   printf("input string is:%s\n",input);
   Lnode *fast ,*slow;
   Lnode *leftStart,*rightStart;
   fast= slow = strLink->head;
   int slowInd=0;
   while(fast->next!=NULL){
       slowInd++;
       if(slowInd>=strLink->size/2){
           break;
       }
       fast=fast->next->next;
       slow=slow->next;
       printf("slow:%c,fast:%c\n",slow->data,fast->data);
   }
   leftStart = strLink->head;
   rightStart = slow->next;

   int compareSize = (strLink->size /2)-1;
   int i=0;
   for(i=0;i<compareSize;i++){
       if((leftStart->data)!=(rightStart->data)){
           return 0;
       }
       leftStart=leftStart->next;
       rightStart=rightStart->next;
   }
   return 1;
}

int main(int argc,char **argv){
    printf("whether is Palindrom:%d\n",longestPalindrom("abcdedcba"));
    printf("whether is Palindrom:%d\n",longestPalindrom("aaaaaabaaaaba"));
    printf("whether is Palindrom:%d\n",longestPalindrom("aaa123321aaa"));
}

