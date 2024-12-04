#include <stdio.h>

main(argc, argv)
int argc;
char** argv;
{
    FILE *infp;
    int c;

    if (argc != 2) {
        printf("Input of one file needed\n");
        return;
    }
    printf("Starting the count!\n");
    infp = fopen(argv[1], "r");
    while ((c = fgetc(infp)) != EOF) {
        if 
    }
    fclose(infp);

}