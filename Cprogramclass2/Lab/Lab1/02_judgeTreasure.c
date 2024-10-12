#include <stdio.h>

#define x_1 5
#define y_1 5

int main() 
{
    int x_2, y_2;
    int in_the_same_position;
    scanf("%d %d", &x_2, &y_2);
    
    // TODO
    in_the_same_position = x_2 == x_1 && y_2 == y_1 ? 1 : 0 ;
    
    printf("in_the_same_position: %d\n", in_the_same_position);
    return 0;
}