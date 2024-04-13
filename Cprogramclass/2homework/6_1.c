#include <stdio.h>

int main()
{
    char nums[ 12 ] = { '\0' } ;
    scanf("%s" , nums ) ;

    for ( int i = 0 ; nums[ i ] ; i ++ )
    {
        printf("%c " , nums[ i ] ) ;
    } 

    return 0;
}