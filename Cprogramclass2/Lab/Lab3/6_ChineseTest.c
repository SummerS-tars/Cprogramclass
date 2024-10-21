#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    // Set the locale to the user's default environment
    setlocale(LC_ALL, "zh_CN.UTF-8");

    // Declare a wide character array to store input
    wchar_t input[100];

    // Prompt the user for input
    wprintf(L"请输入一些中文字符: ");
    
    // Read wide characters from standard input
    fgetws(input, 100, stdin);

    // Output the wide characters
    wprintf(L"您输入的中文字符是: %ls\n", input);

    return 0;
}