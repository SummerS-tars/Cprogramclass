#include "02_cursorOperation.h"
#include <windows.h>

extern void MoveCursorTo(int nRows, int nCols) // ������λ���ƶ����
{
    COORD crdLocation;
    crdLocation.X = nRows;
    crdLocation.Y = nCols;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crdLocation);
}

void GetCursorPosition(int *nRows, int *nCols) // ��ȡ��ǰ���λ��
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        *nRows = csbi.dwCursorPosition.X;
        *nCols = csbi.dwCursorPosition.Y;
    }
}

void ClearPartialScreen(int Row , int Col )                                 //���ָ��λ��֮�����Ļ
{                                   
    HANDLE hdout = GetStdHandle(STD_OUTPUT_HANDLE);                         //��ȡ��׼����豸�ľ��
    CONSOLE_SCREEN_BUFFER_INFO csbi;                                        //�����ʾ��Ļ���������Եı���
    GetConsoleScreenBufferInfo(hdout, &csbi);                               //��ȡ��׼����豸����Ļ����������
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y, num = 0;                    //����˫�ֽڱ���
    COORD pos = {Row, Col};                                                 //��ʾ����ı�������ʼ��Ϊ���Ͻ�(0, 0)�㣩

    //�Ѵ��ڻ�����ȫ�����Ϊ�ո����ΪĬ����ɫ��������
    FillConsoleOutputCharacter(hdout, ' ', size, pos, &num);
    FillConsoleOutputAttribute (hdout, csbi.wAttributes, size, pos, &num );
    SetConsoleCursorPosition(hdout, pos);                                   //��궨λ������λ��
}

void HideConsoleCursor()    // ���ع�� 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ShowConsoleCursor()    // ��ʾ��� 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 1};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}