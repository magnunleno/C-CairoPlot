/*
 * Copyright (C) 2012 - Magnun Leno da Silva
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
	CP_Object *dataObj = NULL;
	
	dataObj = cp_newData("label 1", 10.2, 11.2, 12.2);
	check_equal_n(cp_dataAttr(dataObj, x), 10.2, "Found '%f' as x, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, y), 11.2, "Found '%f' as y, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, z), 12.2, "Found '%f' as z, expected '%f'");
	check_equal_s(cp_dataAttr(dataObj, label), "label 1", "Expected '%s' as data label, found '%s'");
	cp_deleteObject(dataObj);

	dataObj = cp_newData1d("label 1", 10.2);
	check_equal_n(cp_dataAttr(dataObj, x), 10.2, "Found '%f' as x, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, y), 0, "Found '%f' as y, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, z), 0, "Found '%f' as z, expected '%f'");
	check_equal_s(cp_dataAttr(dataObj, label), "label 1", "Expected '%s' as data label, found '%s'");
	cp_deleteObject(dataObj);

	dataObj = cp_newData2d("label 1", 10.2, 11.2);
	check_equal_n(cp_dataAttr(dataObj, x), 10.2, "Found '%f' as x, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, y), 11.2, "Found '%f' as y, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, z), 0.0, "Found '%f' as z, expected '%f'");
	check_equal_s(cp_dataAttr(dataObj, label), "label 1", "Expected '%s' as data label, found '%s'");
	cp_deleteObject(dataObj);

	dataObj = cp_newData3d("label 1", 10.2, 11.2, 12.2);
	check_equal_n(cp_dataAttr(dataObj, x), 10.2, "Found '%f' as x, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, y), 11.2, "Found '%f' as y, expected '%f'");
	check_equal_n(cp_dataAttr(dataObj, z), 12.2, "Found '%f' as z, expected '%f'");
	check_equal_s(cp_dataAttr(dataObj, label), "label 1", "Expected '%s' as data label, found '%s'");
	cp_deleteObject(dataObj);
}END_TEST

START_TEST(test_data_list_creation){
	CP_List *list = cp_newList(CP_DATA);
	cp_appendNode(list, cp_newData1d("label 1", 10.0));
	cp_appendNode(list, cp_newData1d("label 2", 11.0));
	cp_appendNode(list, cp_newData1d("label 3", 12.0));

	double values[] = {10.0, 11.0, 12.0};
	char* labels[] = {"label 1", "label 2", "label 3"};

	int n = 0;
	CP_Data *current = NULL;
	for (cp_startIter(list); list->iter; cp_iterNext(list)){
		current = cp_iterUnpack(list, CP_Data*);
		check_equal_n(current->x, values[n], "Found '%f' as data value, expected '%f'");
		check_equal_n(current->y, 0.0, "Found '%f' as data value, expected '%f'");
		check_equal_n(current->z, 0.0, "Found '%f' as data value, expected '%f'");
		check_equal_s(current->label, labels[n], "Expected '%s' as data label, found '%s'");
		n++;
	}
	cp_deleteList(list);
	check_equal_null(list);
	
}END_TEST

Suite* data_suite(void){
	Suite *s = suite_create("Data Test Suite");

	TCase *tc_core = tcase_create("Date Test Case");
	tcase_add_test(tc_core, test_data_creation);
	//tcase_add_test(tc_core, test_data_list_creation);

	suite_add_tcase(s, tc_core);
	return s;
}
