#include <stdio.h>

main(argc, argv)
int argc;
char* argv[];
{
    FILE *infp;
    int ch, newpos, counter, i;
    counter = 0;
    newpos = 0;
    char* buffer[1024];

    if (argc != 2) {
        printf("Need input file ");
        exit();
    }
    if ((infp = fopen(argv[1], "r")) == NULL) {
        printf("Can’t open %s\n", argv[1]);
        exit();
    }
 
    while ((ch = fgetc(infp)) != EOF) {
        counter++;
        if (ch == '\n') {
            newpos = counter - newpos;
            printf("%d: ", newpos);
            for (i = 0; i < newpos; ++i) {
                printf("%c", buffer[i]);
            }
            printf('\n');
        }
        else {            
            buffer[counter] = ch;
        }
    }
    fclose(infp);
}