##### TCP协议

###### 报文头

![network program-tcp-header](/home/anranfan/Downloads/network program-tcp-header.jpg)

-    6位标志位的说明

  | 标志名称 | 描述                                                         |
  | -------- | ------------------------------------------------------------ |
  | URG      | 紧急只镇是否有效                                             |
  | ACK      | 表示确认序号是否有效，携带ACK标志的位确认报文                |
  | PSH      | 提示接收端应用程序应立即从TCP接受缓冲区读走数据，为接受后续的数据腾出空间。接受端：在接受到PSH标志的TCP报文后，内核会立即将接受缓冲区的数据发送给应用程序，如果不是PSH的报文，发送到应用程序的时间是未知的 |
  | RST      | 表示要求对方重新建立连接                                     |
  | SYN      | 表示请求建立一个连接。称SYN位同步报文端                      |
  | FIN      | 表示通知对方，本方要关闭连接了。称FIN为TCP的结束报文段       |

- 

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

   当我们说 select 测试返回，某个套接字准备好可读，表示什么样的事件发生呢？第一种情况是套接字接收缓冲区有数据可以读，如果我们使用 read 函数去执行读操作，肯定不会被阻塞，而是会直接读到这部分数据。第二种情况是对方发送了 FIN，使用 read 函数执行读操作，不会被阻塞，直接返回 0。第三种情况是针对一个监听套接字而言的，有已经完成的连接建立，此时使用 accept 函数去执行不会阻塞，直接返回已经完成的连接。第四种情况是套接字有错误待处理，使用 read 函数去执行读操作，不阻塞，且返回 -1。总结成一句话就是，内核通知我们套接字有数据可以读了，使用 read 函数不会阻塞。

   第一种是套接字发送缓冲区足够大，如果我们使用套接字进行 write 操作，将不会被阻塞，直接返回。第二种是连接的写半边已经关闭，如果继续进行写操作将会产生 SIGPIPE 信号。第三种是套接字上有错误待处理，使用 write 函数去执行写操作，不阻塞，且返回 -1。总结成一句话就是，内核通知我们套接字可以往里写了，使用 write 函数就不会阻塞。

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

      close函数会对套接字的引用次数减1，一旦发现了套接字引用数到0，就会对套接字进行彻底的释放，并且会关闭TCP两个方向的数据流。

      close 如何关闭两个方向的数据流：

      在输入方向上，操作系统内核会将套接字设置为不可读，任何的读操作都会返回异常。

      在输出方向，系统系统会尝试将发送缓冲区的数据发送给对端，并最后向对端发送一个FIN报文，接下来如果再对该套接字进行写操作会返回异常。

      如果对端没有检测到套接字已经关闭，还继续发送报文，会收到一个RST的报文。我们可以发现，close不能帮助我们关闭连接的一个方向。

   2. shutdown

      ```c
      int shutdown(int sockfd,int howto) 
      // howto = SHUT_RD ,SHUT_WR,SHUT_RDWR
      ```

      - SHUT_RD(0)

        关闭连接的读方向，对该套接字进行读操作直接返回EOF，套接字上接收缓冲区已经有的数据将会被丢弃，如果再有新的数据流达到，会对数据进行ACK，然后悄悄的丢弃。对端还是会收到ACK，也就是说对端不知道数据已经丢掉。

      - SHUT_WR(1)

        关闭连接的写方向，也就是常说的半关闭。此时，不管套接字的引用是多少都会关闭连接的写方向。套接字的发送缓冲区中的所有数据会立即发送出去，并发送一个FIN报文给对端。应用程序如果对该套接字进行写操作，就会报错。

      - SHUT_RDWR(2)

        相当SHUT_RD 和 SHUT_WR 。

      - shutdown 和 close的区别：

        - close会关闭连接，并释放连接对应的资源，而shutdown 并不会释放套接字和所有的资源
        - close存在引用技术的概念，并不一定导致该套接字不可用；shutdown 则不管引用技术，直接使得该套接字不可用，如果有别的进程企图使用该套接字会收到影响。
        - clsoe的引用计数导致不一定会发出FIN结束报文，而shutdown则总是会发出FIN结束报文，如果我们需要通知对端关闭信息的时候是非常有用的。

   3. 

      

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

