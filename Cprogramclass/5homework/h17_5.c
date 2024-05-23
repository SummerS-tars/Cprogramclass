#include <stdio.h>

void lowercase_to_capital ( char *s )
{   
    while( *s )
    {
        if(*s >= 'a' && *s <= 'z') *s += 'A' - 'a' ;
        s ++ ;
    }
}

//test example
int main()
{
    char str[ 100 ] = "It's a nice day." ;

    lowercase_to_capital( str ) ;

    printf("%s\n" , str ) ;
}