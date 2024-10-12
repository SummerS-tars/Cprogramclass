#include <stdio.h>

int main() 
{
    int player_win, player_quit;
    int can_exit;
    scanf("%d", &player_win);
    scanf("%d", &player_quit);
    
    // TODO
    can_exit = player_win || player_quit ? 1 : 0 ;
    
    printf("can_exit: %d", can_exit);
    return 0; 
}