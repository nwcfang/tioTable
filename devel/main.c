#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tiotb.h>
#define TIOCHAR 1
#define TIODOUBLE 2
#define TIOLONG 3
#define TIOSTRING 4

/*Тест функция */
int main( )
{
    FILE *in;
    char *string = NULL, **cap = NULL;
    int  *bufType = NULL;
    int i;
    /*Выделение памяти для string*/
    if( (string = (char*) calloc( 50, sizeof(char)) ) != NULL )
        printf("\nok string\n");
    else
    {
        fprintf( stderr, "\nError string\n" );
        return 1;
    }

    if( (in = fopen( "../in2.txt", "rt" )) == NULL )
    {
        fprintf( stderr, "Cannot open input file.\n" );
        return 1;
    }

    /*Считываем строку содержащую названия колонок
      (name&number&&class&state)*/
    fgets( string, 50, in);

    /*Вызов функции иницилиализации таблицы*/
    tioTableBegin(  cap, bufType, string, TIOCHAR, TIODOUBLE, TIOSTRING, TIOLONG );
    tioTableEnd( cap, bufType );

    free(string);
    free(bufType);
    /*не уверен что работает*/
    for( i = 0; cap[i]; ++ i )
        free(cap[i]);

    return 0;

}
