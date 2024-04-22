#include <stdio.h>

int main()
{
    int a[ 100 ][ 10 ] = { 0 } ;

    void initdata( int (*p)[ 10 ] , int , int ) ;
    void test( int (*p)[ 10 ] , int , int ) ;
    
    int row , col ;
    printf("please intput the row and col : " ) ;
    scanf("%d%d" , &row, &col ) ;

    initdata( a , row , col ) ;
    test( a , row , col ) ;

    return 0;
}

void initdata( int (*p)[ 10 ] , int row , int col )
{
    int num = 0 ;
    for( int i = 0 ; i < row ; i ++ )
        for( int j = 0 ; j < col ; j ++ )
            *(*(p + i) + j) = ++ num ;
}

void test( int (*p)[ 10 ] , int row , int col )
{
    for( int i = 0 ; i < row ; i ++ )
    {
        for( int j = 0 ; j < col ; j ++ )
            printf("%3d " , *(*( p + i ) + j ) ) ;
        puts("") ;
    }
}