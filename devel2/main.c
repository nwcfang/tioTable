/* Можно ли реализовать чтение до конца файла, чтобы считывать
 * из директории все фалы тестов.*/
#include <CUnit/Basic.h>
#include <stdio.h>
#include "tioTable.h"

enum { TIOCHAR, TIODOUBLE, TIOLONG, TIOSTRING };

int main()
{
    CU_ErrorCode error;
    void* td;                   /*main data-struct pointer*/ 
    char* cap_name_string = "name1&na&&me2";
    printf( "\n========================= START =========================\n" );

    tioTableBegin( cap_name_string, TIOCHAR, TIODOUBLE );

    /*Initialize registry*/
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /*Register suites in the test's registry*/
    error = CU_register_suites(suites);
    if (error != CUE_SUCCESS)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /*How much information to be displayed*/ 
    CU_basic_set_mode(CU_BRM_VERBOSE);

    /*Run all test*/
    CU_basic_run_tests();
    
    CU_cleanup_registry();

    printf( "\n========================= STOP ==========================\n" );
    return CU_get_error();
}
