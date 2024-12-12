#include <stdio.h>

day_of_year(year, month, day, day_tab)
int year, month, day, *day_tab;
{

    int i;

    for (i = 1; i < month; i++)
        day += day_tab[i];

    return(day); 
}

month_day(year, yearday, pmonth, pday,day_tab)
int year, yearday, *pmonth, *pday, *day_tab;
{
    
    int i;

    for (i = 1; yearday > day_tab + i; i++) {
        yearday -= day_tab[i];
     }
    *pmonth = i;
    *pday = yearday;
}

checkyear(year, day_tab) 
int year, *day_tab;
{
    if(year % 4 == 0 && year% 100!= 0 || year%400 == 0) {
        day_tab[2] = 29;
    }
}

main() {
    int month, day, result;
    month = 3;
    day = 1;
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

    checkyear(year,day_tab);
    result = day_of_year(2024, month, day,day_tab); 
    printf("%d", result);
    return 1;
}