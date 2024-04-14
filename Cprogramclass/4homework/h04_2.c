#include <stdio.h>

int mul ( int , int ) ;
void main()
{
    int u , v , w ;
    printf("Enter two integers!\n") ;
    scanf("%d%d" , &u , &v ) ;
    if ( v>= 0 ) w = mul ( u , v ) ;
    else w = -mul ( u , -v ) ;
    printf("The result is %d\n" , w ) ;
}

int mul ( int a , int b )
{
    if ( a == 0 || b ==0 ) return 0;
    if ( b== 1 ) return a ;
    return a + mul ( a , b-1 ) ;
}

/*此程序的功能为：
 *通过递归加法实现两个整数的乘法
 */