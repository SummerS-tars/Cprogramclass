// 1.ABC
// 2.ABC
// 3.ABC output
// 2.BAC
// 3.BAC output
// 1.ACB
// 2.ACB
// 3.ACB output
// 2.CAB
// 3.CAB output
// 1.CBA
// 2.CBA
// 3.CBA output
// 2.BCA
// 3.BCA output
// 所有的3.会输出,通过递归实现

#include <stdio.h>

void pp ( char *s , int k )
{
    int i ;
    char c ;
    if( k == 0 ) printf("%s\n" , s ) ;
    else
        for( i = k - 1 ; i >= 0 ; i -- )
        {
            c = s[ k - 1 ] , s[ k - 1 ] = s[ i ] , s[ i ]  = c ;
            pp( s , k - 1 ) ;
            c = s[ k - 1 ] , s[ k - 1 ] = s[ i ] , s[ i ]  = c ;//恢复现场
        }
}

int main()
{
    char s[4] = "ABC" ;
    pp( s , 3 ) ;
}

//本题的关键是递归的实现,递归的思想是将问题分解为子问题,然后递归的解决子问题,最后将子问题的解组合起来得到原问题的解
//注意对恢复现场的处理,递归的时候改变了现场,递归结束后要恢复现场

/*
ABC
BAC
ACB
CAB
CBA
BCA
*/