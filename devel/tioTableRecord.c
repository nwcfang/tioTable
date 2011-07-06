#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <tiotb.h>

void *tioTableRecord( void *td, int num, ...  )
{
    va_list ap;
    struct inform *datTab;
    int i;
    char ch;
    double dbd;
    long ln;
    char* strn;
    void *extPointer;

    va_start( ap, num );
    
    datTab = (struct inform *) td;
    for( i = 0; i < datTab->countColum; ++ i )
    {
        
        switch( datTab->bufType[i] )
        {
        case 1:
            ch = (char) va_arg( ap, int);
            datTab->ptr->s[i] = calloc(1, sizeof(char));
            *(char *)datTab->ptr->s[i] =  ch;
            printf("char %c /добавлен\n", *(char *)datTab->ptr->s[i]);
            break;
        case 2:
            dbd =  va_arg( ap, double);
            datTab->ptr->s[i] = calloc(1, sizeof(double));
            *(double *)datTab->ptr->s[i] = dbd;
            printf("double %f /добавлен\n", *(double *)datTab->ptr->s[i]);
            break;
        case 3:
            ln =  va_arg( ap, long);
            datTab->ptr->s[i] = calloc(1, sizeof(long));
            *(long *)datTab->ptr->s[i] = ln;
            printf("long %ld /добавлен\n", *(long *)datTab->ptr->s[i]);
            break;
        case 4:
            strn = va_arg( ap, char *);
            datTab->ptr->s[i]=(char *)calloc(1,strlen(strn));  
            strcpy ((char *)datTab->ptr->s[i],strn);
            printf("string %s /добавлена\n",  (char *) datTab->ptr->s[i]);
            break;
        default:
            printf("Неправельный параметр функции tioTableRecord!\n");
            return NULL;
        }
    }

    /*Выделение памяти для указателя на голову списка*/
    if( (datTab->ptr->n = (cl*) malloc(sizeof(cl))) == NULL )
    {
        printf("Error\n");
        return NULL;
    }
    datTab->ptr = datTab->ptr->n;
    datTab->ptr->n = NULL;

    /*Выделяем память для указателя ptr->s*/
    if( (datTab->ptr->s = (void **) calloc(datTab->countColum, sizeof(void *))) == NULL )
    {
        printf("\nError ptr->s\n");
        return NULL;
    }

   va_end(ap); 

    extPointer = (void *) datTab;
    return extPointer;

}
