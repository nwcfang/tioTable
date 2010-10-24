#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fnbl.h"

#define NUMLINE 30      //число строк в файле
#define NUMCHAR 80      //число символов в каждой строке



int main ()
{
    char** arStr = NULL;
    FILE *in;
    int i,j;
    int* dis = NULL;
    int countString = 0;        // колличество строк в файле

    /*Выдиление памяти под двухмерный указатель для колонки "Наименования"*/
    if( ( arStr = (char**) calloc( NUMLINE, sizeof(char*)) ) != NULL )
    {
        for( i = 0; i < NUMLINE ; ++i )
        {
            if( (arStr[i] = (char*) calloc( NUMCHAR, sizeof(char))) == NULL )
            {
                printf("error calloc **srt!");
                return -1;
            }
        }
    }
    else
    {
        printf("error calloc *str!");
        return -1;
    }

    /*Выделение памяти под указатель для колонки цифр*/
    if( (dis = (int*) calloc(NUMLINE, sizeof(int))) == NULL )
    {
        printf("Error *dis!\n");
        return -1;
    }

    /*Отрить файл для чтения*/
    if( (in = fopen( "../in.txt", "rt" )) == NULL )
    {
        fprintf(stderr, "Cannot open input file.\n");
        return 1;
    }
    /*
     * я переписал то что ты назвал считыванием из файла
     * потестируй на маленьких програмках,свой и мой код
     * должен впринципе понять что к чему.
     */
    /*Считываем и занисим строки в область памяти с указателем **arStr из файла*/
    i = 0;
    char buf[NUMCHAR];
    while( !feof(in) )
    {
        fgets( buf, NUMCHAR, in );
        // Здесь я перестраховался на случай если строка в файле будет больше
        // чем NUMCHAR
        strncpy( arStr[countString], buf, NUMCHAR );
        ++countString;      // тот самый счётчик кол-ва строк в файле
    }
    fclose( in );

    for (i = 0; i < NUMLINE; ++i)
        dis[i] = 123;

    tabl( arStr, dis, 4 );
    for( i=0; i < NUMLINE; ++i )
        free( arStr[i] );
    free ( arStr );
    free( dis );        // НЕ ЗАБЫВАЙ освобождать память!!! хоть зарубки ставь
                        // сколько malloc'ов столько и free

    return 0;
}
