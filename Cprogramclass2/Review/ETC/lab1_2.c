#include <stdio.h>

#define MAX 100

int N, M;
char garden[MAX][MAX];
int visited[MAX][MAX];

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || garden[x][y] == '.' || visited[x][y]) {
        return;
    }
    visited[x][y] = 1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                dfs(x + dx, y + dy);
            }
        }
    }
}

int countPuddles() {
    int puddles = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (garden[i][j] == 'W' && !visited[i][j]) {
                dfs(i, j);
                puddles++;
            }
        }
    }
    return puddles;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", garden[i]);
    }
    printf("%d\n", countPuddles());
    return 0;
}