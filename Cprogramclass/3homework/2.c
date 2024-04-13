#include <stdio.h>

int main()
{
    int cnt[ 26 ] = { 0 } ;
    
    char c = '\0' ;
    printf("Please putin the string : (End with enter)\n") ;
    while ( ( c = getchar() ) != '\n' )
    {
        if( c >= 'a' && c <= 'z' )
            cnt[ c - 'a' ] ++ ;
        else if( c >= 'A' && c <= 'Z' )
            cnt[ c - 'A' ] ++ ;
        c = '\0' ;
    }

    for ( int i = 0 ; i < 26 ; i ++ )
        printf("The times of '%c' and '%c' : %d\n" , i + 'a' , i + 'A' , cnt[ i ] ) ;
    
    return 0 ;
}