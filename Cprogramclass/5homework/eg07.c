#include <stdio.h>

void f1 ( int x , int y ) { int t = x ; x = y ; y = t ; }
void f2 ( int *x , int *y ) { int t = *x ; *x = *y ; *y = t ; }
void f3 ( int **x , int **y ) { int *t = *x ; *x = *y ; *y = t ; }

int main()
{
    int x = 1 , y = 2 ;
    int *xpt = &x , *ypt = &y ;
    printf("First : x = %d , y = %d\n" , x , y ) ;

    f1 ( x , y ) ;

    printf("After call f1() : x = %d , y = %d\n" , x , y ) ;

    x = 1 , y = 2 ;
    f2 ( &x , &y ) ;

    printf("After call f2() : x = %d , y = %d\n" , x , y ) ;

    x= 1 , y = 2 ;
    printf("Before call f3() : x = %d , y = %d\n" , x ,  y ) ;
    printf("Before call f3() : *xpt = %d , *ypt = %d\n" , *xpt , *ypt ) ;
    f3 ( &xpt , &ypt ) ;
    printf("After call f3() : x = %d , y = %d\n" , x , y ) ;
    printf("After call f3() : *xpy = %d , *ypt = %d\n" , *xpt , *ypt ) ;
    return 0;
}