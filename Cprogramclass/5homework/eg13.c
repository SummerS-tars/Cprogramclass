#include <stdio.h>

int main()
{
    int *ap[ 5 ] , a[ 5 ][ 5 ] = { {1,2,3,4,5} , {6,7,8,9,10} , {11,12,13,14,15} , {16,17,18,19,20} , {21,22,23,24,25} } ;
    char *cp[ 5 ] , c[ 5 ][ 10 ] = { "apple" , "banana" , "cat" , "dog" , "elephant" } ;
    //以上 二维数组 可以用 分散的一维数组 来代替

    for( int i = 0 ; i < 5 ; i ++ )
        ap[ i ] = a[ i ] , cp[ i ] = c[ i ] ;
    
    for( int i = 0 ; i < 5 ; i ++ )
    {
        printf("*ap[ %d ] = %d\n" , i , *ap[ i ] ) ;
        for( int j = 0 ; j < 5 ; j ++ )
            printf("ap[ %d ][ %d ] = %d\n" , i , j , ap[ i ][ j ] ) ;
        puts("") ;

        printf("*cp[ %d ] = %s\n" , i , cp[ i ] ) ;
        for( int j = 0 ; j < 10 && cp[ i ][ j ] ; j ++ )
            printf("cp[ %d ][ %d ] = %c\n" , i , j , cp[ i ][ j ] ) ;
        puts("") ;
    }

    return 0;
}