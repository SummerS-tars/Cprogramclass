#include <stdio.h>

int main()
{
    void init( int * , int * ) ;
    int add( int , int ) ;
    int sub( int , int ) ;
    int mul( int , int ) ;
    int div( int , int ) ;
    void executer( int (*)( int , int ) , int , int ) ;

    int a, b ;
    int (*p[])( int , int ) = { add , sub , mul , div } ;
    char *op[] = { "initiate a and b" , "add a and b" , "subtract b from a" , "multiply a and b" , "divide a by b" , "" } ;
    
    while( 1 )
    {
        printf("choose your operation : \n" ) ;
        for( int i = 0 ; op[ i ][ 0 ] ; i ++ )
            printf("\t%d. %s\n" , i + 1 , *(op + i) ) ;
        printf("\t6. enter other characters to quit\n") ;
        
        int choice ;
        scanf("%d" , &choice ) ;
        if( choice == 1 ) init( &a , &b ) ;
        else if( choice > 1 || choice <= 5 ) executer( p[ choice - 2 ] , a , b ) ;
        else break ;
    }

    return 0;
}

void init( int *a , int *b )
{
    printf("enter a and b : ") ;
    scanf("%d%d" , a , b ) ;
}

int add( int a , int b )
{
    return a + b;
}

int sub( int a , int b )
{
    return a - b ;
}

int mul( int a ,int b)
{
    return a * b ;
}

int div( int a, int b)
{
    return a / b ;
}

void executer( int (*p)( int , int ) , int a , int b )
{
    printf("result is %d\n" , p( a , b )) ;
}