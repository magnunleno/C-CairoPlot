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
	check_equal_s("testname.svg", filename, "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname1, CP_PNG);
	check_equal_s("testname.png", filename, "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname2, CP_SVG);
	check_equal_s("/test/path/testname.svg" ,filename, "Extension added incorrectly. Expected '%s', received '%s'");

	cp_addFileExtension(&filename, fname2, CP_PNG);
	check_equal_s("/test/path/testname.png", filename, "Extension added incorrectly. Expected '%s', received '%s'");
}END_TEST

Suite* util_suite(void)
{
	Suite *s = suite_create("util");

	TCase *tc_core = tcase_create("Util testcase");
	tcase_add_test(tc_core, test_file_extention);

	suite_add_tcase(s, tc_core);
	return s;
}
