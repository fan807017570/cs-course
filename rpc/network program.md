##### 常用的系统函数

1. 字节顺序转换函数

   ```c
   #include <arpa/inet.h>
   int inet_pton(int af, const char *src, void *dst);
   // This fucntion convert the networkt address charactor string src into a network address struct in af address family .
   
   #include <arpa/inet.h>
   const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
   // This function convert the network address struct src in af address family into a character string .The resulting string is copied to buffer pointed by dst,which must be a non-null pointer .The caller sepcifies the number of the bytes available in  this buffer in the argument size.
   ```

   

2. 网络地址转化函数

   ```c
    #include <arpa/inet.h>
   
   uint32_t htonl(uint32_t hostlong);
   // the function converts the unsigend integer hostlong from host byte order to network byte order 
   
   uint16_t htons(uint16_t hostshort);
   // the function converts the unsigned integer hostshort from host byte order to network byte order 
   
   uint32_t ntohl(uint32_t netlong);
   // the function converts the unsigned integer from network byte order to  hostlong 
   
   uint16_t ntohs(uint16_t netshort);
   // the function converts the unsigned integer from network byte order to hostshort
   ```

   

3. ip地址信息存储的结构体

   ```c
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   struct sockaddr_in {
                  sa_family_t    sin_family; /* address family: AF_INET */
                  in_port_t      sin_port;   /* port in network byte order */
                  struct in_addr sin_addr;   /* internet address */
              };
   
              /* Internet address. */
              struct in_addr {
                  uint32_t       s_addr;     /* address in network byte order */
              };
   
   
   typedef uint32_t in_addr_t;
   struct in_addr {
                  in_addr_t s_addr;
              };          
   
   struct addrinfo {
                  int              ai_flags;
                  int              ai_family;
                  int              ai_socktype;
                  int              ai_protocol;
                  socklen_t        ai_addrlen;
                  struct sockaddr *ai_addr;
                  char            *ai_canonname;
                  struct addrinfo *ai_next;
              };
   ```

   

4. select的使用模型

   ```c
   #include <sys/select.h>
   #include <sys/time.h>
   #include <sys/types.h>
   #include <unistd.h>
   
   int select(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout);
   // nfds 被监听的文件描述符号中最大的+1 
   //FD_ZERO 用来将这个向量的所有元素都设置成 0；FD_SET 用来把对应套接字 fd 的元素，a[fd]设置成 1；FD_CLR 用来把对应套接字 fd 的元素，a[fd]设置成 0；FD_ISSET 对这个向量进行检测，判断出对应套接字的元素 a[fd]是 0 还是 1。
   
   void FD_CLR(int fd, fd_set *set);
   //remove  a given file descriptor from a set 
   int  FD_ISSET(int fd, fd_set *set);
   // test to see if the file descriptor is a part of the set 
   void FD_SET(int fd, fd_set *set);
   // add a given file descriptor into a set 
   void FD_ZERO(fd_set *set);    
   // clear the set 
   int shutdown(int sockfd, int how);
   // The function call 	cause all or part of a full-duplex connection on the socket associated withd sockfd to be shutdown ,if how is SHUT_RD(0),future receptions will be disallowed ,if how is SHUT_WR(1) ,future transmissions will be disallowed,if how is SHUT_RDWR(2),future receptions and transmissions will be disallowed .
   ```

   

   

5. 常用的函数

   ```c
   #include <stdlib.h>
     //the function convert the initial portion of the string pointer to by nptr to int .The behavior is same as the 
    // strtol(nptr,NULL,10) 
   int atoi(const char *nptr);  
     //the function behavior is same as atoi ,except that they convert the initial portion of the string to their return type of long or long long 
   long atol(const char *nptr);
    
   long long atoll(const char *nptr);
   
   ```

   

6. time 时间结构体

   ```c
   struct timeval{
   		long tv_sec; // 毫秒
       	long tv_usec; // 微秒
   }
   
   ```

   

7. linux下keep-alived 的设置

   - 保活时间
   - 保活时间间隔
   - 保活探测次数

8. tcp协议数据动态传输

   1. 发送窗口

      ```
      ```

      

   2. 接收窗口

      ```
      ```

      

   3. 拥塞窗口

      ```
      ```

      

   

9. linux下socket的优雅关闭 

   1. close
   2.  shutdown

10. 静态连接和动态连接

    1. 静态连接

       gcc  -static  xxx.c -o xxx_share   ,在连接器在连接阶段将库的内容添加到可执行文件中

       优点：

       ​	对环境的依赖较小，具有较好的兼容性

       缺点：

       - 生成的文件比较大，需要占用更多的系统资源
       - 库函数如果由更新，必须要重新编译可执行程序

    2. 动态连接

       gcc xxx.c -o xxx_share，连接器在连接阶段仅仅建立了应用程序和动态库之间的关系，在应用程序运行时才将动态库加载的可执行程序中。

       缺点：

       - 依赖于动态库，不可以独立运行
       - 动态库版本依赖严重

       优点：

       - 在需要时才会将程序加载
       - 具有较小的应用程序体积
       - 实现进程之间的资源共享

    3. 

