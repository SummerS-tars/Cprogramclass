#include <stdio.h>

struct student_grade
{
    char num[ 15] ;//student number
    int grade[ 7 ] ;//1.Chinese 2.Math 3.English 4.Physics 5.Chemistry 6.Biology 7.P.E
    int sum ;//sum of the grades
};

void input_grade ( struct student_grade *A , int nums )//A:struct array name , nums:the size of the array
{
    char* cp[] = { "Chinese" , "Math" , "English", "Physics" , "Chemistry" , "Biology" , "P.E" };
    for( int i = 0 ; i < nums ; i ++)
    {
        (A + i)->sum = 0 ;
        printf("**enter the student number : ") ; getchar() ; fgets( (A + i)->num , 15, stdin ) ;
        
        for( int j = 0 ; j < 7 ; j ++ )
        {
            printf("enter the %s grade : " , cp [ j ] ) ;
            scanf("%d" , (A + i)->grade + j ) ;
            (A + i )->sum += (A + i)->grade[ j ] ;
        }
        printf("**now you have finished %d student(s)\n" , i + 1 ) ;
    }
    printf("**now you have finished all the students\n") ;
}

void sort_grade ( struct student_grade *A , int nums )//from high to low
{
    int sub ;
    char* cp[] = { "Chinese" , "Math" , "English", "Physics" , "Chemistry" , "Biology" , "P.E" , "Total" } ;
    for( int i = 0 ; i < 8 ; i ++ )
        printf("%d.%s\t\t" , i + 1 , cp[ i ] ) ;
    puts("") ;
    
    do 
    {
        printf("**choose the subject to sort(enter 1-8) : ") ;
        scanf("%d" , &sub ) ;
    }
    while( sub < 1 || sub > 8 ) ;

    if( sub == 8 )//sort by total
        for( int i = nums - 1 ; i >= 0 ; i -- )//pop sort (straightly sort the struct array , to get the array from high to low)
        {
            for( int j = 0 ; j < i ; j ++ )
            {
                if( (A + j)->sum < (A + j + 1)->sum )
                {
                    struct student_grade temp = *(A + j ) ;
                    *(A + j) = *(A + j + 1) ;
                    *(A + j + 1 ) = temp ;
                }
            }
        }
    else
        for( int i = nums - 1 ; i >= 0 ; i -- )//pop sort (straightly sort the struct array , to get the array from high to low)
        {
            for( int j = 0 ; j < i ; j ++ )
            {
                if( (A + j)->grade[ sub - 1] < (A + j + 1)->grade[ sub - 1])
                {
                    struct student_grade temp = *(A + j ) ;
                    *(A + j) = *(A + j + 1) ;
                    *(A + j + 1 ) = temp ;
                }
            }
        }

    printf("**now you have finished the sort by %s\n" , cp[ sub - 1 ] ) ;
}

void print_grade ( struct student_grade *A , int nums )
{
    puts("**start to output the grade info : ") ;
    char* cp[] = { "Chinese" , "Math" , "English", "Physics" , "Chemistry" , "Biology" , "P.E" } ;
    for( int i = 0 ; i < nums ; i ++ )
    {
        printf("student number : %s\n" , (A + i)->num ) ;
        for( int j = 0 ; j < 7 ; j ++ )
            printf("%s : %d\t\t" , cp[ j ] , (A + i)->grade[ j ] ) ;
            printf("Total : %d\n" , (A + i )->sum) ;
        puts("") ;
    }
    puts("**output finished") ;
}

int main()
{
    int nums ;
    printf("**enter the number of students : ") ; scanf("%d" , &nums ) ;
    struct student_grade s[ nums ] ;

    char* op[] = { "input" , "sort" , "output" , "quit" } ;
    while( 1 )
    {
        int option ;
        puts("**choose the option : ") ;
        for( int i = 0 ; i < 4 ; i ++ )
            printf("%d.%s\t\t", i + 1 , op[ i ] ) ;
        puts("") ;
        scanf("%d" , &option) ;
        if( option < 1 || option > 4 )
        {
            puts("invalid option") ;
            continue ;
        }
        else if( option == 4 )
        {
            printf("**ready to quit\n") ;
            break ;
        }
        else if( option == 1 ) input_grade( s , nums ) ;
        else if( option == 2 ) sort_grade( s , nums ) ;
        else print_grade( s , nums ) ;
    }

    return 0;
}