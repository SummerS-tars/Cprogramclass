#ifndef CURSOROPERATION_H
#define CURSOROPERATION_H

void MoveCursorTo(int nRows, int nCols);        // ������λ���ƶ����
void GetCursorPosition(int *nRows, int *nCols); // ��ȡ��ǰ���λ��
void ClearPartialScreen(int Row, int Col);      // ��ղ���λ�ú����Ļ
void HideConsoleCursor();                       // ���ع��
void ShowConsoleCursor();                       // ��ʾ���

#endif // CURSOROPERATION_H