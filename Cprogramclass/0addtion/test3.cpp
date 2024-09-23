#include <iostream>

using namespace std;

int main()
{
    int a , b ;
    a = 1 ;
    b = 2 ; 
    cout << "sizeof a = " << sizeof( a ) << endl ;
    cout << "sizeof b = " << sizeof( b ) << endl ;
    cout << "sizeof a + b = " <<sizeof( a + b ) << endl ;
    cout << "sizeof double = " << sizeof(double) << endl ;
    //最后会输出4，因为sizeof( a + b )是sizeof( int )，而int的大小是4
    return 0 ;
}