#include <iostream>

using namespace std;

void swap ( int& a , int& b )
{
    int t = a ;
    a = b , b = t ;
    return ;
}

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    int a[ n ] ;

    for ( int i = 0 ; i < n ; i ++ )
        scanf("%d" , &a[ i ] ) ;
    
    int j = 1 ;
    for ( int i = 0 ; n - j >= 1 ; i = 0 , j ++ )
        while ( i + 1<= n - j)
        {
            if ( a[ i ] > a[ i + 1 ] ) swap ( a[ i ] , a[ i + 1 ] ) ;
            i ++ ;
        }
    
    for ( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    
    return 0 ;
}
/*n = 15
1 54 -13 35 -75 334 67 10 0 23 5 -3 24 100 34*/