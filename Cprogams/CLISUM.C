#include <stdio.h>
main(argc,argv) 
int argc;
char **argv;
{
    int i, total;
    total = 0;
    for (i=1; i <= argc; ++i)
        total = total +  argv[i];
        printf(total);
    printf(total);
}
