#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>


#define WIDTH 120           /*Общая ширина таблицы*/
#define STRINGLEN 1000      /*Максимальная длина строки в одной ячейке таблицы*/ 
#define MAXCOUNTSTR 200     /*Максимальное число строк в таблице*/

/*Вывод таблицы*/
int tioTableEnd( void *td )
{
    struct inform *datTab;
    char strInp[50];        /*Данные переведенные в строку*/
    int i = 0;              /*Счетчик*/
    int j = 0;              /*Счетчик*/
    int leftJ = 0, rightJ = 0, generalJ = 0, sch = 0, len = 0;
    int lenColCon;          /*Размер колонки*/
    int lenColVar;          /*Количество символов (пока не используется)*/
    int colSpace;

    datTab = (struct inform *) td;

    /*Подсчет толщены столбца в зависимости от количества столбцов*/
    lenColCon = (WIDTH - 1) / datTab->countColum;   /*- 1 для правельного отображения таблицы*/
    printf("Размер колонки = %d\n", lenColCon + 1);   
    for( i = 0; i < (WIDTH + 1); ++ i )             /*+ 1 для правельного отображения таблицы*/ 
        printf("-");
    printf( "\n|" );

    /*Отображение шапки*/
    for(i = 0; i < datTab->countColum; ++ i )
    {
        printf( "%s", datTab->cap[i] );
        for( j = 0; j < (lenColCon - strlen(datTab->cap[i])); ++ j )
            printf( " " );
        printf( "|" );
    }
    printf( "\n" );
    for( i = 0; i < (WIDTH + 1); ++ i )             /*+ 1 для правельного отображения таблицы*/ 
        printf("-");
    printf( "\n|" );

    /*Отображение ячеек данных*/ 
    for( i = 0; i < datTab->countColum; ++ i  )
    {
        
        switch( datTab->bufType[i] )
        {
            case 1:
                sprintf( strInp, "%c", *(char *)datTab->data[i][0] );
                printf( "%c", *(char *)datTab->data[i][0] );
                break;

            case 2:
                sprintf( strInp, "%.2f", *(double *)datTab->data[i][0] );
                printf( "%s", strInp );
                break;

            case 4:
                sprintf( strInp, "%d", *(int *)datTab->data[i][0] );
                printf( "%s", strInp);
                break;

            default:
                printf("Это что а тип?");
                break;
        }
        for( j = 0; j < (lenColCon - strlen(strInp)); ++ j )
            printf( " " );
        printf( "|" );
        
    
    }
    printf("\n");
    for( i = 0; i < (WIDTH + 1); ++ i )             /*+ 1 для правельного отображения таблицы*/ 
        printf("-");
    
    
    /*Вывод строки таблицы*/

/*        for( i = 0; i < countString; ++ i )
        {
            printf("|");

            leftJ = 0;
            sch = 0;
            rightJ = 0;
            while( 1 )
            {
                rightJ = leftJ + 1;
                while( (arStr_f[i][rightJ] != ' ') && (arStr_f[i][rightJ] != EOF )
                        &&  ( arStr_f[i][rightJ] != '\n') )
                {
                   ++rightJ;
                }

                if( (sch + (rightJ-leftJ)) > 50)
                {
                    len = 50 - sch- 2;
                    for( j = 0; j < len; j++ )
                        printf(" ");

                    printf("|");
                    printf("                  |\n|");
                    sch = 0;
                }

                for( generalJ = leftJ ; generalJ < rightJ; ++generalJ )
                {
                    printf( "%c", arStr_f[i][generalJ] );
                }
                sch += (rightJ - leftJ);
                if( arStr_f[i][rightJ] == '\n')
                    break;
                printf(" ");
                leftJ = ++rightJ;
            }


            len = 50 - sch;
            for( j = 0; j < len; j++ )
                printf(" ");

            printf("|");
            printf("%18d|", dis_f[i] );
            printf("\n|--------------------------------------------------|------------------|\n");

        }*/

    printf("\n");

    /*Освобождаем память для шапки и data*/
    for( i = 0; i < datTab->countColum; ++ i )
        free(datTab->cap[i]);
    free( datTab->cap );
    for( i = 0; i < datTab->countColum; ++ i )
        free(datTab->data[i][0]);
    free( datTab->data );

    /*Освобождаем память для буффера с типами данных*/
    free(datTab->bufType);

    /*Освобождаем память для структуры*/
    free(datTab);

    return 0;
}


