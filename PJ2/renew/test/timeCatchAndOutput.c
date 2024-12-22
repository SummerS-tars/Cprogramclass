#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    time_t t = time(NULL);
    char timeStr[64];
    strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&t) );
    printf("Current time: %s\n", timeStr);
    return 0;
}