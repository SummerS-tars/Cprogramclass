#include <stdio.h>
#include <string.h>

int main()
{
    char str1[ 1000 ] = { '\0' } ;
    printf("please printf the string:");
    fgets( str1 , 1000 , stdin ) ;

    int sum = 0;
    int len = strlen( str1 ) ;
    for ( int i = 0 ; str1[ i ] ; i ++ )
    {
        int j = i ;
        if ( j < len && str1[ j ] >= 'a' && str1[ j ] <= 'z' || str1[ j ] >= 'A' && str1[ j ] <= 'Z' )
            sum ++ ;
        else continue ;
        while ( j < len && str1[ j ] >= 'a' && str1[ j ] <= 'z' || str1[ j ] >= 'A' && str1[ j ] <= 'Z' )
            j ++ ;
        i = j - 1;
    }

    printf("The number of words: %d \n" , sum ) ;
    return 0 ;
}