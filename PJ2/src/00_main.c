#include <stdio.h>
#include "01_menu.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustom.h"

int main()
{
    // ��ʼ���Զ����ͼ
    mapCustomIni(1 , 0) ;
    mapCustomIni(2 , 0) ;
    mapCustomIni(3 , 0) ;

    // ����˵�
    menuControl();

    // ����ʱ�ٴγ�ʼ���Զ����ͼ
    mapCustomIni(1 , 0) ;
    mapCustomIni(2 , 0) ;
    mapCustomIni(3 , 0) ;
    return 0;
}