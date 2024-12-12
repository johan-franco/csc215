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
int year, yearday, *pmonth, *day_tab;
{
    
    int i;

    for (i = 1; yearday > day_tab + i; i++) {
        yearday -= day_tab[i];
     }
    *pmonth = i;
    day_tab[0] = yearday;
}

checkyear(year, day_tab) 
int year, *day_tab;
{
    if(year % 4 == 0 && year% 100!= 0 || year%400 == 0) {
        day_tab[2] = 29;
    }
}

main() {
    int month, day, result, year;
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
    printf("Enter a date (day month year): ");
    if (scanf("%d %d %d", &day, &month, &year) == 3  ) {
        if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            checkyear(year,day_tab);
            result = day_of_year(year, month, day,day_tab); 
            printf("\n%d", result);
        } 
        else {
            printf("Invalid date\n");
        }
    } else {
        printf("Enter three integers\n");
    }


    return 1;
}