#include <stdio.h>    /*I/O库*/
#include <time.h>     /*时间库*/
#include <stdlib.h>   /*数学或内存分配库*/

int main()
{
    int k ;
    long now ;
    srand( time( &now ) ) ;//用时间初始化随机数发生函数的初态，使初态总不相同
    for( k = 0 ; k < 10 ; k ++ )
        printf("%d\n" , rand() % 100 ) ;//小技巧：约束所有数据在某一范围内，可以用取模运算
    return 0;
}