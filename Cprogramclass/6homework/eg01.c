#include <stdio.h>

struct Date
{
    int day ;
    int month ;
    int year ;
};

struct student
{
    int number ;
    char name[ 10 ] ;
    char sex ;
    struct Date birthday ; /* 若采用C++语法,可以省去struct */
    char address[ 40 ] ;
};