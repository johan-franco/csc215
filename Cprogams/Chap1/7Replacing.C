#include <stdio.h>

main(argc, argv)
int argc;
char** argv;
{

    FILE *infp, *outfp;
    int c; 
    prev = EOF;
    if (argc != 3) {
        printf("Both input and output needed\n");
        return 1;
    }
    printf("Changing multiple blanks to one");

    if ((infp = fopen(argv[1], "r")) == NULL) {
        printf("Can’t open %s\n", argv[1]);
        return 1;
    }
    if ((outfp = fopen(argv[2], "w")) == NULL) {
        printf("Can not open %s\n", argv[2]);
        fclose(infp);
        return 1;
    }

    while ((c = fgetc(infp)) != EOF) {
        if (c == ' ' && prev == ' ') {
	    prev = c;
            continue;
        }
        fputc(c, outfp); 
        putchar(c);      
        prev = c;       
    }

    fclose(infp);
    fclose(outfp);
    return 0;
}


