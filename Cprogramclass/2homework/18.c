#include <stdio.h>
#include <math.h>

int main()
{
    float c = ( 1.0 + sqrt( 5 ) ) / 2.0 ;
    float d = c * c ;

    int a = 0 , b = 1 , c1 , c2 ;
    int cnt = 1 ;
    do
    {
        cnt ++ ;
        c1 = a + b ;
        c2 = (int)( d / sqrt( 5 ) + 0.5 ) ; 
        
        a = b , b = c1 ;
        d *= c ;
    }
    while( c1 == c2 ) ;
    
    printf("c1 = %d , c2 = %d , i = %d\n" , c1 , c2 , cnt ) ;

    return 0;
}
/*c1 = 2178309 , c2 = 2178310 , i = 32*/