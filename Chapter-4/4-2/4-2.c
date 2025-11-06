#include <stdio.h>
#include <ctype.h>

double atof_ext(const char s[]) {
    double val, power;
    int i = 0, sign = 1, exp_sign = 1, exp = 0;

    // Skip whitespace
    while (isspace(s[i])) i++;

    // Sign of number
    if (s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // Integer part
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    // Fractional part
    if (s[i] == '.') {
        i++;
        for (power = 1.0; isdigit(s[i]); i++) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
        }
        val = val / power;
    }

    val = val * sign;

    // Exponent part
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '+' || s[i] == '-') {
            exp_sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        for (exp = 0; isdigit(s[i]); i++) {
            exp = 10 * exp + (s[i] - '0');
        }

        double exp_power = 1.0;
        for (int j = 0; j < exp; j++) {
            exp_power *= 10.0;
        }

        if (exp_sign == 1) {
            val *= exp_power;
        } else {
            val /= exp_power;
        }
    }

    return val;
}

int main() {
    char *tests[] = {
        "123.45e-6",
        "1.2345E3",
        "-0.00123e2",
        "+45.67",
        "3.14e0",
        "2.",
        ".5",
        "7e-1"
    };

    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        printf("atof_ext(\"%s\") = %g\n", tests[i], atof_ext(tests[i]));
    }

    return 0;
}

