#include <stdio.h>

int main()
{
    int j = 10 ;
    int b[ j ] ;//其实这就是一个变长数组 其不能用static定义 即没有静态存储周期
    
    for ( int i = 1 ; i <= 10 ; i ++ )
    {
        int a[ i ] ;
    }

    return 0 ;
}