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
    int num = 1;
    char c_test = 'f' ; 
    double doub_test = 23.7; 
    long   long_test = 33;
    /*char *s_test = "Персональные данные о работниках ОАО РТИ";*/
    char *s_test = "Animated by Ryan Woodward, choreographed by Janet Eilber, and danced by Blakeley White-McGuire.";
    char *s_test2 = "The essence of COM is a language-neutral way of implementing objects that can be used in environments";
    char *s_test4 = "An advantage of COM+ was that it could be run in.";
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
    
    fclose(in);
    printf("Вызов функции \"tioTableBegin\".\n");
    td = tioTableBegin( string, TIOSTRING, TIOSTRING, TIODOUBLE, TIOSTRING);

    /*Вызов функции заполнения таблицы*/
    printf("\nВызов функции \"tioTableRecord\".\n");
    td = tioTableRecord( td,num, s_test4, s_test4, doub_test, s_test );
    c_test = 'g' ; doub_test = 43.9 ;long_test = 43 ;
    td = tioTableRecord( td,num, s_test4, s_test4, doub_test, s_test2 );
    /*Вызов завершающей функции*/
    printf("\nВызов функции \"tioTableEnd\".\n");
    tioTableEnd( td );

    /*Освобождаем память для строки*/
    free(string);

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    return 0;

}
