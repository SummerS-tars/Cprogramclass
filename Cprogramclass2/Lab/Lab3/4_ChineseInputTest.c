#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char strch1[ 100 ] = { "你好" } , strch2 [ 100 ] = { '\0' } ;
    wchar_t strwch1[ 100 ] = { L"你好" } , strwch2[ 100 ] = { '\0' } ;

    scanf("%s" , strch2 ) ;
    wscanf(L"%ls" , strwch2 ) ;

    printf("length1 = %d\n" , strlen( strch1 ) ) ;
    printf("length2 = %d\n" , strlen( strch2 ) ) ;

    printf("length1 = %d\n" , wcslen( strwch1 ) ) ;
    printf("length2 = %d\n" , wcslen( strwch2 ) ) ;

    printf("change the line\n") ;

    //    for( int i = 0 ; i < strlen( strch1 ) ; i ++ )
    //        printf("%c" , strch1[ i ] ) ;
    //    printf("\n") ;
    //   for( int i = 0 ; i < strlen( strch2 ) ; i ++ )
    //      printf("%c" , strch2[ i ] ) ;
    //  printf("\n") ;

    printf("%s\n" , strch1 ) ;
    printf("%s\n" , strch2 ) ;
    wprintf(L"%ls\n" , strwch1 ) ;
    wprintf(L"%ls\n" , strwch2 ) ;


    //if( !strcmp( strch1 , strch2 ) ) printf("1") ;
    //else printf("0") ;

    
    return 0 ;
}