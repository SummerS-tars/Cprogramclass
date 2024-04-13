#include <stdio.h>

int main()
{
    int i = 1 , j = 2 , k = 3 , u = 47215 ;
    float x = 2.2 , y = 3.4 , z = -5.6 ;
    char c1 = 'a' , c2 = 'b' ;

    printf("i=%d   j=%d   k=%d   \n" , i , j , k ) ;
    printf("x=%.5f,y=%.5f,z=%.5f\n" , x , y , z ) ;
    printf("x+y=%.2f y+z=%.2f z+x=%.2f\n" , x + y , y + z , z + x ) ;
    printf("u=%d\n" , u ) ;
    printf("c1='%c' or %d(ASCII) c2='%c' or %d(ASCII)\n", c1 , (int) c1 , c2 , (int) c2 ) ;

    return 0 ;
}
//朱文凯 23307110192