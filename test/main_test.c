#include <stdio.h>
#include <glib.h>
#include <check.h>

int main(void){
	int number_failed;

	SRunner *sr;
	//sr = srunner_create(data_suite());
	//srunner_add_suite(sr, serie_suite());
	//srunner_run_all(sr, CK_NORMAL);

	//number_failed = srunner_ntests_failed (sr);
	//srunner_free(sr);
	return (number_failed == 0)?0:1;
}
