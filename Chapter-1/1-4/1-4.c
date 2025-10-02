#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower = -20, upper = 100, step = 10;

    celsius = lower;
    while (celsius <= upper) {
        fahr = (9.0/5.0) * celsius + 32.0;
        printf("%7.1f %10.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}

