#include <stdio.h>
#include <stdlib.h>

int main ()
{
    void **p;
    int in = 5;
    char ch = 'd';

    p = (void **) calloc (2, sizeof(void *));

    p[0] = (void *) &in;
    p[1] = (void *) &ch;

    printf("%d\n", ((int*)p[0])[0]);
    printf("%c\n", ((char*)p[1])[0]);


    return 0;
}
