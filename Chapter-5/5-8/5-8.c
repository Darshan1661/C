#include <stdio.h>

static char daytab[2][13] = {
   {0,31,28,31,30,31,30,31,31,30,31,30,31},
   {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int is_leap(int year) {
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

// day_of_year:  return day of year from month & day; returns -1 on error
int day_of_year(int year, int month, int day) {
    if (month < 1 || month > 12)
        return -1;  // invalid month
    int leap = is_leap(year);
    if (day < 1 || day > daytab[leap][month])
        return -1;  // invalid day for month
    
    int doy = 0;
    for (int i = 1; i < month; i++)
        doy += daytab[leap][i];
    return doy + day;
}

// month_day:  set *pmonth and *pday from year and day of year;
// returns 0 on success, -1 on error (invalid day of year)
int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = is_leap(year);
    int maxday = leap ? 366 : 365;
    if (yearday < 1 || yearday > maxday)
        return -1;  // invalid day of year
    int month;
    for (month = 1; month <= 12 && yearday > daytab[leap][month]; month++) {
        yearday -= daytab[leap][month];
    }
    if (month > 12)  // safety check, should never occur
        return -1;
    *pmonth = month;
    *pday = yearday;
    return 0;
}

// Test program with example inputs
int main() {
    int year = 2024;
    int month = 2, day = 29;
    int doy = day_of_year(year, month, day);

    if (doy == -1)
        printf("Invalid date %d-%02d-%02d\n", year, month, day);
    else
        printf("%d-%02d-%02d is day %d of the year\n", year, month, day, doy);

    int pmonth, pday;
    int err = month_day(year, doy, &pmonth, &pday);
    if (err == -1)
        printf("Invalid day of year %d for year %d\n", doy, year);
    else
        printf("Day %d of year %d is %02d-%02d\n", doy, year, pmonth, pday);

    // Test invalid inputs
    printf("Invalid test day_of_year: %d\n", day_of_year(year, 13, 1));
    int e = month_day(year, 367, &pmonth, &pday);
    printf("Invalid test month_day returns %d\n", e);

    return 0;
}

