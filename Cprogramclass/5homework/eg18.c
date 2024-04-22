#include <stdio.h>
#define N sizeof a/sizeof a[ 0 ]

double max(double *, int) , min( double * , int ) , ave( double * ,int ) ;
double( *fpt[] )( double * , int ) = { max , min , ave , NULL } ;
char *menuName[] = { "求最大值" , "求最小值" , "求平均值" , "" } ;
double a[ 10 ] = { 1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 } ;

double (*menu( char **titptr))(double * , int )
{
    int ans , k ;
    printf("请选择以下菜单命令：\n") ;
    for( k = 0 ; menuName[ k ][ 0 ] != '\0' ; k ++ )
        printf("\t%d. %s\n" , k + 1 , menuName[ k ] ) ;
    printf("\t输入其他选项结束程序\n") ;
    scanf("%d" , &ans ) ;
    if ( ans < 1 || ans > 3 ) return NULL ;
    *titptr = menuName[ ans - 1 ] + 2 ;
    return fpt[ ans - 1 ] ;
}

int main()
{
    double (*fp)(double * , int ) ;
    char *titstr ;
    while ( 1 ) 
    {
        if((fp = menu(&titstr)) == NULL ) break ;
        printf("%s = %f\n" , titstr , (*fp)( a , N )) ;
    }
    return 0;
}

double max( double a[] , int n )
{
    int i ; double r ;
    for( r = a[ 0 ] ,i = 1 ; i < n ; i ++ )
        if( r < a[ i ] ) r = a[ i ] ;
    return r ;
}

double min( double a[] , int n )
{
    int i ; double r ;
    for( r = a[ 0] , i = 1 ; i < n ; i ++ )
        if( r > a[ i ] ) r = a[ i ] ;
    return r;
}

double ave( double a[] , int n )
{
    int i ; double r;
    for( r = 0 , i = 0 ; i < n ; i ++ )
        r += a[ i ]; 
    return r / n ;
}