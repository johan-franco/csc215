#include <stdio.h>


main(argc,argv) 
int argc;
char **argv;
{
    int i, j,total, input;
    char *a;
    total = 0;
    for (i=1; i < argc; ++i){
        a = argv[i];
        input = atoi(argv[i]);
        for (j=0; j <strlen(a); ++j){
            if (a[j] != '0' && input == 0){
                printf("OOPS %s is not accepted", a);
                return 0;
            }
        }
        total += input;
    }
    

    printf("SUM: %d",total);
    return 0;
}
