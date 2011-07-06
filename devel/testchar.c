#include <stdio.h>
#include <stdlib.h>
int main ()
{
    char ch = 'f';
    void* chh;
    char* c = (char*) malloc(sizeof(char));

    *c = ch;
    chh = (void*)c;

    printf("%c\n", *(char*)chh);

    free(c);
    return 0;
}
