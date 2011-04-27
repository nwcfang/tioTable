#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *str;
    float i = 3.4;
    str = (char*) calloc (10, sizeof(char));
    sprintf( str, "%.2f", i );
    printf( "%s", str );
    return  0;
}
