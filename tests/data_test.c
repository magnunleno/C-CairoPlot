/*
 * Copyright (C) 2012 - Magnun Leno
 *
 * This file (data_test.c) is part of C-CairoPlot.
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

#include "data_test.h"

START_TEST(test_data_creation){
	CP_Data *data = NULL;
	
	data = cp_newData("label 1", 10.2);
	check_equal_n(data->value, 10.2, "Found '%f' as value, expected '%f'");
	check_equal_s(data->label, "label 1", "Expected '%s' as data label, found '%s'");
	free(data);

	data = cp_newData(NULL, 11.2);
	check_equal_n(data->value, 11.2, "Found '%f' as value, expected '%f'");
	check_equal_null(data->label);
	free(data);
}END_TEST

START_TEST(test_point_creation){
	CP_Point *point;

	point = cp_newPoint("test", 10.2, 11.2);
	check_equal_n(point->x, 10.2, "Found '%f' as x, expected '%f'");
	check_equal_n(point->y, 11.2, "Found '%f' as x, expected '%f'");
	check_equal_s(point->label, "test", "Expected '%s' as data label, found '%s'");
	free(point);

	point = cp_newPoint(NULL, 0.0, 11.2);
	check_equal_n(point->x, 0.0, "Found '%f' as x, expected '%f'");
	check_equal_n(point->y, 11.2, "Found '%f' as x, expected '%f'");
	check_equal_null(point->label);
	free(point);

}END_TEST

Suite* data_suite(void){
	Suite *s = suite_create("data");

	TCase *tc_core = tcase_create("Data Case");
	tcase_add_test(tc_core, test_data_creation);
	tcase_add_test(tc_core, test_point_creation);

	suite_add_tcase(s, tc_core);
	return s;
}
