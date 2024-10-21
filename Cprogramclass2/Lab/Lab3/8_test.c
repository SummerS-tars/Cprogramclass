#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

int main()
{
    char str1[ 100 ] = { "你好" } , str2[ 100 ] = { 0 } ;
    printf("%s\n" , str1 ) ;
    gets( str2 ) ;
    printf("%s\n" , str2 ) ;
    return 0;
}