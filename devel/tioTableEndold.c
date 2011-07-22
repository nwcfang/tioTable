#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

#define WIDTH 120           /*Общая ширина таблицы*/

char *myStrncpy(char *dest, char *src, int start, int end)
{
    int i;
    int j;
    for (i = start ; i < end && src[i] != '\0' ; i++)
    {
        dest[j] = src[i];
        ++ j;
    }
    for ( ; j <= end ; j++)
        dest[j] = '\0';

    return dest;
}

/*Вывод таблицы*/
int tioTableEnd( void *td )
{
    struct inform *datTab;
    char *myString;             /*Строка*/ 
    int tmp;
    int strI;
    int strIend;                /*До этого числа будет выводится строка,
                                потом будет переходить на новую строчку*/ 
    int i = 0;                  /*Счетчик*/

    int cStr, cMax;             /*Строк выведеных, строк надо вывести*/ 
    
    int j = 0;                  /*Счетчик*/
    int lenColCon;              /*Размер колонки*/
    void *next;                 /*Указать на следующую область памяти которую надо освободить*/ 
    int *masCountCells;         /*Массив содержащий количество дополнительных ячеек,
                                которые могут потребоваться в случае, если строка
                                не помещается в одну ячейку*/ 
    char * tmp2;                /*Ввел чтобы проще было прочесть*/ 

    datTab = (struct inform *) td;

    /*Выделение памяти для *masCountCells*/ 
    if( (masCountCells = (int *) calloc (datTab->countColum, sizeof(int))) == NULL )
    {
        printf("error");
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

    if (lenColCon <= 0)
    {
        fputs("Wrong string length", stderr);
        return 1;
    }

    if( (myString = (char *) malloc(lenColCon)) == NULL )
    {
        printf("error in calloc");
        return 1;
    }

    /*Отображение ячеек данных*/
    while( 1 )
    {
        /*Условие выхода из цикла*/ 
        if( datTab->ptr->n == NULL )         
            break;

        cStr = 0;
        cMax = 0;

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
                         * правельно отобразить данную ящейку таблицы (cMax)*/ 
                        if( masCountCells[i] > cMax )
                            cMax = masCountCells[i];
                    }
                    printf("|");
                    if(cStr <= masCountCells[i])
                    {
                        strI = (lenColCon - 1) * cStr;
                        strIend = (lenColCon - 1)  * (cStr + 1) ;
                        tmp2 = (char *)datTab->ptr->s[i];
                        myStrncpy( myString, (char *)datTab->ptr->s[i], strI, strIend);
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
        } while(cStr < cMax + 1);
        

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

    //======================================

    free(myString);

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
