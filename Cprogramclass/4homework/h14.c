#include <stdio.h>

#define MAX(A,B,C) if((A)<(B))\
    if((B)<(C)) printf("C is the biggest\n");\
    else printf("B is the biggest\n");\
else\
    if((A)<(C)) printf("C is the biggest\n");\
    else printf("A is the biggest\n")

int main()
{
    int a , b , c ;
    printf("please enter 3 numbers : \n") ;
    printf("a = ") ; scanf("%d" , &a ) ;
    printf("b = ") ; scanf("%d" , &b ) ;
    printf("c = ") ; scanf("%d" , &c ) ;

    MAX(a,b,c) ;

    return 0;
}