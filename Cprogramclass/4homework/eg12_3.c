#include <stdio.h>

int add (int a, int b )
{
    return a + b ;
}

int main()
{
    printf("please enter two numbers : ") ;
    int a , b;
    scanf("%d%d" , &a , &b ) ;

    printf("a + b = %d\n" , add (a , b) ) ;

    return 0;
}