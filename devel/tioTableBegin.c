#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <tiotb.h>

/*Функция инициализирует таблицу(задаётся шапка, и типы данных для каждого столбца)*/
/* Нужно пределать: чтобы типы сообщалиль в функцию словами а не констанктами
                    передавать в функцию указатели для наименований колонок и
                    типов данных*/
int tioTableBegin( struct inform *datTab, const char* format,  ... )
{
    va_list ap;
    int i, jj, j;

    va_start( ap, format );

    /*Подсчет колличества колонок в таблице, максимальной длины колонки.*/
    for( i = 0; format[i] != '\n'; ++i ) /*  \n - проверить работает ли  */
    {
        datTab->countLetter;
                if( (format[i] == '&') && (format[i+1]) != '&')
        {
            ++datTab->countColum;
        }
    }

    for ( i = 0; i < datTab->countColum + 1; ++ i )
    {
        datTab->bufType[i] = va_arg(ap, int); /* Возможно, будет нужно поменять int на void*//*Нафиг?*/
        printf("%i", datTab->bufType[i]);
    }
    printf("\n");

    jj = 0;
    for ( i = 0; i < datTab->countColum + 1; ++i )
    {
        j = 0;
        while( (format[jj] != '&') && (format[jj] != '\n') )
        {

            datTab->cap[i][j] = format[jj];
            if ( (format[jj+1] == '&') && (format[jj+2] == '&')  )
            {
                datTab->cap[i][j+1] = '&';
                ++j;
                jj = jj + 2;
            }
            ++j;
            ++jj;
        }
        ++jj;
    }
    /* Вывод на экран содержимое datTab.cap[i][j], в котором содержатся названия колонок */
    for( i = 0; i <= datTab->countColum; ++i )
    {
        for( j = 0; j < datTab->countLetter; ++j)
            printf("%c", datTab->cap[i][j]);
        printf("\n");
    }
    va_end( ap );

    return 0;
}