11. 地址已经被使用的原因的解决方案

    - 服务端的样例代码

      ```c
      #include<sys/socket.h>
      #include<string.h>
      #include<arpa/inet.h>
      #include<signal.h>
      #include<errno.h>
      #include<sys/types.h>
      #include<stdlib.h>
      #include<strings.h>
      #include<stdio.h>
      #include<unistd.h>
      #define SERV_PORT  8090
      #define MAX_LINE 4096
      static void sig_int(int signo){
          printf("\nreceived datagrams \n");
          exit(0);
      }
      int main(int argc, char** argv){
          int fd;
          fd = socket(AF_INET,SOCK_STREAM,0);
          if(fd<0){
              printf("locate socket error:%s \n",strerror(errno));
              exit(0);
          }
          struct sockaddr_in server_addr;
          bzero(&server_addr,sizeof(server_addr));
          server_addr.sin_family = AF_INET;
          server_addr.sin_port = htons(8090);
          
      	int on = 1;
          setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)); // 设置socket为
          
          inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
          int ret = bind(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
          if(ret<0){
              printf("bind tcp address error:%s\n",strerror(errno));
              exit(0);
          }
          signal(SIGPIPE,sig_int);
          int lst = listen(fd,10);
          if(lst<0){
              printf("listen error:%s\n",strerror(errno));
              exit(0);
          }
          int connfd ;
          struct sockaddr_in cli_addr;
          socklen_t sock_len = sizeof(cli_addr);
          bzero(&cli_addr,sizeof(cli_addr));
          connfd = accept(fd,(struct sockaddr*)&cli_addr,&sock_len);
          if(connfd<0){
              printf("accept error :%s\n",strerror(errno));
              exit(0);
          }
          char message[MAX_LINE];
          for(;;){
              int rtc = read(connfd,message,MAX_LINE);
              if(rtc<0){
                  printf("read error:%s\n",strerror(errno));
                  exit(0);
              }else if(rtc==0){
              
                  printf("client has closed!");
                  exit(0);
              }
              message[rtc]=0;
              printf("received %d bytes:%s",rtc,message);
              
          }
      }
      ```

      使用telnet 客户端访问服务端，并发送消息，服务端会打印telnet发送的消息，如果在telnet 客户端crtl+] 然后输入quit 会退出,服务端也会正常推出，如果在服务端直接ctrl+c 退出，导致socket 处于time_wait的状态，所以会提示地址已经被绑定了。

    - 解决方案

      我们知道，一个 TCP 连接是通过四元组（源地址、源端口、目的地址、目的端口）来唯一确定的，如果每次 Telnet 客户端使用的本地端口都不同，就不会和已有的四元组冲突，也就不会有 TIME_WAIT 的新旧连接化身冲突的问题。事实上，即使在很小的概率下，客户端 Telnet 使用了相同的端口，从而造成了新连接和旧连接的四元组相同，在现代 Linux 操作系统下，也不会有什么大的问题，原因是现代 Linux 操作系统对此进行了一些优化。第一种优化是新连接 SYN 告知的初始序列号，一定比 TIME_WAIT 老连接的末序列号大，这样通过序列号就可以区别出新老连接。第二种优化是开启了 tcp_timestamps，使得新连接的时间戳比老连接的时间戳大，这样通过时间戳也可以区别出新老连接。在这样的优化之下，一个 TIME_WAIT 的 TCP 连接可以忽略掉旧连接，重新被新的连接所使用。

      ```c
      int on = 1;
      setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
      ```

    - tcp_tw_reuse 和 SO_REUSEADDR的区别

      tcp_tw_reuse 是内核选项，主要用在连接的发起方。TIME_WAIT 状态的连接创建时间超过 1 秒后，新的连接才可以被复用，注意，这里是连接的发起方；

      SO_REUSEADDR 是用户态的选项，SO_REUSEADDR 选项用来告诉操作系统内核，如果端口已被占用，但是 TCP 连接状态位于 TIME_WAIT ，可以重用端口。如果端口忙，而 TCP 处于其他状态，重用端口时依旧得到“Address already in use”的错误信息。注意，这里一般都是连接的服务方。

      关于tcp_tw_reuse和SO_REUSEADDR的区别，可以概括为：tcp_tw_reuse是为了缩短time_wait的时间，避免出现大量的time_wait链接而占用系统资源，解决的是accept后的问题；SO_REUSEADDR是为了解决time_wait状态带来的端口占用问题，以及支持同一个port对应多个ip，解决的是bind时的问题

12. 多路复用IO

    1. 多路复用IO解决的问题

    2. 多路复用的原理

       select 函数就是这样一种常见的 I/O 多路复用技术，我们将在后面继续讲解其他的多路复用技术。使用 select 函数，通知内核挂起进程，当一个或多个 I/O 事件发生后，控制权返还给应用程序，由应用程序进行 I/O 事件的处理。

    3. fda 

13. fdas 