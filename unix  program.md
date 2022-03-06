​		

#### 1.fcntl 函数详解

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* arg */ );
// 1. 
```

|   cmd   |                           可选参数                           | 功能描述 | 返回值                    |
| :-----: | :----------------------------------------------------------: | :------: | ------------------------- |
| F_SETFD | close-on-exec 标志位，如果是1 ，在执行execv 系列函数返回后，就关闭在子进程中访问的文件描述符<br />如果是0，在执行execv 系列函数返回后，就不关闭在子进程中访问的文件描述符<br />0: 关闭 close-on-exec <br /><br />1:打开对应文件描述符的close-on-exec 的标志 |          | 返回失败 -1               |
| F_SETFD |             获取文件描述符的close-on-exec 的标志             |          | 返回close-on-exec的标志位 |
|         |                                                              |          |                           |

​	
