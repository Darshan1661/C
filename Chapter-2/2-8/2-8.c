#include <stdio.h>

// Define the number of bits in an unsigned int
#define INT_BITS (sizeof(unsigned int) * 8)

/*
 * rightrot: rotate x to the right by n bits
 */
unsigned int rightrot(unsigned int x, int n) {
    n = n % INT_BITS; // To handle rotations larger than bit size
    return (x >> n) | (x << (INT_BITS - n));
}

int main() {
    unsigned int x = 0xF0F0; // Example number
    int n = 4; // Number of positions to rotate

    unsigned int rotated = rightrot(x, n);

    printf("Original x: 0x%X\n", x);
    printf("Rotated x: 0x%X\n", rotated);

    return 0;
}

