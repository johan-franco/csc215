#include <stdio.h>
/*nums and spaces are ignored but other 'words' in the same line are outputted*/

main(argc, argv)
int argc;
char** argv;
{
    FILE *infp, *outfp;
    int c, prev, count, linenum;
    linenum = 0;
    c =0;
    prev = EOF;
    char** val;

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
        if((c = fgetc(infp)) == '\n') {
            count = 0;
            linenum++;
        }
        
        val[linenum][count] = c;
        printf("%s\n", val[linenum][count]);
        count++;
        printf("%s\n", c);

    }

    fclose(infp);
    fclose(outfp);
    return 0;
}


