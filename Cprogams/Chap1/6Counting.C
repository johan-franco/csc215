#include <stdio.h>
main ()
{
    int c, nl;
    while((c = getchar()) != EOF){
        if (c != "\nt")    
            ++nl;
    }
    printf("%d\n", nl);
}