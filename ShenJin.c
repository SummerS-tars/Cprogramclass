#include <stdio.h>
#include <string.h>
int main(){
    /****** Begin **********/
    char num[ 100 ] = { 0 } ;
    scanf("%s" , num ) ;
    
    int len = strlen( num ) ;
    int is_Rep = 1 ;
    for( int i = 0 ; i <= len / 2 ; i ++ )
        if( num[ i ] != num[ len - i ] )
        {
            is_Rep = 0 ;
            break ;
        } 

    if( is_Rep ) printf("Yes!") ;
    else printf("No!") ;
    
    /****** End ************/
    return 0;
}