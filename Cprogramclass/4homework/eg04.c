#include <stdio.h>
#include <math.h>

//判断三个数是否可以构成三角形的三条边
int istri(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        return 0;
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    return 1;
}

//计算三角形的面积
double triangle(double a, double b, double c) {
    if (!istri(a, b, c))
        return 0;

    double s, area;
    s = (a + b + c) / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

int main() {
    double a, b, c, area;

    // Read the values of sides a, b, and c
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    area = triangle(a, b, c);
    if (!area)
        printf("Not a triangle\n");
    else
        printf("Area of the triangle: %lf\n", area);

    return 0;
}