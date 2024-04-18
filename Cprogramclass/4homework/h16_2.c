#include <stdio.h>
#include "h16_1format.h"
#include "h16_1format.h"
//上述第三行就属于无效包含

int main()
{
    int n1 , n2 , n3 ;
    printf("please enter 3 nums : \n") ;
    printf("n1 = ") ; scanf("%d" , &n1 ) ;
    printf("n2 = ") ; scanf("%d" , &n2 ) ;
    printf("n3 = ") ; scanf("%d" , &n3 ) ;

    PR1(n1) ;
    PR2(n1,n2) ;
    PR3(n1,n2,n3) ;

    return 0;
}