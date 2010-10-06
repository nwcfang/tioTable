#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMLINE 30      //число строк в файле
#define NUMCHAR 80      //число символов в каждой строке 

/*
 * Пришлось добавить ещё один параметр который нам говорит о колличестве
 * полученых из файла.
 */
/*Функция для вывода таблицы с стролбцами "Наименования" и "Цифры"*/
int f( char** arStr_f, int* dis_f, const int countString )
{

    int i = 0, j = 0, jj = 0, sch = 0, col_char = 0, len = 0; // кто что значит хз!!!!!

    /*Рисование названий колонок*/
    printf("|--------------------------------------------------|------------------|\n");
    printf("|                      Название                    |      Цифры       |\n");
    printf("|--------------------------------------------------|------------------|\n");

    /*Вывод строки таблицы*/
    for (i = 0; i < countString; i++)       // это одно из тех мест где у тебя
    {                                       // могла упать программа ( сверся
        printf("|");                        // со своей версией)

        j = 0;          // зачем два раза подряд инициализируешь?
        sch = 0;
        while (arStr_f[i][j] != '\n'  )
        {
            if (sch < 50)
            {
                printf("%c",arStr_f[i][j]);
                ++j;
                ++sch;
            }
            else
            {
                printf("|                  |\n|");
                sch = 0;
            }
        }

        len = 50 - sch;
        for (j = 0; j < len; j++)
            printf(" ");

        printf("|");
        printf("%18d|", dis_f[i]);
        printf("\n|--------------------------------------------------|------------------|\n");

    }

    return 0;
}

int main ()
{
    char** arStr = NULL;
    FILE *in;
    int i,j;
    int* dis = NULL;
    int countString = 0;        // колличество строк в файле

    /*
     * Ошибка была в неправильном способе выделения памяти для массива строк.
     * твой код:
     * arStr = (char *) calloc(numb_line, sizeof(char))
     * как видишь ты выделял память размером numb_line * sizeof(char)
     * причём всё это дело ты применял к arStr с приведением к (char*)
     * в то время, как arStr имеет тип char**
     */
    /*Выдиление памяти под двухмерный указатель для колонки "Наименования"*/
    if( ( arStr = (char**) calloc(NUMLINE, sizeof(char*)) ) != NULL )
    {
        for( i = 0; i < NUMLINE ; ++i )
        {
            if( (arStr[i] = (char*) calloc(NUMCHAR, sizeof(char))) == NULL )
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
    if( (in = fopen( "in.txt", "rt" )) == NULL )
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

    f(arStr, dis, countString );
    for( i=0; i < NUMLINE; ++i )
        free( arStr[i] );
    free (arStr);
    free( dis );        // НЕ ЗАБЫВАЙ освобождать память!!! хоть зарубки ставь
                        // сколько malloc'ов столько и free

    return 0;
}
