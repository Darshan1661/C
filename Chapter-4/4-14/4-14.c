#include <stdio.h>

#define swap(t, x, y) do { \
    t temp = x;            \
    x = y;                 \
    y = temp;              \
} while (0)

int main() {
    int a = 5, b = 10;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(int, a, b);
    printf("After swap: a=%d, b=%d\n", a, b);

    double x = 2.5, y = 4.7;
    printf("Before swap: x=%.1f, y=%.1f\n", x, y);
    swap(double, x, y);
    printf("After swap: x=%.1f, y=%.1f\n", x, y);

    return 0;
}

