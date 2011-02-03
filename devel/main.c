#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

#define TIOCHAR 1 /*Типы данных временно представлены в виде констант*/
#define TIODOUBLE 2
#define TIOLONG 3
#define TIOSTRING 4

#define MSRTLEN 50/*Максимальная длина строки с названиями колонок*/

/*Тест функция */
/*Требуется создать структурный тип данных*/
/*Освободить память! Не забыть!*/

int main( )
{
    FILE* in;
    struct inform *datTab;
    char* string = NULL;
    int i;

    /*Выделение памяти для указателя на структуру*/
    if( (datTab = (struct inform*) calloc( 1, sizeof(struct inform)) ) == NULL )
    {
        fprintf( stderr, "\nError \n" );
        return 1;
    }
    datTab->countLetter = 0;
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

    /*Выделение памяти под шапку.*/
    if( (datTab->cap = (char**) calloc((datTab->countColum + 1), sizeof(char*))) != NULL )
    {
        printf("\nok **datTab->cap\n");
        for( i = 0; i < (datTab->countColum + 1); ++ i)
        {
            if( (datTab->cap[i] = (char*) calloc(datTab->countLetter, sizeof(char))) != NULL )
                printf(" ok *datTab->cap[%d][]\n",i);
            else
            {
                printf(" error datTab->cap[%d][]\n",i);
                return 1;
            }
        }
    }
    else
    {
        printf("\nerror **datTab->cap\n");
        return 1;
    }

    /*Выделение памяти для типов данных. */
    if( (datTab->bufType = (int*) calloc((datTab->countColum +1), sizeof(int))) != NULL )
        printf("\nok *datTab->bufType\n");
    else
    {
        printf("\nerror *datTab->bufType\n");
        return 1;
    }

    /*Считываем строку содержащую названия колонок
      (name&number&&class&state)*/
    fgets( string, MSRTLEN, in);


    /*Вызов функции иницилиализации таблицы*/
    tioTableBegin( datTab, string, TIOCHAR, TIODOUBLE, TIOSTRING, TIOLONG );

    /*tioTableEnd( cap, bufType );*/
    /*Освобождаем память для строки*/
    free(string);
    /*Освобождаем память для шапки*/
    /*Не уверен что работает*/
    for( i = 0; datTab->cap[i]; ++ i )
       free(datTab->cap[i]);
    /*Освобождаем память для буффера с типами данных*/
    free(datTab->bufType);

       return 0;

}
