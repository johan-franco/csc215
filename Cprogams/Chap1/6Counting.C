#include <stdio.h>

main(argc, argv)
int argc;
char** argv;
{
    FILE *infp;
    int nl, t, b;
    char c;
    nl = 0;
    t = 0;
    b = 0;
    if (argc != 2) {
        printf("Input of one file needed\n");
        return;
    }
    printf("Starting the count!\n");
    infp = fopen(argv[1], "r");
    while ((c = fgetc(infp)) != EOF) {
        if(c == '\n') {
            nl+=1;
        }
        else if (c == " ")
        {
            b+=1;
        }
        else if (c == '\t')
        {
            t+=1;
        }
        
    }
    printf("Num of tabs %d \n Num of spaces %d \n Num of newlines %d \n", t,b,nl);
    fclose(infp);
    return 0;
}