#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
/*Функция инициализирует таблицу(задаётся шапка, и типы данных для каждого столбца)*/
/* Нужно пределать: чтобы типы сообщалиль в функцию словами а не констанктами
                    передавать в функцию указатели для наименований колонок и
                    типов данных
                    cap и bufType перенести в main, следовательно countLetter и countColum тоже
                    и прийдется их тоже сообщать в функции, либо придумать как не использовать
                    countLetter и countColum*/
/*indexCap - элементы шапки*/
int tioTableBegin( char** cap, int* bufType, const char* format,  ... )
{
    va_list ap;
    int i, jj, j, countLetter = 0, countColum = 0;
   // char **cap = NULL;
   // int *bufType = NULL;

    va_start( ap, format );
    /*Подсчет колличества колонок в таблице, максимальной длины колонки*/
    for( i = 0; format[i] != '\n'; ++i )
    {
        ++countLetter;
        if( (format[i] == '&') && (format[i+1]) != '&')
        {
            ++countColum;
        }
    }
    /*Выделение памяти под шапку*/
    if( (cap = (char**) calloc((countColum + 1), sizeof(char*))) != NULL )
    {
        printf("\nok **cap\n");
        for( i = 0; i < (countColum + 1); ++ i)
        {
            if( (cap[i] = (char*) calloc(countLetter, sizeof(char))) != NULL )
                printf(" ok cap[%d][]\n",i);
            else
            {
                printf(" error cap[%d][]\n",i);
                return 1;
            }
        }
    }

    else
    {
        printf("\nerror **cap\n");
        return 1;
    }

    if( (bufType = (int*) calloc((countColum +1), sizeof(int))) != NULL )
        printf("\nok *bufType\n");
    else
    {
        printf("\nerror *bufType\n");
        return 1;
    }

    for ( i = 0; i <= countColum; ++i )
    {
        bufType[i] = va_arg(ap, int);
        printf("%i", bufType[i]);
    }
    printf("\n");

    jj = 0;
    for ( i = 0; i <= countColum; ++i )
    {
        j = 0;
        while( (format[jj] != '&') && (format[jj] != '\n') )
        {

            cap[i][j] = format[jj];
            if ( (format[jj+1] == '&') && (format[jj+2] == '&')  )
            {
                cap[i][j+1] = '&';
                ++j;
                jj = jj + 2;
            }
            ++j;
            ++jj;
        }
        ++jj;
    }
    /* вывод на экран содержимое cap[i][j], в котором содержатся названия колонок */
    for( i = 0; i <= countColum; ++i )
    {
        for( j = 0; j < countLetter; ++j)
            printf("%c", cap[i][j]);
        printf("\n");
    }
    va_end( ap );

    /*for( i = 0; i < (countColum + 1); ++i )
        free(cap[i]);*/
    return 0;
}
