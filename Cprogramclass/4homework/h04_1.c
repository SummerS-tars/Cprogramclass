#include <stdio.h>
void main()
{
    int c ;
    if ( (c = getchar() ) != '\n' ) 
    {
        main() ;
        printf("%c" , c ) ;
    }
    else printf("\n") ;
}
/*此程序的功能：反向输出输入的字符，直到输入回车为止
 *示例：
 *input : 1234567890-=_+qaz wsx edc rfv tgb yhn ujm iok ol. p;/ [']
 *
 *output : ]'[ /;p .lo koi mju nhy bgt vfr cde xsw zaq+_=-0987654321
 */