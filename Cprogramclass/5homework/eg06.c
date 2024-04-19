#include <stdio.h>

int main()
{
    int a , b; 
    printf("please enter two numbers : \n") ;
    printf("a = ") ; scanf("%d" , &a ) ;
    printf("b = ") ; scanf("%d" , &b ) ;

    void swap ( int* , int* ) ;
    swap ( &a , &b ) ;
    printf("a = %d , b = %d\n" , a , b ) ;
    return 0;
}

void swap ( int *a , int *b )
{
    int t = *a ;
    *a = *b , *b = t ;
}