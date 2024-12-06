#include <stdio.h>
/*nums and spaces are ignored but other 'words' in the same line are outputted*/

count(p, infp)
int p; 
FILE *infp;
{
    int count;
    while ((p = fgetc(infp)) != EOF || (p = fgetc(infp)) != '\n') {
        count++;
    }
    return count;
}

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
    printf("Attempting counting char and input");

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
        fputc(count(c,infp),outfp);
        putchar(c);
        prev = c; 
        if (count(c,infp) < 10){
            printf("Working");
        }
    }

    fclose(infp);
    fclose(outfp);
    return 0;
}


