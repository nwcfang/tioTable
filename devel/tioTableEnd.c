#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

#define MAX_MYSTRING 100
#define WIDTH 120           /*Общая ширина таблицы*/

/*Вывод таблицы*/
int tioTableEnd( void *td )
{
    struct inform *datTab;
    char *myString;            /*Строка*/ 
    int tmp;
    int strI;
    char strInp[50];        /*Данные переведенные в строку*/
    int i = 0, ii = 0;      /*Счетчик*/
    int cStr, cMax;         /*Счетчит строк выведеных, счетчик строк надо вывести*/ 
    int j = 0;              /*Счетчик*/
    int lenColCon;          /*Размер колонки*/
    int lenColVar;          /*Количество символов (пока не используется)*/
    void *next;             /*Указать на следующую область памяти которую надо освободить*/ 
    char *str;
    int *masStr;              /*Массив количества требуемых строк для 
                               вывода каждой ячейки строки */ 
    datTab = (struct inform *) td;
    
    /*Выделение памяти для массива символов, которые не поместились*/ 
    if( (masStr = (int *) malloc ( sizeof(int) * datTab->countColum)) == NULL )
    {
        printf("error in malloc!");
        return 1;
    }

    /*Подсчет толщены столбца в зависимости от количества столбцов*/
    lenColCon = WIDTH / datTab->countColum;   
    printf("Размер колонки = %d\n", lenColCon);  

    /*Линия*/ 
    for( i = 0; i < WIDTH; ++ i )             
    {
        if((i % lenColCon) == 0)
            printf("+");
    else
            printf("-");
    }
    printf( "+\n|" );

    /*Отображение шапки*/
    for(i = 0; i < datTab->countColum; ++ i )
    {
        printf( "%s", datTab->cap[i] );
        tmp = lenColCon - strlen(datTab->cap[i]);
        for( j = 0; j < tmp - 1; ++ j )
            printf( " " );
        printf( "|" );
    }
    printf( "\n");

    /*Линия*/ 
    for( i = 0; i < WIDTH; ++ i )             
    {
        if((i % lenColCon) == 0)
            printf("+");
        else
            printf("-");
    }
    printf( "+\n" );

    datTab->ptr = datTab->head;

    if( (myString = calloc(MAX_MYSTRING, sizeof(char))) == NULL )
    {
        printf("error in calloc");
    }

    /*Отображение ячеек данных*/
    while( 1 )
    {
        /*Условие выхода из цикла*/ 
        if( datTab->ptr->n == NULL )         
            break;


         /*Нужно 1) создать бесконечный цикл пока не выведет все строчки потом уже переходить на следующий узел
          * 2) подсчет максимального вывода строк
          * 3) заполнять массив |2|3|4|3|
          * 4) счетчик для уже выведеных строчек
          */ 
        


        
        for( i = 0; i < datTab->countColum; ++ i  )
        {
            strI = 0;
            switch( datTab->bufType[i])
            {
            case 1:
                if(cStr = 1 )
                {
                    printf( "|%c", *(char *)datTab->ptr->s[i]);
                    sprintf( myString, "%c", *(char *)datTab->ptr->s[i] );
                }
                break;
            case 2:
                printf("|%.2f", *(double *)datTab->ptr->s[i]);
                sprintf( myString, "%.2f", *(double *)datTab->ptr->s[i] );
                break;
            case 3:
                printf("|%ld", *(long *)datTab->ptr->s[i]);
                sprintf( myString, "%ld", *(long *)datTab->ptr->s[i] );
                break;
            case 4:
                printf("|");
                while( ((char *)datTab->ptr->s[i])[strI] != '\0' )
                {
                   printf("%c", ((char *)datTab->ptr->s[i])[strI] );
                   ++ strI;
                }
                sprintf(myString, "%s", (char *)datTab->ptr->s[i] );
                break;
            default:
                printf( "Ошибка!" );
                return 1;
            }
            tmp = lenColCon - strlen(myString) - 1;
            for( j = 0; j < tmp; ++ j )
                printf( " " );
        } 
        printf("|");
        printf("\n");

        /*for(j = 0; j < 2; ++ j)*/
        /*{*/
            /*j = 2;*/
            /*for(ii = 0; ii < datTab->countColum; ++ ii)*/
            /*{*/
                /*if(masStr[ii] != 0)*/
                /*{*/
                    /*while((strI < (((lenColCon -1) * j))) && ( ((char *)datTab->ptr->s[ii])[strI] != '\0' ))*/
                    /*{*/
                        /*[>printf("#%d#",strI);<]*/
                        /*printf("%c", ((char *)datTab->ptr->s[ii])[strI] );*/
                        /*++ strI;*/
                        /*-- masStr[ii];*/
                    /*}*/
                    /*printf("\n");*/

                /*}*/
            /*}*/
        /*}*/

        /*Линия*/ 
        for( i = 0; i < WIDTH; ++ i )             
        {
            if((i % lenColCon) == 0)
                printf("+");
            else
            printf("-");
        }
        printf( "+\n" );
 
        datTab->ptr = datTab->ptr->n;
    }
    free(myString);
    /*Вывод строки таблицы*/

    printf("\n");

    /*Освобождаем память для masStr*/ 
    free(masStr);

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
            if(datTab->ptr->n != NULL)
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


