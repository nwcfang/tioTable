#include <stdio.h>
#include <stdlib.h>
int main()
{
    void **d;
    char ch = 'v';

    d = (void **) malloc (sizeof(void *));
    d[0] = (void *) &ch;
    printf("(%c) %c\n", ch, *(char *) d[0] );
    
    free(d);
    return 0;
}
