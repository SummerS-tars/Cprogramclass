#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main()
{
    float x1 , y1 , x2 , y2 , x3 , y3 ;
    scanf("%lf%lf%lf%lf%lf%lf", &x1 , &y1 , &x2 , &y2 , &x3 , &y3 ) ;
    
    float a = sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2 ) ) ;
    float b = sqrt( (x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3 ) ) ;
    float c = sqrt( (x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3 ) ) ;

    bool rat = false ;
    bool ot = false ;
    bool at = false ;
    if ( a + b - c < 1e-6 || a + c -b < 1e-6 || b + c - a< 1e-6  )//娉細姝ゅ鍙互鏀硅繘锛屼絾鏈夌偣楹荤儲
        printf("-1\n") ;
    else
    {
        float d1 = a*a + b*b - c*c ;
        float d2 = a*a + c*c - b*b ;
        float d3 = b*b + c*c - a*a ;
        if (fabs(d1) < 1e-6 || fabs(d2) < 1e-6 || fabs(d3) < 1e-6 ) rat = true ;
        else if ( d1 < -1e-6 || d2 < -1e-6 || d3 < -1e-6 ) ot = true ;
        else at = true ;
    }

    bool et = false , it =false ;
    if ( fabs( a - b ) < 1e-6 || fabs( a - c ) <1e-6 || fabs( b - c ) <1e-6 )
    {
        if ( fabs( a - b ) < 1e-6 && fabs( b - c ) <1e-6) et = true ;
        it = true ;
    }

    puts("三角形的类型") ;
    puts("按角:") ;
    if ( rat ) printf("直角三角形\n") ;
    else if ( ot ) printf("钝角三角形\n") ;
    else printf("锐角三角形\n") ;
    puts("按边:") ;
    if ( et ) printf("等边三角形\n") ;
    if ( it ) printf("等腰三角形\n") ;
    if ( ! it ) printf("普通三角形\n") ;

    return 0 ;
}
//大概不能支持太强的数据