#include <stdio.h>

int bitcount(unsigned int x) {
    int count = 0;
    while (x != 0) {
        x &= (x - 1); // delete rightmost 1-bit
        count++;
    }
    return count;
}

int main() {
    unsigned int x = 29; // binary: 11101, expected count is 4
    printf("Number of 1 bits in %u is %d\n", x, bitcount(x));
    return 0;
}

