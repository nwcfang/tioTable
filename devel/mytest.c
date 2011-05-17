#include <stdio.h>
#include <stdlib.h>

int main()
{

    void **ykaz;
    int i = 4;
    char c = 'd';

    ykaz = (void **) calloc(3, sizeof(void *));

    ykaz[0] = (void *)&i; 
    ykaz[1] = (void *)&c;
    printf("%d %c", *(int *)ykaz[0],*(char *)ykaz[1]);
    free(ykaz);
    return 0;
}
