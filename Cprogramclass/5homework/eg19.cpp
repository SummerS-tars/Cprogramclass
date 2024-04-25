#include <iostream>

using namespace std;

void swap ( int &a , int &b )
{
    int t = a ;
    a = b , b = t ;
}

int main()
{
    int a , b ;
    cout << "please enter two numbers : " ;
    cin >> a >> b ;
    swap( a , b ) ;
    cout << "the numbers after swapping are : " << a << " " << b << endl ;

    return 0 ;
}