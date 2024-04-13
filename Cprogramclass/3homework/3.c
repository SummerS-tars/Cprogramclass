#include <stdio.h>

int main()
{
    printf("please putin your .c file :(end with '`')\n") ;
    
    char c = '\0' ;
    int cntl1 , cntl2 , cntr1 , cntr2 ;
    cntl1 = cntl2 = cntr1 = cntr2 = 0 ;
    while ( ( c = getchar() ) != '`' )
    {
        if ( c == '(') cntl1 ++ ;
        else if ( c == ')' ) cntr1 ++ ;
        else if ( c == '{' ) cntl2 ++ ;
        else if ( c == '}' ) cntr2 ++ ;
    }

    if ( cntl1 < cntr1 ) puts("lack '('") ;
    else if ( cntl1 > cntr1 ) puts("lack ')'") ;
    else puts("maybe no problem whit '(' and ')'") ;

    if ( cntl2 < cntr2 ) puts("lack '{'") ;
    else if ( cntl2 > cntr2 ) puts("lack '}'") ;
    else puts("maybe no problem whit '{' and '}'") ;

    return 0 ;
}