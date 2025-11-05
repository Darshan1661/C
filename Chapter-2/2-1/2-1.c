#include <stdio.h>
#include <limits.h>
#include <float.h>

void compute_int_ranges() {
    // Compute signed char range
    signed char schar_min = 0;
    signed char schar_max = 0;
    unsigned char uchar_max = 0;

    uchar_max = ~0;
    schar_max = uchar_max >> 1;
    schar_min = -schar_max - 1;

    // Compute signed short range
    short sshort_min = 0;
    short sshort_max = 0;
    unsigned short ushort_max = 0;

    ushort_max = ~0;
    sshort_max = ushort_max >> 1;
    sshort_min = -sshort_max - 1;

    // Compute signed int range
    int sint_min = 0;
    int sint_max = 0;
    unsigned int uint_max = 0;

    uint_max = ~0;
    sint_max = uint_max >> 1;
    sint_min = -sint_max - 1;

    // Compute signed long range
    long slong_min = 0;
    long slong_max = 0;
    unsigned long ulong_max = 0;

    ulong_max = ~0UL;
    slong_max = ulong_max >> 1;
    slong_min = -slong_max - 1;

    printf("Computed ranges:\n");
    printf("signed char: %d to %d\n", schar_min, schar_max);
    printf("unsigned char: 0 to %u\n", uchar_max);
    printf("signed short: %d to %d\n", sshort_min, sshort_max);
    printf("unsigned short: 0 to %u\n", ushort_max);
    printf("signed int: %d to %d\n", sint_min, sint_max);
    printf("unsigned int: 0 to %u\n", uint_max);
    printf("signed long: %ld to %ld\n", slong_min, slong_max);
    printf("unsigned long: 0 to %lu\n", ulong_max);
}

int main() {
    // Print ranges from standard headers
    printf("Ranges from standard headers:\n");
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char: 0 to %u\n", UCHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 to %u\n", USHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 to %u\n", UINT_MAX);
    printf("long: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: 0 to %lu\n", ULONG_MAX);

    // Floating-point ranges from float.h
    printf("\nFloating-point ranges from float.h:\n");
    printf("float: %e to %e\n", FLT_MIN, FLT_MAX);
    printf("double: %e to %e\n", DBL_MIN, DBL_MAX);
    printf("long double: %Le to %Le\n", LDBL_MIN, LDBL_MAX);

    // Compute ranges manually
    printf("\n");

    compute_int_ranges();

    return 0;
}

