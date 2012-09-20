/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 *
 * This file (template.c) is part of C-CairoPlot.
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