13. 非阻塞IO

    - 读操作

      如果套接字对应的接收缓冲区没有数据可读，在非阻塞情况下 read 调用会立即返回，一般返回 EWOULDBLOCK 或 EAGAIN 出错信息。在这种情况下，出错信息是需要小心处理，比如后面再次调用 read 操作，而不是直接作为错误直接返回。这就好像去书店买书没买到离开一样，需要不断进行又一次轮询处理。

    - write 操作

      我们发现在阻塞IO条件下，我们的write 函数输入的字节数 和 返回的结果的字节数总是一样的，在非阻塞 I/O 的情况下，如果套接字的发送缓冲区已达到了极限，不能容纳更多的字节，那么操作系统内核会尽最大可能从应用程序拷贝数据到发送缓冲区中，并立即从 write 等函数调用中返回。可想而知，在拷贝动作发生的瞬间，有可能一个字符也没拷贝，有可能所有请求字符都被拷贝完成，那么这个时候就需要返回一个数值，告诉应用程序到底有多少数据被成功拷贝到了发送缓冲区中，应用程序需要再次调用 write 函数，以输出未完成拷贝的字节。write 等函数是可以同时作用到阻塞 I/O 和非阻塞 I/O 上的，为了复用一个函数，处理非阻塞和阻塞 I/O 多种情况，设计出了写入返回值，并用这个返回值表示实际写入的数据大小。也就是说，非阻塞 I/O 和阻塞 I/O 处理的方式是不一样的。非阻塞 I/O 需要这样：拷贝→返回→再拷贝→再返回。而阻塞 I/O 需要这样：拷贝→直到所有数据拷贝至发送缓冲区完成→返回。

    - 总结

      | 操作    | 系统内核缓冲区状态 | 阻塞模式                                                     | 非阻塞模式                             |
      | ------- | ------------------ | ------------------------------------------------------------ | -------------------------------------- |
      | read()  | 缓冲区有数据       | 立即返回                                                     | 立即返回                               |
      | read()  | 缓冲区没有数据     | 阻塞，操作系统将cpu时间片分给其它的进程，不会分给处理 网络的进程，直到有数据到来为止 | 立即返回，返回EAGAIN 或者时EWOULDBLOCK |
      | write() | 发送缓冲区空闲     | 全部数据写入到发送缓冲区才返回                               | 能写多少写多少，立即返回               |
      | write() | 发送缓冲区不空闲   | 等待发送缓冲区空闲                                           | 立即返回，返回EAGAIN 或者时EWOULDBLOCK |

      1.read 总是在接收缓冲区有数据时就立即返回，不是等到应用程序给定的数据充满才返回。当接收缓冲区为空时，阻塞模式会等待，非阻塞模式立即返回 -1，并有 EWOULDBLOCK 或 EAGAIN 错误。

      2.和 read 不同，阻塞模式下，write 只有在发送缓冲区足以容纳应用程序的输出字节时才返回；而非阻塞模式下，则是能写入多少就写入多少，并返回实际写入的字节数。

      3.阻塞模式下的 write 有个特例, 就是对方主动关闭了套接字，这个时候 write 调用会立即返回，并通过返回值告诉应用程序实际写入的字节数，如果再次对这样的套接字进行 write 操作，就会返回失败。失败是通过返回值 -1 来通知到应用程序的。

    - 发达

14. so_linger 详解

    ```c
    struct linger {
                          int l_onoff;    /* linger active */
                          int l_linger;   /* how many seconds to linger for */
                  };
    // 操作系统默认调用close时，默认在等待
    
    ```

    

15. linux socket通信的错误处理机制

    1. RST 分节

       服务端应为某种原因关闭了连接(调用了close方法)，但是客户端依然在向服务端读写数据，此时服务端就会返回RST的复位标志(RST)。 RST产生的三个条件 ：目的地为某端口的SYN到达，然而改端口上没有服务监听 ；TCP取消一个连接 ；TCP接收到一个根本不存在的连接上的分节

    2. 超时信息

       

    3. SIGPIPE的信号

       信号的产生机制： 当一个进程向某个已经收到的RST的套接字进行读写操作时，内核会向应用进程发送SIGPIPE的信号。SIGPIPE产生的场景：

       ![network program-tcp_sigpipe](/home/anranfan/Downloads/network program-tcp_sigpipe.jpg)

    4. 异常情况

       - 对端无FIN包发送

         1. 网络中断

            很多情况会造成网络中断，TCP程序并不能及时感知到异常信息。除非网络中的其它网络设备，例如路由器，发送了ICMP报文，说明网络的不可达，这个时候通过read 或者 write 函数会返回 Unreaable的错误异常。

            如果没有ICMP报文的情况下，如果应用程序阻塞在read函数的调用上，那么很不辛，程序无法从异常中恢复，可以通过设置read的超时时间来解决。如果程序时先发送了write函数，然后阻塞在read调用上。Linux 的内户会不断尝试，将发送缓冲区的数据发送出去，大概在重传12次，大概9分钟以后，内核会将该连接标志为连接异常。这是，阻塞的read调用会立即返回一条TIMEOUT的错误信息。如果此时应用程序还在该连接上写数据，写操作会立即失败，返回一个SIGPIPE给应用程序。

         2. 系统崩溃(如断电)

            这种情况和网络中断很像，在没有ICMP报文的情况下，应用程序只能通过read ，write函数来感知异常。不过有一种情况需要考虑就是在系统崩溃恢复以后，当重传的TCP发送到重启的系统后，由于系统中没有TCP对应分组的连接，系统会返回一个RST的重置分节。如果阻塞的read调用，会立即返回Connection Reset的错误。如果时一次write 操作，也会立即失败内核返回SIGPIPE的信号

       - 对端有FIN包发送（如程序崩溃）

          可能的场景时对端调用了close和shutdown显示的关闭了连接，也可能时对端的应用程序崩溃，操作系统的内核代为清理发出的。 这种情况下，阻塞的read操作在正常接收的数据读取之后，FIN包会通过返回一个EOF来完成通知，此时，read调用返回为0。收到FIN包以后操作不会立即返回，需等到接收缓冲区的数据读取之后，在读到EOF标志，应用程序才会感知，之前已经在接收缓冲区的有效数据不会收到影响。如果此时没有read调用，而是write调用，一直在向套接子写入数据。因为收到FIN包意味着对方不会在发送消息。收到FIN包的一端，会将发送缓冲区的数据发送给对端，然后关闭套接子。当数据达到对端以后，操作系统的内核发现，这是一个指向关闭的套接字，会向客户端发送一个RST包，对于发送端来说，如果再执行write操作，就会立即返回一个RST的错误信息(BSD返回SIGPIPE的信号)。

       - 

       

    5. 发达

16. epoll 相关

    1. epoll的相关的数据接口
    
       - epoll_event
    
         ```c
         typedef union epoll_data {
                        void        *ptr;
                        int          fd;
                        uint32_t     u32;
                        uint64_t     u64;
                    } epoll_data_t;
         
                    struct epoll_event {
                        uint32_t     events;      /* Epoll events */
                        epoll_data_t data;        /* User data variable */
                    };
         
         ```
    
          
    
       - epoll_wait c
    
    
