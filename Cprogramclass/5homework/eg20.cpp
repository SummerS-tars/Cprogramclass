#include <iostream>

using namespace std;

int main()
{
    int i , s[] = { 0 , 2 , 4 , 6 , 8 } ;
    int &f( int a[] , int index ) ;

    i = f( s , 3 ) ;
    f( s , 3 ) = 22 ;// 返回了s[ 3 ] 的引用，所以可以对s[ 3 ] 进行赋值操作
    printf("f{s,3) = %d\n" , f(s , 3) ) ;
    printf("  i = %d\n" , i ) ;

    return 0;
}

int &f( int a[] , int index )
{
    return a[ index ] ;
}