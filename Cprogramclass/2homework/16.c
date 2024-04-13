#include <stdio.h>
#include <math.h>

int main()
{
    double pi = 0 ;
    int i = 0 ;
    int pos = 1 ;

    while ( 4.0 / ( 2 * i + 1 ) >= 1e-2 )
    {
        pi += pos * 4.0 / ( 2 * i + 1 ) ;
        i ++ ;
        pos = - pos ;
    }
    printf("PI    : %.2f\ntimes : %d\n", pi , i ) ;

    while ( 4.0 / ( 2 * i + 1 ) >= 1e-3 )
    {
        pi += pos * 4.0 / ( 2 * i + 1 ) ;
        i ++ ;
        pos = - pos ;
    }
    printf("PI    : %.3f\ntimes : %d\n" , pi , i ) ;

    while ( 4.0 / ( 2 * i + 1 ) >= 1e-4 )
    {
        pi += pos * 4.0 / ( 2 * i + 1 ) ;
        i ++ ;
        pos = - pos ;
    }
    printf("PI    : %.4f\ntimes : %d\n" , pi , i ) ;

    while ( 4.0 / ( 2 * i + 1 ) >= 1e-5 )
    {
        pi += pos * 4.0 / ( 2 * i + 1 ) ;
        i ++ ;
        pos = - pos ;
    }
    printf("PI    : %.5f\ntimes : %d\n" , pi , i ) ;

    while ( 4.0 / ( 2 * i + 1 ) >= 1e-6 )
    {
        pi += pos * 4.0 / ( 2 * i + 1 ) ;
        i ++ ;
        pos = - pos ;
    }
    printf("PI    : %.6f\ntimes : %d\n" , pi , i ) ;

    return 0 ;
}
/*
PI    : 3.14
times : 200
PI    : 3.141
times : 2000
PI    : 3.1415
times : 20000
PI    : 3.14159
times : 200000
PI    : 3.141592
times : 2000000
*/