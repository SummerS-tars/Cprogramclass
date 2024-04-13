
# 简单函数调用执行过程梗概

## first

    给形式参数分配内存空间

## second

    传实型参数（有必要要先计算其表达式）
        C语言规定实参到形参为单向传递（若要调整实参变量，涉及到后面的指针传递）
        即对形参的改变不会影响实参

        对于实参表达式，一般按照从右至左的顺序
        （总之没事不要瞎折腾那些奇怪的东西）

## third

    给函数局部变量分配内存空间

## forth

    执行函数体

## fifth

    执行完函数后释放函数调用的内存空间

## sixth

    （如果有返回值）返回值到函数调用处

## p.s.函数说明

    此外还有函数声明，常用于调用 执行处后 或 其他程序文件中 定义的函数
        值得注意的是，函数不能在别的函数中被定义，但可以被声明

e.g
```c
#include <stdio.h>
int main()
{
    double a, b ; 
    double min ( double , double ) ;//函数声明
    printf("Input a,b :") ;
    scanf("%lf%lf" , &a , &b ) ;
    printf("MIN(%f,%f) = %f\n" , a , b , min(a, b) ) ;
    return 0 ;
}
double min ( double x ,double y )
{
    return x < y ? x : y ;
}
```
