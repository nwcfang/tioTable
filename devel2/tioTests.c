#include <CUnit/Basic.h>

void test_counting_number_of_columns(void)
{
    CU_ASSERT_EQUAL(counting_columns("name1&name2"), 2);
    CU_ASSERT_EQUAL(counting_columns("name1"), 1);
    CU_ASSERT_EQUAL(counting_columns(""), 1);
    CU_ASSERT_EQUAL(counting_columns("name1&na&&me2"), 2);
}

void test_counting_letter(void)
{
    CU_ASSERT_EQUAL(counting_letter("name1&name2"), 11);
    CU_ASSERT_EQUAL(counting_letter("name1"), 5);
    CU_ASSERT_EQUAL(counting_letter(""), 0);
    CU_ASSERT_EQUAL(counting_letter("name1&na&&me2"), 13);
}
void test_create_array_title(void)
{
    CU_ASSERT_STRING_EQUAL( cap_names[0], "name1" );  
    CU_ASSERT_STRING_EQUAL( cap_names[1], "name2" );
    CU_ASSERT_STRING_EQUAL( cap_names[2], "na&&me3" );  
}

CU_TestInfo test_simply_array[] = {
    { "test_counting_columns", test_counting_number_of_columns },
    { "test_counting_letter", test_counting_letter },
    CU_TEST_INFO_NULL,
};


