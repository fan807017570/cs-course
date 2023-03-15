/*===================================================
 *	Copyright(c) 2023All rights reserved.
 *	
 * file   name:merge_sort.c
 *      Author: miracle
 * crete  date:20230202/10/23
 * description:
 *
 =========================================================*/
#include "base_struture.h"
typedef int comparetor(const void *left,const void *right) ;
typedef int swap(void *input,int left,int right);

int int_compare(const void *left,const void *right){
    int leftInt = *(int*)left;/*{{{*/
    int rightInt = *(int*)right;
    if(leftInt>rightInt){
        return 1;
    } 
    if(leftInt == rightInt){
        return 0;
    }
    return -1;/*}}}*/
}

void swap_int(void *input,int first,int second){
    int *inputArray = (int*) input; /*{{{*/
    int tmp;
    tmp = inputArray[first];
    inputArray[first]=inputArray[second];
    inputArray[second]=tmp;/*}}}*/
}

void heap_sort(void *input,int size, comparetor *compare){
    int curInd=size;/*{{{*/
    if(size>1){
        while(1){
            int topInd = size/2;
            if(size%2==0){
                if(1){
                    //void *tmp =input+topInd;
                    //input[topInd]=input[curInd];
                    //input[curInd] = *tmp;
                }
            }

        }
    }
    /*}}}*/
}



void heap_insert(void *heap,void *toInsert,comparetor *com){

}
void heap_delete(){

}
void print_int_array(int *array){
    if(array==NULL){/*{{{*/
        printf("input parameter error\n");
        return ;
    }
    int size = sizeof(array)/sizeof(int);
    printf("array:%ld,%d\n",sizeof(array),size);
    int i=0;
    for(i=0;i<size;i++){
        printf(" %d",array[i]);
    }
    printf("\n");/*}}}*/
}
void heap_adjust(){
}
int main(int argc,char **argv){
    int a =3;
    int b=4;
    printf("compare :%d\n",int_compare(&a,&b));
    a =30;
    b=4;
    printf("compare :%d\n",int_compare(&a,&b));
    a =3;
    b=3;
    printf("compare :%d\n",int_compare(&a,&b));
    comparetor *com = int_compare;
    printf("compare :%d\n",com(&a,&b));
    int num[10] = {1,2,3,4,5,6,7,8,9,10};   
    void *num1 = num;
    printf("size:%ld\n",sizeof(num1));
    printf("size:%ld\n",sizeof(num));
    printf("size:%d\n",*((int*)num1+2));
    print_int_array(num);
    swap_int(num,2,5);
    print_int_array(num);

}
