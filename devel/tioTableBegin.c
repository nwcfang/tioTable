#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <tiotb.h>          /*My header*/ 

/*Table initialization*/
void* tioTableBegin( const char* format,  ... )
{
    va_list ap;
    int i;
    int jj; 
    int j;
    struct inform *datTab;
    void *extPointer;

    va_start( ap, format );

    /*Allocating memory for datTab structure*/
    if( (datTab = (struct inform*) calloc( 1, sizeof(struct inform)) ) == NULL )
    {
        fprintf( stderr, "\nError \n" );
        return NULL;
    }

    /*Count the number of columns in a table and calculate the maximum length of the column.*/
    for( i = 0; format[i] != '\n'; ++i )
    {
       ++ datTab->countLetter;
        if( (format[i] == '&') && (format[i+1]) != '&')
            ++ datTab->countColum;
    }

    printf("Count of letter %d.\nCount of colum %d.\n", datTab->countLetter,
            datTab->countColum );

    /*Allocating memory for cap*/
    if( (datTab->cap = (char**) calloc(datTab->countColum , sizeof(char*))) != NULL )
    {
        for( i = 0; i < datTab->countColum ; ++ i)
        {
            if( (datTab->cap[i] = (char*) calloc(datTab->countLetter, sizeof(char))) == NULL )
            {
                printf(" error datTab->cap[%d][]\n",i);
                return NULL;
            }
        }
    }
    else
    {
        printf("\nerror\n");
        return NULL;
    }


    /*Allocating memory for datTab->bufType*/
    if( (datTab->bufType = (int*) calloc(datTab->countColum, sizeof(int))) == NULL )
    {
        printf("\nerror *datTab->bufType\n");
        return NULL;
    }

    printf("\n");

    /*Allocating memory for pointer to the head of list*/ 
    if( (datTab->head = (cl *) malloc( sizeof(cl))) == NULL )
    {
        printf("\nError ptr\n");
        return NULL;
    }

    datTab->ptr = datTab->head;
    datTab->ptr->n = NULL;

    /*Allocating memory for ptr->s*/    
    if( (datTab->ptr->s = (void **) calloc(datTab->countColum, sizeof(void *))) == NULL )
    {
        printf("\nError ptr->s\n");
        return NULL;
    } 

    /*Writing data types to the buffer*/
    printf ("Data types: ");
    for ( i = 0; i < datTab->countColum; ++ i )
    {
        datTab->bufType[i] = va_arg(ap, int);
        printf("%i", datTab->bufType[i]);
    }

    printf("\n");

    /*Определяем имена колонок*/
    jj = 0;
    for ( i = 0; i < datTab->countColum; ++ i )
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
    for( i = 0; i < datTab->countColum; ++i )
    {
        printf("%s", datTab->cap[i]);
        printf("\n");
    }

    va_end( ap );

    extPointer = (void *) datTab;
    return extPointer;
}
