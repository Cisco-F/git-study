 RUNOOB Markdown Test
======================
 Hello World!
 ---------------
###三级标题
####四级标题

*斜体*
**粗体**
***粗斜体***

***
哈哈哈哈哈哈
- - -
___
~~删除线~~
<u>下划线 </u>asdf

脚注[^1]

[^1]: ???

* first
* second
* third
***
1. first
   - A.1
   - A.2
1. second
   - B.1
   - B.2
2. third
***
>第一层嵌套
asdfasdasgjalksdjlg
>>第二层
>>>第三层
***
>区块中使用列表
>1. 第一项
>2. 第二项
***
1. 第一项
   >hahaha
   >heheeh
2. 第二项
***
输入代码 `printf("")`
```C
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
```

    printf("Hello World");
    return 0;
***
这是一个链接  [百度](https://www.baidu.com)
<https://www.baidu.com>
***
这个链接用 1 作为网址变量 [Google][1]
这个链接用 runoob 作为网址变量 [Runoob][runoob]
然后在文档的结尾为变量赋值（网址）

  [1]: http://www.google.com/
  [runoob]: http://www.runoob.com/
***
![RUNOOB 图标](http://static.runoob.com/images/runoob-logo.png)

![RUNOOB 图标](http://static.runoob.com/images/runoob-logo.png "RUNOOB")
***
| 左对齐 | 右对齐 | 居中对齐 |
| :-----| ----: | :----: |
| 单元格 | 单元格 | 单元格 |
| 单元格 | 单元格 | 单元格 |
***
$$
\begin{Bmatrix}
   a & b \\
   c & d
\end{Bmatrix}
$$
$$
\begin{CD}
   A @>a>> B \\
@VbVV @AAcA \\
   C @= D
\end{CD}
$$
$$\lim_{n\rightarrow+\infty}\sum_{n=1}^{100}f(\frac{1}{n})$$
$$\lim_{n\rightarrow+\infty} n$$