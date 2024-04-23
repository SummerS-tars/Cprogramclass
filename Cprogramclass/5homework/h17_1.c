#include <stdio.h>

void main_diagonal_rotation( int (*ip)[ 10 ] , int size )
{
    for( int i = 0 ; i < size ; i ++ )
        for( int j = i + 1 ; j < size ; j ++ )
        {
            int t = *(*(ip + i) + j) ;
            *(*(ip + i) + j ) = *(*(ip + j ) + i ) ;
            *(*(ip + j ) + i ) = t ;
        }
}

int main()
{
    int a[ 10 ][ 10 ] = { 0 } ;
    int size ;
    printf("please enter the size of the matrix : ") ;
    scanf("%d" , &size ) ;

    printf("please enter the elements of the matrix : \n") ;
    for( int i = 0 ; i < size ; i ++ )
        for( int j = 0 ; j < size ; j ++ )
            scanf("%d" , &a[ i ][ j ] ) ;
    
    main_diagonal_rotation( a , size ) ;

    printf("the matrix after main diagonal rotation is : \n") ;
    for( int i = 0 ; i < size ; i ++ )
    {
        for( int j = 0 ; j < size ; j ++ )
            printf("%d " , a[ i ][ j ] ) ;
        puts("") ;
    }

    return 0 ;
}