#include <stdio.h>

/*思路：实现函数可知本身被调用了多少次
 *显然不能是局部变量来统计，
 *因为局部变量每次调用都会被初始化，
 *而只要求函数内部本身可见，
 *那么static存储类型就很合适
 */
void foo1 () ;

int main()
{
    int n ;
    printf("enter an integer : n = " ) ;
    scanf("%d" , &n ) ;

    for ( int i = 1 ; i <= n ; i ++ )
        foo1 () ;
    
    return 0;
}

void foo1 ()
{
    static int cnt = 0;
    printf("foo1() has been called %d times\n" , ++ cnt ) ;

    return ;
}