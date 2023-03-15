/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:cow_tech.c
*      Author: miracle
* crete  date:20220303/21/22
* description:
*
=========================================================*/
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/types.h>
#include<wait.h>
typedef struct oper{
    char *name;
    char *company;
}Oper;

//Oper *init(const char *name,const char *company){
//    Oper *op = (struct oper *)malloc(sizeof(struct oper));
//    if(op==NULL){
//        printf("allocate for Oper error:%s\n",strerror(errno));
//        return NULL;
//    }
//    op->name = name;
//    op->company= company;
//    age->age = age;
//    return op;
//}
//int writeOper(Oper *op,const char *fname){
//   int fd =open(fname,O_CREAT|O_APPEND|O_RDWR,777); 
//   if(fd<0){
//       printf("open local file error:%s\n",strerror(errno));
//       exit(-1);
//   }
//   char buf[200];
//   char *p = buf;
//   int n_len = strlen(op->name);
//   memcpy(p,op->name,n_len);
//   p = p+n_len;
//   int c_len = strlen(op->company);
//   memcpy(p,op->company,c_len);
//   p = p+c_len;
//   int a_len = sizeof(int);
//   memcpy(p,(char*)(int*)(&op->age),a_len);
//   buf[n_len+c_len+a_len]= '\n';
//   int count=write(fd,buf,strlen(buf));
//   if(count<0){
//       printf("write file error:%s\n",strerror(errno));
//       exit(-1);
//   }
//   return 1;
//}

//void loadOper(const char *fname){
//    
//}
int saveBgd(const char *msg){
    char *fname = "content.txt";
    
    int fd =  open(fname,O_CREAT|O_APPEND|O_RDWR,777);
    if(fd<0){
        printf("open file error:%s\n",strerror()); 
    }
    int count =write(fd,msg,strlen(msg));
    if(count<0){
        printf("write msg error:%s\n",strerror(errno));
        return -1;
    }
    return count;
}
void signal_handler(int sig){
    while(waitpid(-1,0,WNOHANG)){
        return ;
    }
}
int main(int argc,char **argv){

    //Oper op = init("fananran","shopee",23); 
    signal(SIGCHLD,signal_handler);
    char *content ="who are your mather?";
    pid_t pid=fork();
    if(pid<0){
        printf("fork error:%s\n",strerror(errno));
    }else if(pid==0){
        sleep(5);
        printf("pid is :%d,msg is :%s\n",getpid(),content);
        saveBgd(content); 
    }else{
        content = "My name is fananran.";
        printf("pid is :%d,content is :%s\n",getpid(),content);
    }
}
