1. 自己制造线程池的案例时 ，总是报Core Segment ，

   ```
   Segmentation fault (core dumped)
   ```

   

   直接退出了，而且是多线程的场景，用gdb一行一行的调试，debug的效率太低了，于是想通过调试产生的CoreDump 文件，来定位代码的位置。 可是遇到了一个问题，我并没有差生对应的core 文件。具体的解决步骤如下： 

   创建文件： 

   ```shell
   # 创建文件
   ~/.config/apport/settings
   # 文件内容如下：
   [main]
   unpackaged=true
   # 然后需要重启apport
   sudo systemctl restart apport
   # 编译应用程序： 
   gcc thread_pool.c main.c -o main -lpthread -g
   #执行应用程序
   ./main 
   # core 文件生成的路径默认在 /var/crash 目录下，具体文件的样式是通kernel.core_pattern 来定一的
   #执行命令查看kernel.core_pattern 
   sysctl kernel.core_pattern 
    #显示的结果
    kernel.core_pattern = /coredumps/core-%e-%s-%u-%g-%p-%t
    #默认情况下文件的名字想*.*100.crash 这样的格式，执行 cd /var/crash 
    _home_anranfan_projects_cs-course_course-code_network-program_src_mutil-process_main.1000.crash  mysql-server-8.0.0.crash
    # 以上文件并不能被 gdb直接调试使用，需要执行一下命令以后才能被gdb使用
    apport-unpack  ***.1000.crash    /home/project/thread-pool/core（target direectory ）   #target direectory 文件路径必须不存在
    # gdb调试core 文件
    gdb main ./core/CoreDump 
    # 结果
    Type "apropos word" to search for commands related to "word"...
   Reading symbols from main...
   [New LWP 146413]
   [New LWP 146411]
   [New LWP 146412]
   [Thread debugging using libthread_db enabled]
   Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
   Core was generated by `./main'.
   Program terminated with signal SIGSEGV, Segmentation fault.
   #0  function_pool (arg=0x559555f622a0) at thread_pool.c:53
   53	        pool->head = pool->head->next;
   [Current thread is 1 (Thread 0x7f55facbb700 (LWP 146413))]
   (gdb)
   # 很快定位到问题代码
   ```

   

   

