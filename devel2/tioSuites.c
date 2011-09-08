#include <stdio.h>
#include <CUnit/Basic.h>
#include "tioTable.h"

int init_create_array_title(void)
{
    char** cap_names;
    char* format = "name1&name2&na&&me3";
    int count_columns;
    count_letter; 

    count_columns = counting_columns( format );
    count_letter = counting_letter( format );

    if( (cap_names = (char **) calloc(count_columns, sizeof(char *))) == NULL )
    {
        return -1;
    }
    else
    {
        for( i = 0; i < count_columns; ++ i )
        {
            if( (cap_names[i] = (char *) calloc(count_letter + 1, sizeof(char ))) == NULL )
            {
                return -1;
            }
        }
    }
    create_array_title( format, cap_names );
}

int clean_create_array_title(void)
{
    int i;
    /*FREE*/ 
    for( i = 0; i < count_columns; ++ i )
    {
        free( cap_names[i] );
    }
    free( cap_names );
}

CU_SuiteInfo suites[] = {
    {"Simply tests", NULL, NULL, test_simply_array},
    {"Not simply tests", init_create_array_title, clean_create_array_title, test_create_array_title},
    CU_SUITE_INFO_NULL,
};
