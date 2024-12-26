#include<stdio.h>
#include<string.h>
int main(void)
{
    /*********Begin*********/
    char str[ 3 ][ 110 ] = { 0 } ;
    for( int i = 0 ; i < 3 ; i ++ )
    {
        fgets( str[ i ] , 110 , stdin ) ;
        int len = strlen( str[ i ] ) ;
        if( str[ i ][ len - 1 ] == '\n' ) str[ i ][ len - 1 ] = '\0' ;
    }

    printf("%s\n%s\n%s" , str + 0 , str + 1 , str + 2 ) ;

    //首先我们有strcmp函数可以用于进行比较
    int o1 , o2 , o3 ;
    if( strcmp(str[0] , str[1]) == 1 )
    {
        if( strcmp(str[1] , str[2]) == 1) o1 = 0 , o2 = 1 , o3 = 2 ;
        else if( strcmp(str[0] , str[2]) == 1) o1 = 0 , o2 = 2 , o3 = 1 ;
        else o1 = 2 , o2 = 0 , o3 = 1 ;
    }
    else
    {
        if(strcmp(str[0] , str[2]) == 1) o1 = 1 , o2 = 0 , o3 = 2 ;
        else if( strcmp(str[1] , str[2]) == 1) o1 = 1 , o2 = 2 , o3 = 0 ;
        else o1 = 2 , o1 = 1 , o3 = 0;
    }
    printf("%s\n%s\n%s" , str + o1 , str + o2 , str + o3 ) ;

    /*********End**********/
    return 0;
}