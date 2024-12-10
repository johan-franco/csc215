#include <stdio.h>

main(argc, argv)
int argc;
char* argv[];
{
    FILE *infp;
    int ch, newpos, star, en;
    char buffer[1024];
    char temp;

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
            buffer[newpos] = '\0';
            en = newpos - 1;
            star = 0;

            while (star < en) {
                temp = buffer[star];
                buffer[star] = buffer[en];
                buffer[en] = temp;
                star++;
                en--;
            }

            printf("%s\n", buffer);
            newpos = 0;
        }
        else {
            if (newpos < 1024) {
                buffer[newpos++] = ch;
            }
        }
    }

    if (newpos > 0) {
        buffer[newpos] = '\0';

        en = newpos - 1;
        star = 0;

        while (star < en) {
            temp = buffer[star];
            buffer[star] = buffer[en];
            buffer[en] = temp;
            star++;
            en--;
        }

        printf("%s", buffer);
    }

    fclose(infp);
    return 0;
}
