#include <check.h>
#include "lib.h"

START_TEST(test_calculate)
{
    char* expr1 = "2+3";
    ck_assert_int_eq(5, calculate(expr1));

    char* expr2 = "3*5+2";
    ck_assert_int_eq(17, calculate(expr2));

    char* expr3 = "(2+3)*4-2";
    ck_assert_int_eq(18, calculate(expr3));

    char* expr4 = "4^3+2*3-5";
    ck_assert_int_eq(35, calculate(expr4));
}
END_TEST

int main(void)
{
    Suite* s = suite_create("Test");

    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_calculate);
    suite_add_tcase(s, tc_core);

    SRunner* sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
