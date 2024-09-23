#include <iostream>

using namespace std;

// printf test
int main()
{
    cout << "format output test" << endl ;
    printf("%+10.4Lf\n", 3.1415926);
    printf("%#10o\n" , 10 ) ;
    printf("%#10X\n" , 198 ) ;

    int sum ;
    printf("%#10p\n" , &sum ) ;
    double f = 3.1415926 ;  
    printf("%10.4llf\n", f ) ;
    printf("%10.4e\n" , f ) ;
    return 0 ;
    // 为什么用long double会输出错误的结果？
}