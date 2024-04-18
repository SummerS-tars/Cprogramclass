#include <stdio.h>

int main()
{
    int x , y ;
    printf("请输入x(x!=0)与y : ") ;
    scanf("%d%d" , &x , &y ) ;

    int cal ( int , int ) ;
    printf("x^y = %d\n" , cal( x ,  y ) ) ;

    return 0 ;
}

int cal ( int x , int y ) 
{
    if ( y == 0 ) return 1 ;

    return x * cal( x , y-1 ) ;
}