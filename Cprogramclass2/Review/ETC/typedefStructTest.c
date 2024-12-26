#include <stdio.h>
#include <locale.h>
#include <wchar.h>

typedef struct student{
    wchar_t name[20];
    int age;
} STUDENT;

int main()
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    STUDENT s1;
    wprintf(L"请输入学生姓名：");
    wscanf(L"%ls", s1.name);
    wprintf(L"请输入学生年龄：");
    wscanf(L"%d", &s1.age);
    wprintf(L"学生姓名：%ls\n", s1.name);
    wprintf(L"学生年龄：%d\n", s1.age);
    
    return 0;
}
