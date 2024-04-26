#include <stdio.h>

struct address_book
{
    char name[ 20 ] ;
    char number[ 15 ] ;
    char email[ 30 ] ;
    char address[ 40 ] ;
};

void add_address_book ( struct address_book *a)
{
    printf("start to enter the information of this address_book_item\n") ;

    printf("please enter the name : ") ;
    fgets( a->name , 20 , stdin ) ;
    printf("please enter the number : " ) ;
    fgets( a->number , 15 , stdin ) ;
    printf("please enter the email : ") ;
    fgets( a->email , 30 , stdin ) ;
    printf("please enter the address : " ) ;
    fgets( a->address , 40 , stdin ) ;

    printf("you have finished entering the information\n") ;
}

void output_address_book ( struct address_book *a)
{
    printf("in this address_book_item \n") ;
    printf("name : %s\n" , a->name) ;
    printf("number : %s\n" , a->number ) ;
    printf("email : %s\n" , a->email ) ;
    printf("address : %s\n" , a->address ) ;
    printf("this item is over\n") ;
}

int main()
{
    struct address_book person_A ;

    add_address_book( &person_A ) ;
    output_address_book( &person_A ) ;

    return 0;
}