#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

void *tioTableRecord( void *td )
{
    struct inform *datTab;
    int i;
    int* in;
    char* ch;
    double* db;
    void *extPointer;
    
    datTab = (struct inform *) td;

    (in = (int*) calloc( 1, sizeof(int))) == NULL;
    (ch = (char*) calloc( 1, sizeof(char))) == NULL;
    (db = (double*) calloc( 1, sizeof(double))) == NULL; 
    
    if( (in == NULL) && (ch == NULL) && (db == NULL) )
    {
        fprintf( stderr, "Error calloc 'in' or 'ch' or 'db'\n" );
        return NULL;
    }

    /*Тестовый способ присвоения данных*/
    in[0] = 5;
    ch[0] = 'c';
    db[0] = 1.42;
    datTab->data[0][0] = (void *) ch;
    datTab->data[1][0] = (void *) db;
    datTab->data[2][0] = (void *) in;

    printf( "В data хронится: %c, %.2f, %d\n", *(char *)datTab->data[0][0], *(double *)datTab->data[1][0], *(int *)datTab->data[2][0] );

    extPointer = (void *) datTab;
    return extPointer;

}
