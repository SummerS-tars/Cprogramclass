#include <stdio.h>
#include <math.h>

int main()
{
    long long a = 0 , b = 1 , f1 = 0 , f2 = 0 ;
    long double c= ( 1.0 + sqrt( 5 ) ) / 2.0 ;
    long double d = c * c ;

    int i = 2 ;
    for (;; i ++ )
    {
        f1 = a + b ;
        f2 = ( long long )( d / sqrt( 5 ) + 0.5 ) ;

        if ( f1 != f2 ) break ;
        
        a = b , b = f1 ;
        d *= c ;
    }

    printf("f1 = %lld , f2 = %lld , i = %d\n" , f1 , f2 , i ) ;

    return 0 ;
}
/*f1 = 308061521170129 , f2 = 308061521170130 , i = 71*/