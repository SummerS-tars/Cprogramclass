# unit2 基本数据类型 and 相关计算

## 2.1 基本数据类型

三种：整数 浮点数 and 字符  
有穷性  

### 2.1.1 整形数据

不带小数点 and 指数符号 的数据  

长度修饰：short , long  
符号类型修饰：signed , unsigned  

其中signed为int的默认类型，可以省略  
short int 可以省略为 short  
long , unsigned 同理  

负数的表示方式，补码，用二进制的最高位的表示正负  

整常量的类型表示方式：  
加 L or l 表长整型常量  
加 U or u 表无符号整数  
在整数之后加上 U and L(顺序不限), 表无符号长整型  

### 2.1.2 浮点型数据

表带 小数点 or 指数符号 的数值数据  

三类：  
单精度型 float  
双精度型 double  
长双精度型 long double  
(实际上也存在long long double)  

一般格式：  
```正负号 整数部分.小数部分 指数部分```  

注意点：  

1. 整数部分 and 小数部分 至少存在一个  
2. 小数点 and 指数部分 至少存在一个  
3. 指数部分格式  
    ```e(or E)整数```  
    **整数不可以少！！！**  

合法举例：  
```7. .457 1E5 1.5e-6```  
不合法举例：  
```E4 .E5 4.0E```  

也可以在常数结尾加上类型字符：  
F 单精度  
L 长双精度  
默认为 双精度  

此外还需要注意：  
浮点数运算 和 数学中的小数运算 因为表示浮点数位数的限制是不一样的！！！  
浮点数运算需要考虑到有效位数的问题  

### 2.1.3 字符型数据

比较简单  
注意点：

1. 单个字符记得加`''`  
    值得注意的是，转义字符常量也是一个字符  
    转义字符的拓展用法:`\ddd`中`ddd`表1～3个**八进制**数字，表示对应字符的ASCII值；同理`\xhh`中`hh`表1～2个**十六进制**数字  
2. 字符串记得加`""`  
    值得注意的是，为单个字符赋值不要用`""`否则就算其中只有一个字符也是字符串，结尾要多一个空白字符  

### 2.2 基本 输入 and 输出

1. 单个字符的输入and输出  putchar() and getchar()  
    putchar()输出其实参所代表的字符  
    可以直接简单来说存在一个 int 向 char 的隐式转换  
    而getchar()不需要实参  
2. 格式输入and输出 printf() and scanf()  
    printf()转换说明：  
    `%`后 输出修饰符 and 输出格式符 ，输出修饰符可缺省  

    完全格式如下：  
    ```%[flags][width][.precision][length]specifier```  

| specifier      | 含义                         |
| ------------- | ---------------------------- |
| d or i        | 十进制输出整数               |
| o(必须是小写，其他未指明可以大写的都同理) | (不带0开头)八进制输出整数    |
| x or X        | (不带0x开头)十六进制输出整数 |
| u             | 无符号十进制输出整数         |
| f             | 小数形式输出单、双精度浮点数 |
| e or E        | 指数形式输出单、双精度浮点数 |
| c             | 输出一个字符                 |
| s             | 输出字符串                   |
| %             | 输出%                        |
| p             | 十六进制输出指针所指向的地址 |

| flags | 含义                            |
| ----- | ------------------------------- |
| -     | 给定width内左对齐(默认右对齐)   |
| +     | 强制结果前显示正负号(默认省略+) |
| #     | 搭配 o、x、X 非零值前显示 0、0x、0X ;搭配 e、E、f 强制输出含小数点 |