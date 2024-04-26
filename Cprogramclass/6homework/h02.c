#include <stdio.h>

struct student
{
    char name[ 20 ] ;
    char sex ;
    int year ;
    char num[ 15 ] ;
    char phone_num[ 15 ] ;
    int grade[ 7 ] ;//1.CH 2.Math 3.EN 4.Phy 5.Che 6.Bio 7.P.E
};

void fill_stu_info ( struct student *A )
{
    puts("start to input the info") ;

    printf("enter the name : ") ; fgets( A->name , 20 , stdin ) ;
    printf("enter the sex(M/F) : ") ; scanf("%c" , &A->sex ) ; getchar() ;
    printf("enter the year : ") ; scanf("%d" , &A->year ) ; getchar() ;
    printf("enter the number : ") ; fgets( A->num , 15 , stdin ) ;
    printf("enter the phone number : ") ; fgets( A->phone_num , 15 ,stdin ) ;
    
    char *cp[] = { "Chinese" , "Math" , "English" , "Physics" , "Chemistry" , "Biology" , "P.E" } ;
    for( int i = 0 ; i < 7 ; i ++ )
    {
        printf("enter the %s grade : ", cp[ i ] ) ;
        scanf("%d" , A->grade + i ) ;
    }
        
    printf("now you have finished\n") ;
}

void print_stu_info ( struct student *A )
{
    puts("start to output the info") ;

    printf("name : ") ; printf("%s" , A->name ) ;
    printf("sex : ") ; printf("%c\n" , A->sex ) ;
    printf("year : ") ; printf("%d\n" , A->year ) ;
    printf("number : ") ; printf("%s", A->num ) ;
    printf("phone number : ") ; printf("%s" , A->phone_num);
    
    char *cp[] = { "Chinese" , "Math" , "English" , "Physics" , "Chemistry" , "Biology" , "P.E" } ;
    for( int i = 0 ; i < 7 ; i ++ )
        printf("%s grade : %d\n", cp[ i ] , A->grade[ i ] ) ;

    printf("output finished\n") ;
}

int main()
{
    struct student s1 ;
    fill_stu_info ( &s1 ) ;
    print_stu_info ( &s1 ) ;

    return 0;
}