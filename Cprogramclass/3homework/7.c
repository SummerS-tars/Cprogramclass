#include <stdio.h>

#define N 100000
int a[ N ] ;

//输出100000之内的左右质数
int main()
{
    for ( int i = 2 ; i < N ; i ++ )
        a[ i ] = 1;

    for ( int i = 2 ; i < N ; i ++ )
        if ( a[ i ] )
        { 
            for ( int j = 2 ; i * j < N ; j ++ )
                a[ i * j ] = 0 ;
            printf("%d " , i ) ;
        }

    return 0;
}