/*=============================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numb_line 5//число строк в файле
#define numb_char 80//число символов в каждой строке 
/*=============================*/



/*=============================*/
/*Функция для вывода таблицы с стролбцами "Наименования" и "Цифры"*/
int f(char** arStr_f, int* dis_f)
{

	int i = 0, j = 0, jj = 0, sch = 0, col_char = 0, len = 0;
        
    /*Рисование названий колонок*/
    printf("|--------------------------------------------------|------------------|\n");  
    printf("|                      Название                    |      Цифры       |\n");
    printf("|--------------------------------------------------|------------------|\n");
    
    /*Вывод строки таблицы*/
	for (i = 0; i < numb_line; i++)
	{
		printf("|");
        
        j = 0;
        sch = 0;
        while (arStr_f[i][j] != '\n')
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
/*=============================*/



/*=============================*/
int main ()
{

	char** arStr = NULL;
	FILE *in;
	int i,j;
	int* dis = NULL;

    /*Очистка экрана*/
	for (i = 0; i < 50; i ++)
		printf("\n");

    /*Выдиление памяти под двухмерный указатель для колонки "Наименования"*/
	if ((arStr = (char *) calloc(numb_line, sizeof(char))) != NULL)
	{
		printf("calloc *str succ!\n");
		for (i = 0; i < numb_line ; i ++)
		{
			if ((arStr[i]  = (char *) calloc(numb_char, sizeof(char))) == NULL)
			{
				printf("error calloc **srt!");
				return 1;
			}
		}
		printf("calloc **str succ!\n");
	}
	else
	{
		printf("error calloc *str!");
		return 1;
	}

    /*Выделение памяти под указатель для колонки цифр*/
	if ((dis = (int *) calloc(numb_line , sizeof(int))) != NULL)
		printf("calloc *dis succ!\n");

    /*Отрить файл для чтения*/
	if ((in = fopen("in.txt", "rt")) == NULL)
	{
		fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}

    /*Считываем и занисим строки в область памяти с указателем **arStr из файла*/
	for (i = 0; i < numb_line; i ++)
		fgets(arStr[i], numb_char, in);

	for (i = 0; i < numb_line; i ++)
		dis[i] = 123;
	printf("\n");

	f(arStr, dis);
    for(i=0;i<numb_line;i++)
        free(arStr[i]);
	free (arStr);
    return 0;
}
/*=============================*/
