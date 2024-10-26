# Log

## Basic Information

Operation System    : Windows 11  
IDE Tool            : Visual Studio Code  
Compiler            : gcc (GCC) 14.1.0  

## Part 1 Menu

### Content

use char array to store  
details can be seen in [Menu](partFunction\1_Menu\00_1_menu.c)  

**two ways to clear the screen**  

1. based on `#include <stdlib.h>`  

    ```c
    system("clr") ;
    ```

2. based on ANSI  

    ```c
    printf("\033[H\033[J") ;
    ```

**menu store and print**  

1. multi-dimension array  
2. use one variance `pos` to store the position status  
3. use `getch()` in `conio.h` to get char without flush  
