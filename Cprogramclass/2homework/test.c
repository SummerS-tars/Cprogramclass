#include <stdio.h>
#include <stdbool.h>

int main()
{
    _Bool a = -11 ;
    if ( a )
    {
        printf("1\n") ;
    }
    else
    {
        printf("0\n") ;
    }

    // C/C++强制类型转换时,非0的值对应bool值的1(不论正负),0的值对应bool值的0
    //判断条件留空时也是如此 ( i ) ( ! i ) 注意区别开,第一个是i非0输出true,第二个是i为0才输出true
}