#include <stdio.h>

int main()
{
    char s1[ 1000 ] = { '\0' }, s2[ 1000 ] = { '\0' } ;

    printf("请输入s1:(only letters & end with enter)");
    fgets( s1 , 1000 , stdin ) ;

    printf("\n请输入s2:(only letters & end with enter)");
    fgets( s2 , 1000 ,stdin ) ;

    int a[ 26 ] = { 0 } , A[ 26 ] = { 0 } ;
    for ( int i = 0 ; s2[ i ] ; i ++ )
    {
        if ( s2[ i ] >= 'A' && s2[ i ] <= 'Z' )
        A[ s2[ i ] - 'A' ] ++ ;
        else if ( s1[ i ] >= 'a' && s1[ i ] <='z' )
        a[ s2[ i ] - 'a' ] ++ ;
    }

    char str[ 1000 ] = { '\0' } ;
    int tt = -1 ;
    for ( int i = 0 ; s1[ i ] != '\n' ; i ++ )
    {
        int a1 = s1[ i ] - 'a' , A1= s1[ i ] - 'A' ;
        if ( a1 >= 0 && a1 <= 26 && ! a[ a1 ] )
        {
            str[ ++ tt ] = s1[ i ] ;
            continue;
        }
        if ( A1 >= 0 && A1 <= 26 && ! A[ A1 ] )
        {
            str[ ++ tt ] = s1[ i ] ;
            continue;
        }
    }

    printf("%s\n" , str ) ;
    return 0;
}