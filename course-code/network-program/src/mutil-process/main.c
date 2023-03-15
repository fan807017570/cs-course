/*===================================================
*	Copyright(c) 2022All rights reserved.
*	
* file   name:main.c
*      Author: miracle
* crete  date:20220303/24/22
* description:
*
=========================================================*/
#include"./thread_pool.h"
void *work(void *arg){
    char *msg = (char*)arg;
    log(TPOOL_INFO,"receive msg is :%s \n",msg);
    sleep(2);
}
int main(int argc,char **argv){
    thread_pool_t *pool =thread_pool_init(4,10);

    int size =100;
    
    add_job(pool,work,"my name is zzz");
    add_job(pool,work,"my name is yyy");
    add_job(pool,work,"my name is xxx");
    add_job(pool,work,"my name is 111");
    add_job(pool,work,"my name is 222");
    add_job(pool,work,"my name is 333");
    add_job(pool,work,"my name is 444");
    add_job(pool,work,"my name is 555");
    add_job(pool,work,"my name is 666");
    add_job(pool,work,"my name is 777");
    add_job(pool,work,"my name is 888");
    add_job(pool,work,"my name is 999");
    sleep(10);
    return 0;


}
