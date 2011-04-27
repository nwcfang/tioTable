#include <stdio.h>
#include <stdlib.h>
int main ( )
{
    void **p;
    int i;
    int h = 3234;
    p = (void **) calloc ( 3, sizeof(void *) );
    for ( i = 0; i < 3; ++i )
    {
        p[i] = (void *) calloc ( 3, sizeof(void *) );
    }
    p[0] = (void*)&h;
    printf("%d", *(int*)p);
    for ( i = 0; i < 3; ++i ) 
        free(p[i]);
    free(p);
    return 0;
}
