/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (util_test.c) is part of C-CairoPlot.
 * 
 * C-CairoPlot is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * C-CairoPlot is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * C-CairoPlot. If not, see http://www.gnu.org/licenses/.
 *
 */

#include "util_test.h"

START_TEST(test_file_extention)
{
	/*
	 * Tests the file name allocation
	 */
	char *fname1 = "testname";
	char *fname2 = "/test/path/testname";
	char *filename = NULL;

	cp_addFileExtension(&filename, fname1, CP_SVG);
	check_equal_s(filename, "testname.svg", "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname1, CP_PNG);
	check_equal_s(filename, "testname.png", "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname2, CP_SVG);
	check_equal_s(filename, "/test/path/testname.svg", "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname2, CP_PNG);
	check_equal_s(filename, "/test/path/testname.png", "Extension added incorrectly. Expected '%s', received '%s'");
}END_TEST

int main(void){
	int number_failed;
	SRunner *sr;
	Suite *suite;

	suite = suite_create("Util Suite");

	TCase *tc_core = tcase_create("Util testcase");
	tcase_add_test(tc_core, test_file_extention);

	suite_add_tcase(suite, tc_core);
	sr = srunner_create(suite);
	srunner_run_all(sr, CK_NORMAL);

	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0)?0:1;
}
