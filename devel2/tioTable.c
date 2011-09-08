#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/*Singly linked list for data*/

typedef struct cell
{
    void** row_data;
    struct cell* next_cell;
} cl;

/* The structure is designed to store table's data.
 * Fields:
 * cap_names        - array contains a string with the names of table title
 * count_columns    - the number of columns
 * count_letter     - the nunber of letter in cap string
 * mas_types        - array which specifies the types of data
 * head             - pointer to the top of list
 * ptr              - pointers to the current element of list*/

struct inform
{
    char** cap_names;
    int count_columns;
    int count_letter;
    int* mas_types;
    cl *head, *ptr;
};


int counting_columns(const char* format);
int counting_letter(const char* format);
/*int create_array_title( const char* format, table_data->cap_names );*/

void* tioTableBegin( const char* format, ... )
{
    int i;
    va_list ap;    
    struct inform* table_data;
    void* export_pointer;

    va_start( ap, format);
    
    /*Allocating memory for table_data structure*/
    if ((table_data  = (struct inform*) calloc (1, sizeof( struct inform ))) == NULL )
    {
        printf("Error in alloc memory for table_data\n");
        return NULL;
    }

    if( (format[0] == '\0') || (format[0] == '\n') || (format[0] == '&') )
    {
        printf( "\nError in cap!\n" );
        return NULL;
    }

    table_data->count_columns = counting_columns( format );
    table_data->count_letter = counting_letter( format );

    printf( "Count of columns:  %d\n", table_data->count_columns );
    printf( "Count of letters:  %d\n", table_data->count_letter );

    /*Allocating memory for table_data->mas_types*/
    if( (table_data->mas_types = (int*) calloc(table_data->count_columns, sizeof(int))) == NULL )
    {
        printf("\nError in allocating memory for table_data->mas_types\n");
        return NULL;
    }
    
    
    /*Allocating memory for table_data->cap_names*/
    if( (table_data->cap_names = (char **) calloc(table_data->count_columns, sizeof(char *))) == NULL )
    {
        printf("\nError in allocating memory for table_data->cap_names\n");
        return NULL;
    }
    else
    {
        for( i = 0; i < table_data->count_columns; ++ i )
        {
            if( (table_data->cap_names[i] = (char *) calloc(table_data->count_letter + 1, sizeof(char ))) == NULL )
            {
                printf("\nError in allocating memory for table_data->cap_names\n");
                return NULL;
            }
        }
    }


    /*Print using data types*/ 
    printf("Data types: ");
    for( i = 0; i < table_data->count_columns; ++ i )
    {
        table_data->mas_types[i] = va_arg( ap, int );
        printf( "%d ", table_data->mas_types[i]);
    }
    
    va_end( ap );
/*======================================================================*/ 
/*    int create_array_title( const char* format, char** cap_names )*/
/*======================================================================*/ 
    return export_pointer = (void *) table_data;
}

int counting_columns(const char* format)
{
    int i = 0;
    int count_columns = 1;
    while( format[i] != '\0' )
    {
        if( (format[i] == '&') && (format[i+1] == '&') )
            ++ i;
        else if ( (format[i] == '&') && (format[i+1] != '&') )
            ++ count_columns;
        ++ i;
    }
    return count_columns; 
}

int counting_letter(const char* format)
{
    int i = 0;
    int count_letter = 0;
    while( format[i] != '\0' )
    {
        ++ count_letter;
        ++ i;
    }
    return count_letter; 
}

void create_array_title( const char* format, char** cap_names )
{
    int i = 0;
    int j = 0;
    int ii = 0;

    while( format[ii] != '\0' )
    {
        if( format[ii] == '&')
        {
            if( format[ii+1] == '&' )
            {
                ++ ii;
            }
            else
            {
                cap_names[i][j] = '\0';
                ++ j;
            }
        }
        cap_names[i][j] = format[ii]; 
        ++ i;
        ++ ii;
    }
}
