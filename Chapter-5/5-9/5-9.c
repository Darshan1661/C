#include <stdio.h>

static char daytab[2][13] = {
   {0,31,28,31,30,31,30,31,31,30,31,30,31},
   {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int is_leap(int year) {
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

// day_of_year: convert month, day to day of year using pointers; returns -1 on error
int day_of_year(int year, int month, int day) {
    if (month < 1 || month > 12)
        return -1;
    int leap = is_leap(year);
    const char *p = *(daytab + leap) + 1; // pointer to first month day count
    if (day < 1 || day > *(p + month - 1))
        return -1;

    int doy = 0;
    while (--month > 0) {
        doy += *p++;
    }
    doy += day;
    return doy;
}

// month_day: convert day of year to month and day using pointers; returns 0 on success, -1 on error
int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = is_leap(year);
    const char *p = *(daytab + leap) + 1; // pointer to day counts of months
    int maxday = leap ? 366 : 365;
    if (yearday < 1 || yearday > maxday)
        return -1;

    int month = 1;
    while (yearday > *p) {
        yearday -= *p;
        p++;
        month++;
    }
    *pmonth = month;
    *pday = yearday;
    return 0;
}

// Test program
int main() {
    int year = 2025, month = 11, day = 7;
    int doy = day_of_year(year, month, day);
    if (doy == -1)
        printf("Invalid date: %d-%d-%d\n", year, month, day);
    else
        printf("%d-%02d-%02d is day %d of the year\n", year, month, day, doy);

    int m, d;
    if (month_day(year, doy, &m, &d) == -1)
        printf("Invalid day of year: %d\n", doy);
    else
        printf("Day %d of year %d is %02d-%02d\n", doy, year, m, d);

    return 0;
}

