#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h> /*Мой хедер*/

#define TIOCHAR     1 
#define TIODOUBLE   2
#define TIOLONG     3
#define TIOSTRING   4

#define MSRTLEN 50/*Максимальная длина строки с названиями колонок*/

/*Тест функция */

int main( )
{
    FILE *in;
    void *td;
    char *string = NULL;
    int i;


    printf("\n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    /*Выделение памяти для строки с названием колонок*/
    if( (string = (char*) calloc( MSRTLEN, sizeof(char)) ) == NULL )
    {
        fprintf( stderr, "\nError string\n" );
        return 1;
    }

    /*Открываем файл для чтения*/
    if( (in = fopen( "../in2.txt", "rt" )) == NULL )
    {
        fprintf( stderr, "Cannot open input file.\n" );
        return 1;
    }

    printf("Считываем строку содержащую названия колонок.\n");
    /*(name&number&&class&state)*/
    fgets( string, MSRTLEN, in);
    printf( "%s\n", string );

    printf("Вызов функции \"tioTableBegin\".\n");
    td = tioTableBegin( string, TIOCHAR, TIODOUBLE, TIOSTRING );

    /*Вызов функции заполнения таблицы*/
    printf("\nВзов функции \"tioTableRecord\".\n");
    td = tioTableRecord( td );

    /*Вызов завершающей функции*/
    printf("\nВызов функции \"tioTableEnd\".\n");
    tioTableEnd( td );

    /*Освобождаем память для строки*/
    free(string);

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    return 0;

}
