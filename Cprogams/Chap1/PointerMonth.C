int *day_tab[2];

day_tab = {
    {0, 31, 29, 31, 30, 31,3 0, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

day_of_year(year, month, day)
int year, month, day;
{
    int i, leap;

    leap = year%4 == 0 && year %100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++)
        day += day_tab[leap][i];
    return(day);
}

month_day(year, yearday, pmonth, pday)
int yearday, *pmonth, *pday;
{
    int i, leap;

    leap = year%4 == 0 && year %100 != 0 || year%400 == 0;
    for (i = 1; yearday > day_tab[leap][i]; i++)
        yearday -= day_tab[leap][i];
    return(day);
}

main()
{
    int birthday;
    birthday = day_of_year(2007,1,22);
    printf("%d", birthday)
    monthday()

}