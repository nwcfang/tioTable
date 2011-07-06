#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

#define MAX_MYSTRING 100
#define WIDTH 120           /*Общая ширина таблицы*/




/*Вывод таблицы*/
int tioTableEnd( void *td )
{
    /*====================================================================================*/ 
    struct inform *datTab;
    char *myString;            /*Строка*/ 
    int tmp;
    int strI;
    int strIend;            /*До этого числа будет выводится строка,
                            потом будет переходить на новую строчку*/ 
    int i = 0, ii = 0;      /*Счетчик*/

    int cStr, cMax;         /*Счетчит строк выведеных, счетчик строк надо вывести*/ 
    
    int j = 0;              /*Счетчик*/
    int lenColCon;          /*Размер колонки*/
    void *next;             /*Указать на следующую область памяти которую надо освободить*/ 
    char *str;
    int fMax;
    int *masCountCells;      /*Массив содержащий количество дополнительных ячеек,
                                которые могут потребоваться в случае, если строка
                                не помещается в одну ячейку*/ 
    /*====================================================================================*/ 

    /*Выделение памяти для *masCountCells*/ 
    if( (masCountCells = (int *) calloc (datTab->countColum, sizeof(int))) == NULL )
    {
        printf("error");
        return 1;
    }

    datTab = (struct inform *) td;
    
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

    if( (myString = (char *) calloc(MAX_MYSTRING, sizeof(char))) == NULL )
    {
        printf("error in calloc");
    }

    /*Отображение ячеек данных*/
    while( 1 )
    {
        /*Условие выхода из цикла*/ 
        if( datTab->ptr->n == NULL )         
            break;

        cStr = 0;
        cMax = 0;

         /* Нужно   1) создать бесконечный цикл пока не выведет все строчки потом уже переходить на следующий узел
          *         2) подсчет максимального вывода строк
          *         3) заполнять массив |2|3|4|3|
          *         4) счетчик для уже выведеных строчек
          */

        /*Пока все строки полностью не выведутся*/ 
        do
        {
            strI = 0;
            /*Цикл выводит одну ячейку таблицы*/ 
            for( i = 0; i < datTab->countColum; ++ i  )
            {
                switch( datTab->bufType[i])
                {
                case 1:
                    if(cStr == 0 )
                    {
                        printf( "|%c", *(char *)datTab->ptr->s[i]);
                        sprintf( myString, "%c", *(char *)datTab->ptr->s[i] );
                    }
                    else
                        printf("|");
                    break;
                case 2:
                    if(cStr == 0)
                    {
                        printf("|%.2f", *(double *)datTab->ptr->s[i]);
                        sprintf( myString, "%.2f", *(double *)datTab->ptr->s[i] );
                    }
                    else
                        printf("|");
                    break;
                case 3:
                    if(cStr == 0)
                    {
                        printf("|%ld", *(long *)datTab->ptr->s[i]);
                        sprintf( myString, "%ld", *(long *)datTab->ptr->s[i] );
                    }
                    else
                        printf("|");
                    break;
                case 4:
                    if(cStr == 0)
                    {
                        masCountCells[i] = strlen((char *)datTab->ptr->s[i])/lenColCon;
                        /* Для вычисления сколько всего понадобится строк чтобы 
                         * правельно отобразить данную строку таблицы (cMax)*/ 
                        if( masCountCells[i] > cMax )
                            cMax = masCountCells[i];
                    }
                    printf("|");
                    if(cStr <= masCountCells[i])
                    {
                        strI = (lenColCon - 1) * cStr;
                        strIend = lenColCon  * (cStr + 1) -1;
                        strncpy( myString, (char *)datTab->ptr->s[i] + strI, strIend );
                        printf("%s", myString);
                    }
                    break;
                default:
                    printf( "Ошибка!" );
                    return 1;
                }
                
                tmp = lenColCon - strlen(myString) - 1;
                for( j = 0; j < tmp; ++ j )
                    printf( " " );
                for( j = 0; j < lenColCon; ++ j )
                    myString[j] = '\0';
            }
            ++ cStr;
            printf("|\n");
        } while(cStr < cMax);
        

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

    /*Тест*/ 
    for(i = 0; i < datTab->countColum; ++ i)
        printf("%d", masCountCells[i]);
    printf("\n%d", cMax);
    //======================================
    free(myString);

    printf("\n");

    /*Освобождаем память masCountCells*/ 
    free(masCountCells);
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


