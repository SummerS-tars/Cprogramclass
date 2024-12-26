#ifndef CURSOROPERATION_H
#define CURSOROPERATION_H

void MoveCursorTo(int nRows, int nCols);        // 在任意位置移动光标
void GetCursorPosition(int *nRows, int *nCols); // 获取当前光标位置
void ClearPartialScreen(int Row, int Col);      // 清空参数位置后的屏幕
void HideConsoleCursor();                       // 隐藏光标
void ShowConsoleCursor();                       // 显示光标

#endif // CURSOROPERATION_H