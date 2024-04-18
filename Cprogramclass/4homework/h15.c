#include <stdio.h>

int a[ 1000 ] ;

#define DEF_ARRAY(NUM) printf("please enter %d numbers : ", (NUM) );\
for(int i = 0 ; i < NUM ; i ++ ) scanf("%d", &a[ i ] )

#define PRI_ARRAY(NUM,LINE) for( int i = 0 ; i < NUM ; )\
{   for( int j = 1 ; i < NUM && j <= LINE ; j ++ , i ++ ) printf("%d " , a[ i ] ) ;\
    puts("");\
}

int main()
{
    int n ;
    printf("please enter the size of the array :\nn = ");
    scanf("%d" , &n ) ;

    DEF_ARRAY(n) ;

    int num , line ;
    printf("please enter how much you want to present and how much numbers per line :\nnum = ");
    scanf("%d" , &num ) ;
    printf("linelen = ") ;
    scanf("%d" , &line ) ;

    PRI_ARRAY(num,line) ;

    return 0;
}