#include <stdio.h>

int main()
{
    char a[ 11 ] = { '\0' } ;//支持到10位以内，大致包含了int的范围
    scanf("%s" , a ) ;

    int i ;
    for( i = 0 ; a[ i ] ; i ++ ) ;//找到最后一个为数字
    i -- ;
    
    int j = 0 ; 
    while ( i > j && a[ i ] == a[ j ] )
    {
        i -- ;
        j ++ ;
    }

    if ( i <= j )
        puts("Yes") ;
    else
        puts("No") ;

    return 0 ;
}