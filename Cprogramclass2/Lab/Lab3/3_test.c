#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char yon[ 2 ][ 20 ] = {"有贷款意向" , "无贷款意向" } ;
    char workCmp[ 3 ][ 20 ] = { "自由职业" , "白领" , "工人" } ;
    char work[ 20 ] = { 0 }, ebg[ 20 ] ={ 0 } ;
    int year = 0 , income = 0 ;

    scanf("%s" , work ) ;
    printf("%s" , work ) ;
    if( !strcmp( work , workCmp[ 0 ] ) )
    {
        scanf( "%d" , &year ) ;
        if( year <= 25 ) printf("%s" , yon[ 1 ] ) ;
        else printf("%s" , yon[ 0 ] );
    }
    else if( !strcmp( work , workCmp[ 1 ] ) )
    {
        scanf("%d" , &year ) ;
        if( year <= 35 )
        {
            scanf("%d" , &income ) ;
            if( income < 10000 ) printf("%s" , yon[ 1 ] ) ;
            else printf("%s" , yon[ 0 ] ) ;
        }
        else printf("%s" , yon[ 0 ] ) ;
    }
    else if( !strcmp( work , workCmp[ 2 ] ) )
    {
        scanf("%d" , &year ) ;
        if( year <= 40 )
        {
            scanf("%s" , ebg ) ;
                if( !strcmp( ebg , "小学" ) ) printf("%s" , yon[ 1 ] ) ;
                else printf("%s" , yon[ 0 ] ) ;
            }
            else printf("%s" , yon[ 1 ] ) ;
    }
    
    return 0 ;
}