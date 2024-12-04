#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point point;
    int distance;
} QueueNode;

int isValid(int x, int y, int n, int m, int maze[n][m], int visited[n][m]) {
    return (x >= 0) && (x < n) && (y >= 0) && (y < m) && (maze[x][y] == 0) && (!visited[x][y]);
}

int bfs(int n, int m, int maze[n][m]) {
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    int visited[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = 0;
        }
    }

    visited[0][0] = 1;

    QueueNode queue[MAX];
    int front = 0, rear = 0;

    queue[rear++] = (QueueNode){{0, 0}, 0};

    while (front < rear) {
        QueueNode curr = queue[front++];

        Point pt = curr.point;

        if (pt.x == n - 1 && pt.y == m - 1) {
            return curr.distance;
        }

        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col, n, m, maze, visited)) {
                visited[row][col] = 1;
                queue[rear++] = (QueueNode){{row, col}, curr.distance + 1};
            }
        }
    }

    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int maze[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    printf("%d\n", bfs(n, m, maze));

    return 0;
}