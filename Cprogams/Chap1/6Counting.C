#include <stdio.h>

main(argc, argv)
int argc;
char** argv;
{
    FILE *infp;
    int c, nl, t, b;

    if (argc != 2) {
        printf("Input of one file needed\n");
        return;
    }
    printf("Starting the count!\n");
    infp = fopen(argv[1], "r");
    while ((c = fgetc(infp)) != EOF) {
        if(c == '\n') {
            ++nl
        }
        else if (c == " ")
        {
            ++b
        }
        else if (c == '\t')
        {
            ++t
        }
        
    }
    printf("Num of tabs %d \n Num of spaces %d \n Num of newlines %d \n", t,b,nl)
    fclose(infp);

}