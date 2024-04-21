#include <stdio.h>
//此程序用于说明 指向数组元素的指针 and 指向数组的指针 的区别

int main()
{
    int a[ 3 ][ 4 ] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
    int  i , *ip , (*p)[ 4 ] ;
    p = a + 1 ;//p 指向 a[ 1 ]一维数组
    ip = p[ 0 ] ;//ip 指向 a[ 1 ][ 0 ]
    //此处如果改成 ip = p 会报警
    //warning: assignment to 'int *' from incompatible pointer type 'int (*)[4]' [-Wincompatible-pointer-types]
    //从报警可以看出 p 在编译中的类型是 int (*)[4] 而 ip 是 int * 类型
    for( i = 1 ; i <= 4 ; ip += 2 , i ++ )
        printf("%d\t" , *ip ) ;
    puts("") ;

    p = a ;
    for( i = 0 ; i < 2 ; p ++ , i ++ )
        printf("%d\t" , *(*(p + i) + 1) ) ;
    puts("") ;

    return 0;
}