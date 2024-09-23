#include <iostream>

using namespace std;

int main()
{
    int intbyte , shortbyte , longbyte , longlongbyte , floatbyte , doublebyte , longdoublebyte ;
    intbyte = sizeof(int) ;
    shortbyte = sizeof(short) ;
    longbyte = sizeof(long) ;
    longlongbyte = sizeof(long long) ;
    floatbyte = sizeof(float) ;
    doublebyte = sizeof(double) ;
    longdoublebyte = sizeof(long double) ;
    printf("intbyte        = %d\n" , intbyte ) ;
    printf("shortbyte      = %d\n" , shortbyte ) ;
    printf("longbyte       = %d\n" , longbyte ) ;
    printf("longlongbyte   = %d\n" , longlongbyte ) ;
    printf("floatbyte      = %d\n" , floatbyte ) ;
    printf("doublebyte     = %d\n" , doublebyte ) ;
    printf("longdoublebyte = %d\n" , longdoublebyte ) ;

    long a = 1 << 31 ;
    int b = 1 << 31 ;
    long long c = 1 ; c <<= 31 ;//注意这里不能直接赋值1<<32,常量默认以int类型存储,可以写成1LL<<32
    printf("a = %ld\n" , a ) ;
    printf("b = %d\n" , b ) ;
    printf("c = %lld\n" , c ) ;
    return 0 ;
}