#include <stdio.h>
#include ".\eg13_4.h"

int main()
{
    int x , y ;
    double power ( int , int ) ;
    printf("please enter two integers: ") ;
    scanf("%d%d" , &x , &y ) ;
    printf("%d**%d = %.0f\n" , x , y , power( x , y ) ) ;
    return 0;
}