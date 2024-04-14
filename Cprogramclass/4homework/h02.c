#include <stdio.h>
#include <time.h>

void formula ( int fig )
{
    int d = 1 ;
    while ( fig -- ) d *= 10 ;

    srand(time(NULL));
    int a =1 + rand() % (d-1) , b =1 + rand() % (d-1) ;
    printf("%d * %d = " , a , b ) ;
    int ans ;
    scanf("%d" , &ans ) ;
    
    int correct = 0;
    if ( ans == a * b )
        correct = 1 ;
    
    char right[3][25] = { "Very good!" , "Excellent!" , "Nice work!" } ;
    char wrong[3][25] = { "No. Please try again." , "Wrong. Try once more." , "Don't give up!" } ;
    int r = rand() % 3 ;
    if ( correct )
        printf("%s\n" , right[r] ) ;
    else
        printf("%s\n" , wrong[r]) ;
    
    return ;
}

int main()
{
    int fig ;
    while ( 1 )
    {
        printf("请输入题目的位数(不小于1且不大于3输入0结束) : fig = ") ;
        scanf("%d" , &fig ) ;
        if ( fig == 0 ) break ;
        else if ( fig < 1 || fig > 3 )
        {
            printf("输入错误，请重新输入 : fig = ") ;
            scanf("%d" , &fig ) ;
            continue ;
        }
        
        printf("请回答以下问题 : \n") ;
        formula( fig ) ;
    }

    return 0;
}