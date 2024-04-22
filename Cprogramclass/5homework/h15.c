#include <stdio.h>

int a = 2 , c = 4 ;
void f( int a , int *x )
{
    int b = 10 ;
    static int c = 20 ;
    b += a ++ ; c += a + b ; *x = c + 2 ;
}

int main()
{
    f( a , &c ) ;
    printf("In main( 1 ) : a = %d , c = %d \n" , a, c ) ;
    f( 3+c , &a ) ;
    printf("In main( 2 ) : a = %d , c = %d \n" , a , c ) ;

    return 0;
}