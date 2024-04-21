#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void randInitArray( int a[] , int n , int range )
{
    long now ;
    srand(time(&now)) ;//这一步到底是什么意思呢？
    for( int i = 0 ; i < n ; i ++ )
        *a++ = rand() % range ;//生成不大于range的自然数
}

int main()
{
    int x[ 10 ] = { 0 } ;
    for( int i = 0 ; i < 10 ; i ++ )
        printf("%d " , x[ i ] ) ;
    puts("") ;

    randInitArray( x , 10 , 500 ) ;

    for( int i = 0 ; i < 10 ; i ++ )
        printf("%d " , x[ i ] ) ;
    puts("") ;

    return 0;    
}