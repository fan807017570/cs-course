​		

#### 1.fcntl 函数详解

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* arg */ );
// 1. 
```

|   cmd   |                           可选参数                           |     功能描述     | 返回值                    |
| :-----: | :----------------------------------------------------------: | :--------------: | ------------------------- |
| F_SETFD | close-on-exec 标志位，如果是1 ，在执行execv 系列函数返回后，就关闭在子进程中访问的文件描述符<br />如果是0，在执行execv 系列函数返回后，就不关闭在子进程中访问的文件描述符<br />0: 关闭 close-on-exec <br /><br />1:打开对应文件描述符的close-on-exec 的标志 |                  | 返回失败 -1               |
| F_GETFD |             获取文件描述符的close-on-exec 的标志             |                  | 返回close-on-exec的标志位 |
| F_SETFL |                             如果                             | 设置文件状态标志 |                           |
| F_GETFL |                                                              | 获取文件状态标志 |                           |

​	文件状态标志说明

| 文件状态标志(CMD=F_SETFL/F_GETFL) |        功能说明        | 备注                                                         |
| :-------------------------------: | :--------------------: | ------------------------------------------------------------ |
|             O_RDONLY              |        只读权限        |                                                              |
|              O_CREAT              |    如果不存在就创建    | 此时的第三个参数就是文件的访问权限控制(用户权限控制\|用户组权限控制\|其它用户权限控制)   1(001)：可执行权限 2（010）：可写权限4(100)：可读权限 7(111)：可读、科协、可执行权限 |
|             O_WRONLY              |        只写权限        |                                                              |
|              O_RDWR               |        读写权限        |                                                              |
|              O_EXEC               |       可执行权限       |                                                              |
|             O_SEARCH              |     只搜索权限打开     |                                                              |
|             O_APPEND              |         追加写         |                                                              |
|            O_NONBLOCK             |       非阻塞模式       |                                                              |
|              O_SYNC               | 等待写完成(数据和属性) |                                                              |
|              O_DSYNC              |   等待写完成(仅数据)   |                                                              |
|              O_RSYNC              |        同步读写        |                                                              |
|              O_FSYNC              |       等待写完成       |                                                              |
|              O_ASYNC              |         异步IO         |                                                              |

#### 2.信号处理

| 信号名称 | 描述                     |
| -------- | ------------------------ |
| SIGINT   | 用户输入INTR字符，ctrl+C |
| SIG      |                          |
|          |                          |
|          |                          |
|          |                          |

2. #### 操作系统缓冲区

   ```shell
   # 查看接受缓冲区
   cat /proc/sys/net/ipv4/tcp_rmem
   # 查看发送缓冲区
   cat /proc/sys/net/ipv4/tcp_rmem
   ```
   
   
   
   
   
3. #### 多进程

   - 父子进程

     ```c
     if(fork()==0){
        do_child_process();// 处理子进程
     }else{
       do_parent_process(); //处理父进程
     }
     ```

   - 僵尸进程

     如果一个子进程推出以后，内核还会保存子进程的推出状态，如果父进程不进行手动的回收，那么子进程就会变成僵尸进程。僵尸进程会挂在init进程下，会占用额外的资源。

   - 子进程的回收

     ```c
     			 pid_t wait(int *wstatus); // 如果没有结束的子进程，wait方法将阻塞。
     
            pid_t waitpid(pid_t pid, int *wstatus, int options); // 如果一个子进程的状态，没有变化，该方法就会阻塞，默认情况下是子进程的退出，不过可以通过optoins参数来修改
     
            int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
     ```

     

     一般通过注册一个信号处理函数，在子进程推出以后，再调用wait() 或者waitpid()。

4. 
  
