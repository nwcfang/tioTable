#include <stdio.h>
#include <stdlib.h>
int main( )
{
    void *p;
    int i;
    int h = 5564;
    char g = 'c';
    p = (void *) calloc (2, sizeof(void *));
    printf("%d %d", p[0], p[1]);
    p = (void*) h;
    printf("%d ", *(int*) p);
    free(p);
    return 0;
}
