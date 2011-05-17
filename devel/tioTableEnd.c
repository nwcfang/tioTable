#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>


#define WIDTH 120           /*Общая ширина таблицы*/

/*Вывод таблицы*/
int tioTableEnd( void *td )
{
    struct inform *datTab;
    char strInp[50];        /*Данные переведенные в строку*/
    int i = 0;              /*Счетчик*/
    int j = 0;              /*Счетчик*/
    /*int leftJ = 0, rightJ = 0, generalJ = 0, sch = 0, len = 0;*/
    int lenColCon;          /*Размер колонки*/
    int lenColVar;          /*Количество символов (пока не используется)*/
    void *next;             /*Указать на следующую область памяти которую надо освободить*/ 
    datTab = (struct inform *) td;

    /*Подсчет толщены столбца в зависимости от количества столбцов*/
    lenColCon = WIDTH / datTab->countColum;   /*- 1 для правельного отображения таблицы*/
    printf("Размер колонки = %d\n", lenColCon);  
    for( i = 0; i < WIDTH; ++ i ) /*+ 1 для правельного отображения таблицы*/
    {
        if((i % lenColCon) == 0)
            printf("+");
        else
            printf("-");
    }
    printf( "+\n|" );

    /*[>Отображение шапки<]*/
    /*for(i = 0; i < datTab->countColum; ++ i )*/
    /*{*/
        /*printf( "%s", datTab->cap[i] );*/
        /*for( j = 0; j < (lenColCon - strlen(datTab->cap[i])); ++ j )*/
            /*printf( " " );*/
        /*printf( "|" );*/
    /*}*/
    /*printf( "\n" );*/
    /*for( i = 0; i < (WIDTH + 1); ++ i )             [>+ 1 для правельного отображения таблицы<] */
        /*printf("-");*/
    /*printf( "\n|" );*/
/*free(datTab->ptr->*/
    /*[>Отображение ячеек данных<] */
    /*for( i = 0; i < datTab->countColum; ++ i  )*/
    /*{*/
        
        
        /*for( j = 0; j < (lenColCon - strlen(strInp)); ++ j )*/
            /*printf( " " );*/
        /*printf( "|" );*/
        
    
    /*}*/
    /*printf("\n");*/
    /*for( i = 0; i < (WIDTH + 1); ++ i )             [>+ 1 для правельного отображения таблицы<] */
        /*printf("-");*/
    
    
    /*Вывод строки таблицы*/

/*       for( i = 0; i < countString; ++ i )
 *        {
 *            printf("|");
 *
 *            leftJ = 0;
 *            sch = 0;
 *            rightJ = 0;
 *            while( 1 )
 *            {
 *                rightJ = leftJ + 1;
 *                while( (arStr_f[i][rightJ] != ' ') && (arStr_f[i][rightJ] != EOF )
 *                        &&  ( arStr_f[i][rightJ] != '\n') )
 *                {
 *                   ++rightJ;
 *                }
 *
 *                if( (sch + (rightJ-leftJ)) > 50)
 *                {
 *                    len = 50 - sch- 2;
 *                    for( j = 0; j < len; j++ )
 *                        printf(" ");
 *
 *                    printf("|");
 *                    printf("                  |\n|");
 *                    sch = 0;
 *                }
 *
 *                for( generalJ = leftJ ; generalJ < rightJ; ++generalJ )
 *                {
 *                    printf( "%c", arStr_f[i][generalJ] );
 *                }
 *                sch += (rightJ - leftJ);
 *                if( arStr_f[i][rightJ] == '\n')
 *                    break;
 *                printf(" ");
 *                leftJ = ++rightJ;
 *            }
 *
 *
 *            len = 50 - sch;
 *            for( j = 0; j < len; j++ )
 *                printf(" ");
 *
 *            printf("|");
 *            printf("%18d|", dis_f[i] );
 *            printf("\n|--------------------------------------------------|------------------|\n");
 *
 *        }*/


    printf("\n");

    /*Освобождаем память для шапки и data*/
    for( i = 0; i < datTab->countColum; ++ i )
        free(datTab->cap[i]);
    free( datTab->cap );

    /*Освобождаем память для буффера с типами данных*/
    free(datTab->bufType);


    /*Освобождаем память списока, ptr->s, также, в
     *случае если есть тип строка, освобождаем строку*/  /*Не уверен что работает*/ 
    datTab->ptr = datTab->head;
    do 
    {     
        next = (void *) datTab->ptr->n;
        for( i = 0; i < datTab->countColum; ++ i )
        {
            if((datTab->bufType[i] == 4) && (datTab->ptr->n != NULL))
                free(datTab->ptr->s[i]);
        }
        free(datTab->ptr->s);
        free(datTab->ptr);
        datTab->ptr = (cl *) next;
    } while (datTab->ptr != NULL);

    /*Освобождаем память для структуры*/
    free(datTab);

    return 0;
}


