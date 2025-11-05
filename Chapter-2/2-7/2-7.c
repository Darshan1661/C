#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n) {
    // Create a mask with n bits set
    unsigned int mask = ((1U << n) - 1);

    // Shift mask to position p
    mask <<= p;

    // XOR x with mask to invert the bits at position p..p+n-1
    return x ^ mask;
}

int main() {
    unsigned int x = 0xFF;  // binary: 11111111
    int p = 3;              // position to start
    int n = 4;              // number of bits to invert

    unsigned int result = invert(x, p, n);

    printf("x = 0x%X\n", x);
    printf("invert(x, %d, %d) = 0x%X\n", p, n, result);

    return 0;
}

