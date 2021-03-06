#### 使用GCC制作静态库和动态库

1. ##### 静态连接

   gcc  -static  xxx.c -o xxx_share   ,在连接器在连接阶段将库的内容添加到可执行文件中

   ###### 优点：

   ​	对环境的依赖较小，具有较好的兼容性

   ###### 缺点：

   - 生成的文件比较大，需要占用更多的系统资源
   - 库函数如果由更新，必须要重新编译可执行程序

   ###### 静态库的命名规则

   - 前缀

     ​	lib  必须为lib

   - 库名称

     ​    自定义

   - 后缀

     ​	.a    

   ###### gcc将源文件编译为静态库

   - 将源文件 通过预处理， 编译 ，汇编 

     ```shell
     	gcc -c xxx.c -o xxx.o
     ```

     

   - 生成静态连接库

     ```shell
     ar -rcs libtest.a add.o sub.o mul.o div.o  #  其中r更新，c创建，s建立索引
     ```

   - 使用静态库

     ```shell
     gcc test.c -o test -I./ -L./ -lcal     # -I./ 头文件的路径，-L./ 库的路径 ,-l 库名称（去掉前后缀） 
     ```

     

   ###### gcc生成动态库

   - 命名规则

     前缀 lib ，库名 ，后缀 .so   libxxx.so 为动态库

   - 预处理，编译，汇编

     ```shell
     gcc -fPIC  -c xxx.c  #-fPIC 创建和地址无关的编译程序
     ```

   - 生成动态连接库

     ```shell
     gcc -shared *.o -o libcal.so
     nm libcal.so |grep "add"  # nm 查看动态库中对应的函数
     ```

   - 使用动态连接库

     ```shell
     # export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/anranfan/projects/cs-course/course-code/network-program/src/static-lib 
     # 或者将生成的动态连接库copy到/usr/lib 或者/lib目录下，ld就可以加载到对应的动态连接库了
     #如果需要永久生效，需要将export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/anranfan/projects/cs-course/course-code/network-program/src/static-lib  写入到.bashrc文件中
     gcc test.c  -o test -I. -L. -lcal
     ```

     ​	 

   ###### 动态连接

   gcc xxx.c -o xxx_share，连接器在连接阶段仅仅建立了应用程序和动态库之间的关系，在应用程序运行时才将动态库加载的可执行程序中。

   缺点：

   - 依赖于动态库，不可以独立运行
   - 动态库版本依赖严重

   优点：

   - 在需要时才会将程序加载
   - 具有较小的应用程序体积
   - 实现进程之间的资源共享

   ###### 多个文件编译

   ```shell
   gcc -o buffer_test buffer_test.c buffer.c   
   ```

   

#### GDB调试器

##### 调试信息

##### 启动GDB

##### GDB多进程调试

##### G

##### DB多线程调试

```shell
cc thread_server.c ../common/afnet.c  -o thread_server -lpthread -g  #gcc 编译多线程程序
```

```shell
Breakpoint 2, main (argc=2, argv=0x7fffffffe1e8) at thread_server.c:61
61	        int fd = accept(srv_fd,(struct sockaddr*)&cli_addr,&len);
(gdb) n
62	        if(fd<0){
(gdb) n
67	        int ret =pthread_create(&thd,NULL,run_thread,(void*)fd);
(gdb) n
[New Thread 0x7ffff7d9a700 (LWP 39334)]
[Switching to Thread 0x7ffff7d9a700 (LWP 39334)]

Thread 2 "thread_server" hit Breakpoint 1, run_thread (arg=0x4) at thread_server.c:23
23	    pthread_detach(pthread_self());// 一个分离的线程，其他的线程，不能对其销毁或者停止操作。
(gdb) info threads
  Id   Target Id                                         Frame
  1    Thread 0x7ffff7d9b740 (LWP 39321) "thread_server" 0x00005555555555d0 in main (argc=2, argv=0x7fffffffe1e8) at thread_server.c:67
* 2    Thread 0x7ffff7d9a700 (LWP 39334) "thread_server" run_thread (arg=0x4) at thread_server.c:23
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7d9a700 (LWP 39334))]
#0  run_thread (arg=0x4) at thread_server.c:23
23	    pthread_detach(pthread_self());// 一个分离的线程，其他的线程，不能对其销毁或者停止操作。
(gdb) n
[Switching to Thread 0x7ffff7d9b740 (LWP 39321)]

Thread 1 "thread_server" hit Breakpoint 2, main (argc=2, argv=0x7fffffffe1e8) at thread_server.c:61
61	        int fd = accept(srv_fd,(struct sockaddr*)&cli_addr,&len);
(gdb) info threads
  Id   Target Id                                         Frame
* 1    Thread 0x7ffff7d9b740 (LWP 39321) "thread_server" main (argc=2, argv=0x7fffffffe1e8) at thread_server.c:61
  2    Thread 0x7ffff7d9a700 (LWP 39334) "thread_server" 0x000055555555537e in run_thread (arg=0x4) at thread_server.c:23
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7d9a700 (LWP 39334))]
#0  0x000055555555537e in run_thread (arg=0x4) at thread_server.c:23
23	    pthread_detach(pthread_self());// 一个分离的线程，其他的线程，不能对其销毁或者停止操作。
(gdb) n
24	    printf("the thread`s thread id is :%d\n",pthread_self());
(gdb) n
the thread`s thread id is :-136730880
25	    int fd = (int)arg;
(gdb) n
26	    loop_echo(fd);
(gdb) p fd
$1 = 4
(gdb) n
receive content is :helelldsafad
```



