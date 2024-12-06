#include <stdio.h>
/*nums and spaces are ignored but other 'words' in the same line are outputted*/

check(p)
int p; 
{
    if (p >= '0' && p <= '9') {
        return 1;
    }
    if (p == ' ' || p == '\t') {
        return 2;
    }
    if (p == '-' || p == '+') {
        return 1;
    }
    return 0;
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

        if (check(c)==1){
            prev = c;
            continue;
        }
        else if (c == '\n') {
	        fputc(c, outfp); 
            putchar(c); 
            prev = c;
            continue;
        }
        else if( check(prev) == 0 && check(c) == 2) {
            /*while ((c = fgetc(infp)) != '\n' || (c = fgetc(infp)) != EOF){
                continue;
            }*/
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


