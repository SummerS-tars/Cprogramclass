#include <stdio.h>

int main()
{
    for ( int i = 'A' ; i <= 'Z' ; i++ )
    {
        printf("the ASCII of '%c' : %8d(D)\n" , i , i ) ;
        printf("                   %#8o(O)\n" , i , i ) ;
        printf("                   %#8x(H)\n" , i , i ) ;
    }
    for ( int i = 'a' ; i <= 'z' ; i++ )
    {
        printf("the ASCII of '%c' : %8d(D)\n" , i , i ) ;
        printf("                   %#8o(O)\n" , i , i ) ;
        printf("                   %#8x(H)\n" , i , i ) ;
    }
    return 0;
}