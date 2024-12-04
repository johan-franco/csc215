#include <stdio.h>
main(argc,argv) 
int argc;
char **argv;
{
    int i, total;
    total = 0;
    for (i=1; i < argc; ++i)
        //"every char in an expression is automatically converted to an int" after the atoi
        total += atoi(argv[i]);
    //printf needs the %d doesn't work if you simply put total
    printf("Total calculated: %d",total);
}
