#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
    // Create a mask for n bits
    unsigned int mask = ((1U << n) - 1);

    // Extract rightmost n bits from y
    unsigned int y_bits = y & mask;

    // Move mask to position p
    mask <<= p;

    // Clear the n bits at position p in x
    x &= ~mask;

    // Insert y_bits at position p
    x |= (y_bits << p);

    return x;
}

int main() {
    unsigned int x = 0xFFFF;            // binary: 1111111111111111
    int p = 4;                         // position to start
    int n = 3;                         // number of bits
    unsigned int y = 0x2;              // binary: 010

    unsigned int result = setbits(x, p, n, y);

    printf("x = 0x%X\n", x);
    printf("y = 0x%X\n", y);
    printf("setbits(x, %d, %d, y) = 0x%X\n", p, n, result);

    return 0;
}

