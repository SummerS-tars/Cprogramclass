#include <stdio.h>

int main()
{
    int a[ 100 ] = { 0 } , num , *p = a ;
    printf("please enter tne size of the array(1~100) : " ) ;
    scanf("%d" , &num ) ;

    printf("please enter the elements of the array : \n" ) ;
    for( int i = 0 ; i < num ; i ++ )
    {
        printf("a[ %d ] = " , i ) ;
        scanf("%d" , p + i ) ;
    }

    int *find( int * , int , int ) ;

    int *p1 , x ;
    printf("please enter the number to be searched : " ) ;
    scanf("%d" , &x ) ;
    p1 = find( p , num , x ) ;

    if( ! p1 ) printf("404 not found\n") ;
    else printf("p1 = &a[ %d ] , *p1 = %d\n" , p1 - p , *p1 ) ;
    return 0;
}

int *find( int *p , int n , int x )
{
    for( int i = 0 ; i < n ; i ++ )
        if( *(p + i) == x ) return p + i ;
    return NULL ;
}