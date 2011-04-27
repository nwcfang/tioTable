
#include <stdlib.h>
#include <stdio.h>

int main()
{
    void **p;
    int dig[] = { 123, 456, 789 };
    char ch = 's';

    p = (void*) malloc( 3 * sizeof(void*) );
    printf("initialize\n");

    p[0] = (void*)&dig;
    p[1] = (void*)&ch;
    printf("assignment\n");

    int i;
    int* d = (int*)p[0];
    for (i = 0; i < 3; i++) {
    printf("dig = %d\n", ((int*)p[0])[i] );
    }
    printf("dig = %c\n", *(char*)p[1]);

    free(p);
    printf("end\n");

    return 0;
}
