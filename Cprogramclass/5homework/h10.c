#include <stdio.h>

int main()
{
    int scoredata[ 100 ][ 7 ] = { 0 } ;
    int num , subs ;
    printf("please enter the number of the students(1~100) : ") ;
    while( 1 )
    {
        scanf("%d" , &num ) ;
        if( num >= 1 && num <= 100 )
            break ;
        else printf("num not supported , please enter again : ") ;
    }
    printf("please enter the number of the subjects(1~6)   : ") ;
    while( 1 )
    {
        scanf("%d" , &subs ) ;
        if( subs >= 1 && subs <= 6 )
            break ;
        else printf("subs not supported , please enter again : ") ;
    }

    void InitData( int (*p)[ 7 ] , int , int ) ;
    void PrintSingleScore( int (*p)[ 7 ] , int , int ) ;
    void PrintAllScore( int (*p)[ 7 ] , int , int ) ;

    void (*fp[])( int (*p)[ 7 ] , int , int ) = { InitData , PrintSingleScore , PrintAllScore } ;
    char *menu[] = { "Initiate Data" , "Print Single Score" , "Print All Score" , "" } ;
    while( 1 )
    {
        printf("please choose the function : \n" ) ;
        for( int i = 0 ; *menu[ i ] != '\0' ; i ++ )
            printf("\t%d. %s\n" , i + 1 , menu[ i ] ) ;
        printf("\tenter other number to quit\n") ;

        int choice ;
        scanf("%d" , &choice ) ;
        if( choice < 1 || choice > 3 ) break ;
        fp[ choice - 1 ]( scoredata , num , subs ) ;
    }

    return 0;
}

//p为数据数组，[]中是1+subs，num为学生数，subs为科目数
void InitData ( int (*p)[ 7 ] , int num , int subs )
{
    for( int i = 0 ; i < num ; i ++ )
    {
        printf("please input the student number : ") ;
        scanf("%d" , *(p + i) ) ;

        for( int j = 1 ; j < 1 + subs ; j ++ )
        {
            printf("please input the score of subject %d : " , j ) ;
            scanf("%d" , *(p + i) + j ) ;
        }
    }
}

//p为数据数组，[]中是1+subs，num为学生数，subs为科目数
void PrintSingleScore ( int (*p)[ 7 ] , int num , int subs )
{
    int no ;
    printf("please input the student number : ") ;
    scanf("%d" , &no ) ;
    int i ;
    for( i = 0 ; i < num && **(p + i) != no ; i ++ ) ;// p + i 停留在学号为no的学生的成绩数组上
    if( i == num )
    {
        puts("No such student!\n") ;
        return ;
    }

    printf("*******") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf("******") ;
    puts("") ;

    printf("*  No *") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf(" Sc%d *" , i ) ;
    puts("") ;

    printf("*******") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf("******") ;
    puts("") ;

    printf("* %3d ", no ) ;
    for( int j = 1 ; j <= subs ; j ++ )
        printf("* %3d " , *(*(p + i) + j) ) ;
    puts("*") ;

    printf("*******") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf("******") ;
    puts("") ;
}

//p为数据数组，[]中是1+subs，num为学生数，subs为科目数
void PrintAllScore ( int (*p)[ 7 ] , int num ,int subs )
{
    printf("*******") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf("******") ;
    puts("") ;

    printf("*  No *") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf(" Sc%d *" , i ) ;
    puts("") ;

    for( int i = 0 ; i < num ; i ++ )
    {
        printf("*******") ;
        for( int i = 1 ; i <= subs ; i ++ )
            printf("******") ;
        puts("") ;

        printf("* %3d ", **(p + i) ) ;
        for( int j = 1 ; j <= subs ; j ++ )
            printf("* %3d " , *(*(p + i) + j) ) ;
        puts("*") ;
    }

    printf("*******") ;
    for( int i = 1 ; i <= subs ; i ++ )
        printf("******") ;
    puts("") ;
}