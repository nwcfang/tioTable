#include <stdio.h>
#define MAXLENWORD 30
/*Функция для вывода таблицы с стролбцами */
int tioTableEnd(char **cap, int *bufType /*char** arStr_f, int* dis_f, const int countString*/ )
{

    int i = 0, j = 0, leftJ = 0, rightJ = 0, generalJ = 0, sch = 0, len = 0;

        /*Рисование названий колонок*/
    for( i = 0; cap[i][0]; ++ i )
    {
        printf("%d", i);
    }
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
    return 0;
}


