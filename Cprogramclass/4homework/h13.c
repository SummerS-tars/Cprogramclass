#include <stdio.h>

#define IS_LY(year) int judge;\
    if( (year) % 4 == 0 )\
        if( (year) % 100 == 0 )\
            if( (year) % 400 == 0 ) printf("%d is leap year\n", (year) );\
            else printf("%d is not leap year\n", (year) );\
        else printf("%d is leap year\n", (year) );\
    else printf("%d is not leap year\n", (year) )

int main()
{
    int year ;
    printf("please enter a year : ") ;
    scanf("%d" , &year ) ;
    IS_LY(year) ;

    return 0;
}