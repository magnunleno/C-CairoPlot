/*
 * Copyright (C) 2012 - Magnun Leno
 *
 * This file (series_test.c) is part of C-CairoPlot.
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

#include "series_test.h"

START_TEST(test_data_series_creation){
	bool retCode;
	CP_Series *series;

	series = cp_newDataSeries("Series name");
	retCode = cp_appendData(series, "label 1", 10.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");
	retCode = cp_appendData(series, "label 2", 11.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");
	retCode = cp_appendData(series, "label 3", 12.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");

	check_equal_n(series->size, 3, "Found '%i' as series size, expected '%i'");

	retCode = cp_appendPoint(series, "label 3", 12.0, 12.0);
	check_equal_n(retCode, false, "Found '%i' as retCode, expected '%i'");

	check_equal_n(series->size, 3, "Found '%i' as series size, expected '%i'");

	double values[] = {10.0, 11.0, 12.0};
	char* labels[] = {"label 1", "label 2", "label 3"};

	int n = 0;
	CP_Data *current = NULL;
	for (cp_startIter(series); series->iter; cp_iterNext(series)){
		current = cp_iterUnpack(series, CP_Data*);
		check_equal_n(current->value, values[n], "Found '%f' as data value, expected '%f'");
		check_equal_s(current->label, labels[n], "Expected '%s' as data label, found '%s'");
		n++;
	}
	cp_emptySeries(series);
	check_equal_n(series->size, 0, "Found '%i' as series size, expected '%i'");
	cp_destroySeries(series);
	check_equal_null(series);
}END_TEST

START_TEST(test_point_series_creation){
	bool retCode;
	CP_Series *series;

	series = cp_newPointSeries("Series name");
	retCode = cp_appendPoint(series, "label 1", 10.0, 11.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");
	retCode = cp_appendPoint(series, "label 2", 11.0, 12.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");
	retCode = cp_appendPoint(series, "label 3", 12.0, 13.0);
	check_equal_n(retCode, true, "Found '%i' as retCode, expected '%i'");

	check_equal_n(series->size, 3, "Found '%i' as series size, expected '%i'");

	retCode = cp_appendData(series, "label 3", 12.0);
	check_equal_n(retCode, false, "Found '%i' as retCode, expected '%i'");

	check_equal_n(series->size, 3, "Found '%i' as series size, expected '%i'");

	double values[3][2] = {
		{10.0, 11.0},
		{11.0, 12.0},
		{12.0, 13.0},
	};
	char* labels[] = {"label 1", "label 2", "label 3"};

	int n = 0;
	CP_Point *current = NULL;
	for (cp_startIter(series); series->iter; cp_iterNext(series)){
		current = cp_iterUnpack(series, CP_Point*);
		check_equal_n(current->x, values[n][0], "Found '%f' as point x, expected '%f'");
		check_equal_n(current->y, values[n][1], "Found '%f' as point y, expected '%f'");
		check_equal_s(current->label, labels[n], "Expected '%s' as data label, found '%s'");
		n++;
	}
	cp_destroySeries(series);
	check_equal_null(series);
}END_TEST

START_TEST(test_series_circular_iteration)
{
	CP_Series *series = cp_newDataSeries(NULL);
	double sum = 0.0;
	int count = 0;
	
	cp_appendData(series, NULL, 1.0);
	cp_appendData(series, NULL, 0.5);
	cp_appendData(series, NULL, 0.25);

	// Test iteration in a for loop
	for (cp_startIter(series); series->iter; cp_iterNextCircular(series)){
		sum += cp_iterDataAttr(series, value);
		count++;
		if (count == 5)
			break;
	}

	check_equal_n(sum, 3.25, "Sum found was %f, expected %f");

	// Test iteration in a while loop
	count = 0;
	sum = 0;
	cp_startIter(series);
	while (series->iter){
		sum += cp_iterDataAttr(series, value);
		count++;
		if (count == 5)
			break;
		cp_iterNextCircular(series);
	}

	check_equal_n(sum, 3.25, "Sum found was %f, expected %f");

	cp_destroySeries(series);
	check_equal_null(series);
}END_TEST

START_TEST(test_series_index_search)
{
	double value;
	CP_Series *series = cp_newDataSeries(NULL);
	cp_appendData(series, NULL, 1.0);
	cp_appendData(series, NULL, 0.5);
	cp_appendData(series, NULL, 0.25);
	cp_appendData(series, NULL, 0.75);
	cp_appendData(series, NULL, 0.15);

	value = cp_getDataNodeN(series, 0)->value;
	check_equal_n(value, 1.0, "Value #0 found %f, expected %f");

	value = cp_getDataNodeN(series, 1)->value;
	check_equal_n(value, 0.5, "Value #1 found %f, expected %f");

	value = cp_getDataNodeN(series, 2)->value;
	check_equal_n(value, 0.25, "Value #2 found %f, expected %f");

	value = cp_getDataNodeN(series, 3)->value;
	check_equal_n(value, 0.75, "Value #3 found %f, expected %f");

	value = cp_getDataNodeN(series, 4)->value;
	check_equal_n(value, 0.15, "Value #4 found %f, expected %f");

	value = cp_getDataNodeN(series, -1)->value;
	check_equal_n(value, 0.15, "Value #5 found %f, expected %f");

	value = cp_getDataNodeN(series, -2)->value;
	check_equal_n(value, 0.75, "Value #5 found %f, expected %f");

	value = cp_getDataNodeN(series, -13)->value;
	check_equal_n(value, 0.25, "Value #5 found %f, expected %f");

	cp_destroySeries(series);

}END_TEST

START_TEST(test_series_data_max)
{
	CP_Series *series = cp_newDataSeries(NULL);
	cp_appendData(series, NULL, 1.0);
	cp_appendData(series, NULL, 0.5);
	cp_appendData(series, NULL, 0.25);
	check_equal_n(cp_maxDataSeries(series), 1.0, "Found max data as %f, expected %f.");

	cp_appendData(series, NULL, 10.0);
	check_equal_n(cp_maxDataSeries(series), 10.0, "Found max data as %f, expected %f.");

	cp_appendData(series, NULL, -20.0);
	check_equal_n(cp_maxDataSeries(series), 10.0, "Found max data as %f, expected %f.");
}END_TEST

// TODO: Add tests to verify the first and last poitner

Suite* series_suite(void){
	Suite *s = suite_create("Series Test Suite");

	TCase *tc_core = tcase_create("Series Test Case");
	tcase_add_test(tc_core, test_data_series_creation);
	tcase_add_test(tc_core, test_point_series_creation);
	tcase_add_test(tc_core, test_series_circular_iteration);
	tcase_add_test(tc_core, test_series_index_search);
	tcase_add_test(tc_core, test_series_data_max);

	suite_add_tcase(s, tc_core);
	return s;
}
