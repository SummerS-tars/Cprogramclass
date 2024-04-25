#include <stdio.h>

void lowercase_to_capital ( char *s )
{   
    while( *s )
    {
        if(*s >= 'a' && *s <= 'z') *s += 'A' - 'a' ;
        s ++ ;
    }
}