##### vim的记录和回放功能

```
首先在命令模式下：q+a ，开始记录操作，将操作记录到寄存器中，然后在当前行执行你想要的操作，最后按下q结束记录操作，然后@+a 在其它行可以进行回放刚才的操作，如果20+@+a可以在后变面0行执行回放操作
```

##### vim的列编辑模式

```
Ctrl+v 进入列选择模式，shift+i ,进入编辑，然后按两次esc，可以实现在多列进行编辑，
直接按下 进入visual 模式，按字符进行选择。
```

##### 自定义vim函数

```shell
## 在创将这些后缀文件时，自动创建文件的注释信息
autocmd BufNewFile *.[ch],*.hpp,*.cpp exec ":call SetTitle()"
func SetComment()
    call setline(1,"/*===================================================")
    call append(line("."),"*    Copyright(c) ".strftime("%Y")."All rights reserved.")
    call append(line(".")+1,"*  ")
    call append(line(".")+2,"*  文件名称:".expand("%:ti"))
    call append(line(".")+3,"*    创建者: 范安然")
    call append(line(".")+4,"*  创建日期:".strftime("%Y年%m月%d日"))
    call append(line(".")+5,"*      描述:")
    call append(line(".")+6,"*")
    call append(line(".")+7,"=========================================================*/")
endfunc
##  Ctrl + F9 自动生成方法的注释
map <C-F9> :call  SetMethodComment()<CR>
func SetMethodComment()
    call append(line("."),"/*")
    call append(line(".")+1,"* 函数名称:")
    call append(line(".")+2,"* 描    述:")
    call append(line(".")+3,"* 参    数:")
    call append(line(".")+4,"* 返    回:")
    call append(line(".")+5,"*/")
endfunc
## F5实现c和C++程序的编译
map <F5>    :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "! /.%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "! ./%<"
    endif
endfunc
## F8实现GDB调试
map <F8>    :call Runrgdb()<CR>
func! Runrgdb()
    exec "w"
    exec "!g++ % -g -o %<"
    exec "!gdb ./%<"
endfunc


```

##### vim插件安装

##### vim的替换功能

```shell
进入到命令模式：
%s/MUL/DIV/g  # 将文件中的所有MUL 替换位DIV
```

##### vim删除操作

```shell
:%s/r//g                    删除DOS方式的回车^M 
:%s= *$==                   删除行尾空白 

:%s/^(.*)n1/1$/               删除重复行 

:%s/^.{-}pdf/new.pdf/         只是删除第一个pdf 

:%s/<!--_.{-}-->//           又是删除多行注释（咦？为什么要说「又」呢？） 

:g/s*^$/d                    删除所有空行 ：这个好用有没有人用过还有其他的方法吗？
:g!/^dd/d                     删除不含字符串'dd'的行 
:v/^dd/d                     同上 （译释：v ==&nbspg!，就是不匹配！） 

:g/str1/,/str2/d              删除所有第一个含str1到第一个含str2之间的行 


:v/./.,/./-1join                压缩空行 
:g/^$/,/./-j                  压缩空行 

ndw 或&nbspndW              删除光标处开始及其后的&nbspn-1 个字符。 
d0                          删至行首。 
d$                          删至行尾。 
ndd                         删除当前行及其后&nbspn-1 行。 
x 或&nbspX                  删除一个字符。 
Ctrl+u                      删除输入方式下所输入的文本。 
^R                          恢复u的操作 
J                           把下一行合并到当前行尾 
V                           选择一行 
^V                          按下^V后即可进行矩形的选择了 
aw                          选择单词 
iw                          内部单词(无空格) 
as                          选择句子 
is                          选择句子(无空格) 
ap                          选择段落 
ip                          选择段落(无空格) 
D                           删除到行尾 
x,y                         删除与复制包含高亮区 

dl                          删除当前字符（与x命令功能相同） 
d0                          删除到某一行的开始位置 
d^                          删除到某一行的第一个字符位置（不包括空格或TAB字符） 
dw                          删除到某个单词的结尾位置 
d3w                         删除到第三个单词的结尾位置 
db                          删除到某个单词的开始位置 
dW                          删除到某个以空格作为分隔符的单词的结尾位置 
dB                          删除到某个以空格作为分隔符的单词的开始位置 
d7B                         删除到前面7个以空格作为分隔符的单词的开始位置 
d）                         删除到某个语句的结尾位置 
d4）                        删除到第四个语句的结尾位置 
d（                         删除到某个语句的开始位置 
d）                         删除到某个段落的结尾位置 
d{                          删除到某个段落的开始位置 
d7{                         删除到当前段落起始位置之前的第7个段落位置 
dd                         删除当前行 
d/text                     删除从文本中出现“text”中所指定字样的位置， 一直向前直到下一个该字样所出现的位置（但不包括该字样）之间的内容 
dfc                        删除从文本中出现字符“c”的位置，一直向前直到下一个该字符所出现的位置（包括该字符）之间的内容 
dtc                        删除当前行直到下一个字符“c”所出现位置之间的内容 ～
d$                         删除到某一行的结尾 
5dd                        删除从当前行所开始的5行内容 
dL                         删除直到屏幕上最后一行的内容 
dH                         删除直到屏幕上第一行的内容 
dG                         删除直到工作缓存区结尾的内容 
d1G                        删除直到工作缓存区开始的内容  
```

##### vim光标移动技巧

```
ma表示标记该行为a；包括第几列的信息，都在标记a里。 
‘a表示跳转到标记a处；会跳转到标记a的行首。单引号’ 
`a表示跳转到标记a处；会跳转到标记a的行，包括第几列
I是定位到行首，A是定位到行末
```





