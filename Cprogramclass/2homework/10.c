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
    if ( a + b - c < 1e-6 || a + c -b < 1e-6 || b + c - a< 1e-6  )//注：此处可以改进，但有点麻烦
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

    puts("�����ε�����") ;
    puts("����:") ;
    if ( rat ) printf("ֱ��������\n") ;
    else if ( ot ) printf("�۽�������\n") ;
    else printf("���������\n") ;
    puts("����:") ;
    if ( et ) printf("�ȱ�������\n") ;
    if ( it ) printf("����������\n") ;
    if ( ! it ) printf("��ͨ������\n") ;

    return 0 ;
}
//��Ų���֧��̫ǿ������