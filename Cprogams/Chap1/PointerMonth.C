#include <stdio.h>

day_of_year(year, month, day, day_tab)
int year, month, day, *daytab;
{

    int i;

    for (i = 1; i < month; i++)
        day += day_tab + i;

    return(day); 
}

month_day(year, yearday, pmonth, pday,day_tab)
int year, yearday, *pmonth, *pday, *daytab;
{
    
    int i;

    for (i = 1; yearday > day_tab + i; i++) {
        yearday -= day_tab + i;
     }
    *pmonth = i;
    *pday = yearday;
}

main() {
    int *day_tab[13];
    day_tab[0] = 0;
    day_tab[1] = 31;
    day_tab[2] = 28;
    day_tab[3] = 31;
    day_tab[4] = 30;
    day_tab[5] = 31;
    day_tab[6] = 30;
    day_tab[7] = 31;
    day_tab[8] = 31;
    day_tab[9] = 30;
    day_tab[10] = 31;
    day_tab[11] = 30;
    day_tab[12] = 31;
    int month, day, result;
    month = 3;
    day = 4;
    result = day_of_year(2012, month, day,day_tab); 
    printf("%d", result);
    return;
}