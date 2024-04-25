#include <iostream>

using namespace std;

struct Point
{
    int x ;
    int y ;
};

int main()
{
    int n ;
    printf("please enter the times you want to output : " ) ;
    scanf("%d" , &n ) ;
    void test1 () ;
    void test2 () ;
    int i = n ;

    const Point p = { 1 , 2 } ;
    cout << p.x << " " << p.y << endl ;

    puts("") ;

    while( i -- ) test1() ;

    puts("") ;
    
    i = n;
    while( i -- ) test2() ;

    return 0;
}

void test1 ()
{
    static Point p = { 1 , 2 } ;
    cout << ++ p.x << " " << ++ p.y << endl ;
}

void test2 ()
{
    register Point p = { 1 , 2 } ;
    cout << ++ p.x << " " << ++ p.y << endl ;
}