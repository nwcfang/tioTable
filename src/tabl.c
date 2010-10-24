#include <stdio.h>
#define MAXLENWORD 30
/*Функция для вывода таблицы с стролбцами "Наименования" и "Цифры"*/
int tabl( char** arStr_f, int* dis_f, const int countString )
{

    int i = 0, j = 0, leftJ = 0, rightJ = 0, generalJ = 0, sch = 0, len = 0;

        /*Рисование названий колонок*/
        printf("|--------------------------------------------------|------------------|\n");
        printf("|                      Название                    |      Цифры       |\n");
        printf("|--------------------------------------------------|------------------|\n");

        /*Вывод строки таблицы*/
        //printf("%d",countString);
        for( i = 0; i < countString; ++ i )
        {
            printf("|");

            leftJ = 0;
            sch = 0;
            rightJ = 0;
            //while( arStr_f[i][leftJ] != '\n'  )
            while( 1 )
            {
                rightJ = leftJ + 1;
                while( (arStr_f[i][rightJ] != ' ') && (arStr_f[i][rightJ] != EOF ) &&  ( arStr_f[i][rightJ] != '\n') )
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
                    //printf("%18d|\n|", dis_f[i] );

                    //printf("пренос\n|");
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

        }
    return 0;
}


