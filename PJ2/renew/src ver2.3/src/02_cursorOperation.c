#include "02_cursorOperation.h"
#include <windows.h>

extern void MoveCursorTo(int nRows, int nCols) // 在任意位置移动光标
{
    COORD crdLocation;
    crdLocation.X = nRows;
    crdLocation.Y = nCols;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crdLocation);
}

void GetCursorPosition(int *nRows, int *nCols) // 获取当前光标位置
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        *nRows = csbi.dwCursorPosition.X;
        *nCols = csbi.dwCursorPosition.Y;
    }
}

void ClearPartialScreen(int Row , int Col )                                 //清空指定位置之后的屏幕
{                                   
    HANDLE hdout = GetStdHandle(STD_OUTPUT_HANDLE);                         //获取标准输出设备的句柄
    CONSOLE_SCREEN_BUFFER_INFO csbi;                                        //定义表示屏幕缓冲区属性的变量
    GetConsoleScreenBufferInfo(hdout, &csbi);                               //获取标准输出设备的屏幕缓冲区属性
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y, num = 0;                    //定义双字节变量
    COORD pos = {Row, Col};                                                 //表示坐标的变量（初始化为左上角(0, 0)点）

    //把窗口缓冲区全部填充为空格并填充为默认颜色（清屏）
    FillConsoleOutputCharacter(hdout, ' ', size, pos, &num);
    FillConsoleOutputAttribute (hdout, csbi.wAttributes, size, pos, &num );
    SetConsoleCursorPosition(hdout, pos);                                   //光标定位到参数位置
}

void HideConsoleCursor()    // 隐藏光标 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ShowConsoleCursor()    // 显示光标 
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 1};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}