#include <stdio.h>

int main()
{
    int N ;
    printf("please enter the number of rows : N = ") ;
    scanf("%d" , &N ) ;

    int p[ N * (N + 1) / 2 ] , i , j , *pt[ N ] ;
    for( pt[ 0 ] = p , i = 1 ; i < N ; i ++ )
        pt[ i ] = pt[ i - 1 ] + i ;//实现将 一维数组p 分散成 pt[0]~pt[7] 8个一维数组，长度分别为1~8
    
    for( i = 0 ; i < N ; i ++ )
    {
        pt[ i ][ 0 ] = pt[ i ][ i ] = 1 ;
        for( j = 1 ; j < i ; j ++ )
            pt[ i ][ j ] = pt[ i - 1 ][ j - 1 ] + pt[ i - 1][ j ] ;
    }

    for( int i = 0 ; i < N ; i ++ )
    {
        for( int j = 1 ; j < N - i ; j ++ )
            printf("   ") ;
        for( int j = 0 ; j <= i ; j ++ )
            printf("%3d   " , pt[ i ][ j ] ) ;
        puts("") ;
    }

    return 0;
}