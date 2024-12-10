#include <stdio.h>

main(argc, argv)
int argc;
char* argv[];
{
    FILE *infp;
    int ch, newpos, i;
    char buffer[1024]; 

    newpos = 0;

    if (argc != 2) {
        printf("Need input file ");
        return 1;
    }
    if ((infp = fopen(argv[1], "r")) == NULL) {
        printf("Can’t open %s\n", argv[1]);
        return 1;
    }
 
    while ((ch = fgetc(infp)) != EOF) {
        if (ch == '\n') {
            buffer[newpos++] = '\0'; 
            printf("%d: %s\n", newpos, buffer); 
            newpos = 0; 
        }
        else {
            if (newpos < 1024) { 
                buffer[newpos++] = ch; 
            }
        }
    }
    if (newpos > 0) {
        buffer[newpos++] = '\0'; 
        printf("%d: %s\n", newpos, buffer); 
    }

    fclose(infp);

}