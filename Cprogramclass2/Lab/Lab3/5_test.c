#include <stdio.h>
#include <math.h>
int main(){
    /**********begin**********/
    int n , sum = 0 ;
    scanf("%d" , &n ) ;
    int a[ n ] ;
    for( int i = 0 ; i < n ; i ++ )
    {
        scanf("%d" , &a[ i ] ) ;
        sum += a[ i ] ;
    }


    if( sum&1 )
    {
        printf("0") ;
        return 0;
    }

    int sumExist[ 1010 ] = { 0 } ;
    sumExist[ 0 ] = 1 ;
    for( int i = 0 ; i < n ; i ++ )
        for( int j = 0 ; j <= sum ; j ++ )
            if( sumExist[ j ] ) sumExist[ j + a[ i ] ] = 1 ; 
    if( sumExist[ sum / 2 ] ) printf("1") ;
    else printf("0") ;
    /**********end***********/
    return 0;
}