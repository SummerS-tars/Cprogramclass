#include <stdio.h>

long long fibonacci(int n) {
    if (n <= 2) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1 || n > 50) {
        printf("Please enter a value between 1 and 50.\n");
        return 1;
    }

    printf("F(%d) = %lld\n", n, fibonacci(n));
    return 0;
}