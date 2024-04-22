#include <stdio.h>

int main()
{
    int (*fp)( int , int ) , x , y , z ;
    int min( int , int ) , max( int , int ) ;
    printf("Enter x , y : ") ;
    scanf("%d%d" , &x , &y ) ;
    fp = min ;
    z = (*fp)( x,  y ) ;
    printf("MIN(%d,%d) = %d\n" , x , y , z ) ;
    fp = max ;
    z = (*fp)( x , y ) ;
    printf("MAX(%d,%d) = %d\n" , x , y , z ) ;
    return 0 ;
}

int min( int a , int b )
{
    return a < b ? a : b ;
}

int max( int a, int b)
{
    return a > b ? a : b ;
}