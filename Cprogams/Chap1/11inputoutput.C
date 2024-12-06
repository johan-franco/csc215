#include <stdio.h>

main(argc, argv)
int argc;
char** argv;
{
    FILE *infp, *outfp;
    int c; 
    int prev;
    prev = EOF;
    if (argc != 3) {
        printf("Both input and output needed\n");
        return 1;
    }
    printf("Outputting one word from each line\n");

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

        if (c >= '0' && c<='9') {
	        prev = c;
            continue;
        }
        else if ((c == ' ' || c =='\t') {
	        prev = c;
            continue;
        }

        else if (c == '-' || c=='+') {
	        prev = c;
            continue;
        }
        else if (c == '\n') {
	        fputc(c, outfp); 
            putchar(c); 
            prev = c;
            continue;
        }
        else if([])
        fputc(c, outfp); 
        putchar(c);      
        prev = c;       
    }

    fclose(infp);
    fclose(outfp);
    return 0;
}


