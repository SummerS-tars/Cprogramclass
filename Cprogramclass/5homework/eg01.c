#include <stdio.h>

int main()
{
    int i ;
    int *ip ;
    i = 7 ;
    ip = &i ;

    printf("address of i  : %x\nvalue   of ip : %x\n" , &i , ip ) ;
    printf("value  of i   : %d\nvalue  of *ip : %d\n" , i , *ip ) ;
    printf("'*' and '&' are inverses of each ohter\n") ;
    printf("&*ip = %x\n*&ip = %x\n" , &*ip , *&ip ) ;

    return 0;
}