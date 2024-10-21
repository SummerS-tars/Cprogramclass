#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[ 100 ] ={ '\0' } ;
    fgets( str , 100, stdin );
    for( int i = 0 ; i < strlen( str ) ; i ++ )
    {
        printf("%c" , str[ i ] ) ;
    }
    if( !strcmp( str , "工人") )
    {
        printf("工人\n") ;
    }
    else
    {
        printf("不是工人\n") ;
    }
    return 0 ;
}