#include <stdio.h>

#define EXIT_SUCCESS 0;
#define EXIT_ERROR 1;
main(argc,argv) 
int argc;
char **argv;
{
    int i, total, input;
    char *a;
    total = 0;
    for (i=1; i < argc; ++i){
        a = argv[i];
        for (i=0; i <strlen(a); )
        input = atoi(argv[i]);
        if (a[0] != '0' && input == 0){
            printf("OOPS %s is not accepted", a);
            return EXIT_ERROR;
            }

        else{
            total += input;
            }
    }

    printf("Total calculated: %d",total);
    return 0;
}
