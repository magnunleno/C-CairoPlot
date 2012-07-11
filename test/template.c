#include "example_test.h"


START_TEST(test_example){
	fail_unless(0 == 0, "Erro message");
}END_TEST


Suite* example_suite(void){
	Suite *s = suite_create("Example Suite");

	TCase *tc_core = tcase_create("Example Test Case");
	tcase_add_test(tc_core, test_example);

	suite_add_tcase(s, tc_core);
	return s;
}
