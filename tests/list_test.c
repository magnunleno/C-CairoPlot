/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (virtual_list_test.c) is part of C-CairoPlot.
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

#include "list_test.h"

START_TEST(test_color_list)
{
	CP_Color *color = NULL;
	CP_List *list = cp_newList(CP_COLOR);

	cp_appendNode(list, cp_newColor(0.1, 0.2, 0.3, 1.0));
	color = cp_objectUnpack(list->last, CP_Color*);
	check_equal_n(list->size, 1, "List size found was %i, expected %i");
	check_equal_n(color->red, 0.1, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, 0.2, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, 0.3, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 1.0, "Found '%f' as alpha, expected '%f'");

	cp_appendNode(list, cp_newColor(0.2, 0.3, 0.4, 1.0));
	color = cp_objectUnpack(list->last, CP_Color*);
	check_equal_n(list->size, 2, "List size found was %i, expected %i");
	check_equal_n(color->red, 0.2, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, 0.3, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, 0.4, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 1.0, "Found '%f' as alpha, expected '%f'");

	cp_appendNode(list, cp_newColor(0.3, 0.4, 0.5, 1.0));
	color = cp_objectUnpack(list->last, CP_Color*);
	check_equal_n(list->size, 3, "List size found was %i, expected %i");
	check_equal_n(color->red, 0.3, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, 0.4, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, 0.5, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 1.0, "Found '%f' as alpha, expected '%f'");

	double values[3][4] = {
		{0.1, 0.2, 0.3, 1.0},
		{0.2, 0.3, 0.4, 1.0},
		{0.3, 0.4, 0.5, 1.0},
	};

	int n = 0;
	for (cp_startIter(list); list->iter; cp_iterNext(list))
	{
		color = cp_iterUnpack(list, CP_Color*);
		check_equal_n(color->red, values[n][0], "Found '%f' as red, expected '%f'");
		check_equal_n(color->green, values[n][1], "Found '%f' as green, expected '%f'");
		check_equal_n(color->blue, values[n][2], "Found '%f' as blue, expected '%f'");
		check_equal_n(color->alpha, values[n][3], "Found '%f' as alpha, expected '%f'");
		n++;

	}

	cp_emptyList(list);
	check_equal_n(list->size, 0, "List size found was %i, expected %i");
	cp_deleteList(list);
	check_equal_null(list);
}END_TEST

START_TEST(test_data_list)
{
	CP_Data *data = NULL;
	CP_List *list = cp_newList(CP_DATA);

	cp_appendNode(list, cp_newData("test", 1.0, 2.0, 3.0));
	data = cp_objectUnpack(list->last, CP_Data*);
	check_equal_n(list->size, 1, "List size found was %i, expected %i");
	check_equal_s(data->label, "test", "Found '%s' as data label, expected '%s'");
	check_equal_n(data->x, 1.0, "Found '%f' as x, expected '%f'");
	check_equal_n(data->y, 2.0, "Found '%f' as y, expected '%f'");
	check_equal_n(data->z, 3.0, "Found '%f' as z, expected '%f'");

	cp_appendNode(list, cp_newData("test", 2.0, 3.0, 4.0));
	data = cp_objectUnpack(list->last, CP_Data*);
	check_equal_n(list->size, 2, "List size found was %i, expected %i");
	check_equal_s(data->label, "test", "Found '%s' as data label, expected '%s'");
	check_equal_n(data->x, 2.0, "Found '%f' as x, expected '%f'");
	check_equal_n(data->y, 3.0, "Found '%f' as y, expected '%f'");
	check_equal_n(data->z, 4.0, "Found '%f' as z, expected '%f'");

	cp_appendNode(list, cp_newData("test", 3.0, 4.0, 5.0));
	data = cp_objectUnpack(list->last, CP_Data*);
	check_equal_n(list->size, 3, "List size found was %i, expected %i");
	check_equal_s(data->label, "test", "Found '%s' as data label, expected '%s'");
	check_equal_n(data->x, 3.0, "Found '%f' as x, expected '%f'");
	check_equal_n(data->y, 4.0, "Found '%f' as y, expected '%f'");
	check_equal_n(data->z, 5.0, "Found '%f' as z, expected '%f'");


	double values[3][3] = {
		{1.0, 2.0, 3.0},
		{2.0, 3.0, 4.0},
		{3.0, 4.0, 5.0},
	};

	int n = 0;
	for (cp_startIter(list); list->iter; cp_iterNext(list))
	{
		data = cp_iterUnpack(list, CP_Data*);
		check_equal_s(data->label, "test", "Found '%s' as data label, expected '%s'");
		check_equal_n(data->x, values[n][0], "Found '%f' as red, expected '%f'");
		check_equal_n(data->y, values[n][1], "Found '%f' as green, expected '%f'");
		check_equal_n(data->z, values[n][2], "Found '%f' as blue, expected '%f'");
		n++;

	}
	data = NULL;

	cp_emptyList(list);
	check_equal_n(list->size, 0, "List size found was %i, expected %i");
	cp_deleteList(list);
	check_equal_null(list);
}END_TEST

START_TEST(test_list_circular_iteration)
{
	CP_List *list = cp_newList(CP_COLOR);
	double sum = 0.0;
	int count = 0;
	
	cp_appendNode(list, cp_newColor(1.0, 0.2, 0.3, 1.0));
	cp_appendNode(list, cp_newColor(0.5, 0.3, 0.4, 1.0));
	cp_appendNode(list, cp_newColor(0.25, 0.4, 0.5, 1.0));

	// Test iteration in a for loop
	for (cp_startIter(list); list->iter; cp_iterNextCircular(list)){
		sum += cp_colorAttr(list->iter, red);
		count++;
		if (count == 5)
			break;
	}

	check_equal_n(sum, 3.25, "Sum found was %f, expected %f");

	// Test iteration in a while loop
	count = 0;
	sum = 0;
	cp_startIter(list);
	while (list->iter){
		sum += cp_colorAttr(list->iter, red);
		count++;
		if (count == 5)
			break;
		cp_iterNextCircular(list);
	}

	check_equal_n(sum, 3.25, "Sum found was %f, expected %f");

	cp_deleteList(list);
	check_equal_null(list);
}END_TEST

START_TEST(test_list_index_search)
{
	double value;
	CP_List *list = cp_newList(CP_COLOR);
	cp_appendNode(list, cp_newColor(1.0, 0.2, 0.3, 1.0));
	cp_appendNode(list, cp_newColor(0.5, 0.3, 0.4, 1.0));
	cp_appendNode(list, cp_newColor(0.25, 0.4, 0.5, 1.0));
	cp_appendNode(list, cp_newColor(0.75, 0.5, 0.6, 1.0));
	cp_appendNode(list, cp_newColor(0.15, 0.6, 0.7, 1.0));

	value = cp_colorAttr(cp_getNodeN(list, 0), red);
	check_equal_n(value, 1.0, "Value #0 found %f, expected %f");

	value = cp_colorAttr(cp_getNodeN(list, 1), red);
	check_equal_n(value, 0.5, "Value #1 found %f, expected %f");

	value = cp_colorAttr(cp_getNodeN(list, 2), red);
	check_equal_n(value, 0.25, "Value #2 found %f, expected %f");

	value = cp_colorAttr(cp_getNodeN(list, 3), red);
	check_equal_n(value, 0.75, "Value #3 found %f, expected %f");

	value = cp_colorAttr(cp_getNodeN(list, 4), red);
	check_equal_n(value, 0.15, "Value #4 found %f, expected %f");

	value = cp_colorAttr(cp_getNodeN(list, -1), red);
	check_equal_n(value, 0.15, "Value #5 found %f, expected %f");

	cp_deleteList(list);

}END_TEST

START_TEST(test_sub_lists)
{
	CP_List *list = cp_newList(CP_LIST);

	CP_List *subList1 = cp_newList(CP_COLOR);
	cp_appendNode(subList1, cp_newColor(0.1, 0.1, 0.1, 1.0));
	cp_appendNode(subList1, cp_newColor(0.2, 0.2, 0.2, 1.0));
	cp_appendNode(subList1, cp_newColor(0.3, 0.3, 0.3, 1.0));
	cp_appendSubList(list, subList1);

	CP_List *subList2 = cp_newList(CP_COLOR);
	cp_appendNode(subList2, cp_newColor(0.2, 0.2, 0.2, 1.0));
	cp_appendNode(subList2, cp_newColor(0.3, 0.3, 0.3, 1.0));
	cp_appendNode(subList2, cp_newColor(0.4, 0.4, 0.4, 1.0));
	cp_appendSubList(list, subList2);

	CP_List *subList3 = cp_newList(CP_COLOR);
	cp_appendNode(subList3, cp_newColor(0.3, 0.3, 0.3, 1.0));
	cp_appendNode(subList3, cp_newColor(0.4, 0.4, 0.4, 1.0));
	cp_appendNode(subList3, cp_newColor(0.5, 0.5, 0.5, 1.0));
	cp_appendSubList(list, subList3);

	check_equal_n(list->size, 3, "Expected %i as list size, found %i\n");
	double values[3][3][4] = {
		{
			{0.1, 0.1, 0.1, 1.0},
			{0.2, 0.2, 0.2, 1.0},
			{0.3, 0.3, 0.3, 1.0},
		},
		{
			{0.2, 0.2, 0.2, 1.0},
			{0.3, 0.3, 0.3, 1.0},
			{0.4, 0.4, 0.4, 1.0},
		},
		{
			{0.3, 0.3, 0.3, 1.0},
			{0.4, 0.4, 0.4, 1.0},
			{0.5, 0.5, 0.5, 1.0},
		},
	};

	int n = 0;
	int j = 0;
	CP_List *subList = NULL;
	for (cp_startIter(list); list->iter; cp_iterNext(list)){
		subList = cp_iterUnpack(list, CP_List*);
		for (cp_startIter(subList); subList->iter; cp_iterNext(subList))
		{
			//printf("n=%i j=%i  ", n, j);
			//printf("calue=%f\n", values[n][j][0]);
			check_equal_n(cp_colorAttr(subList->iter, red), values[n][j][0], "Found '%f' as red, expected '%f'");
			check_equal_n(cp_colorAttr(subList->iter, green), values[n][j][1], "Found '%f' as green, expected '%f'");
			check_equal_n(cp_colorAttr(subList->iter, blue), values[n][j][2], "Found '%f' as blue, expected '%f'");
			check_equal_n(cp_colorAttr(subList->iter, alpha), values[n][j][3], "Found '%f' as alpha, expected '%f'");
			j++;
		}
		j = 0;
		n++;
	}

	printf("Tentando deletar lista com sublistas\n");
	cp_deleteList(list);
	check_equal_null(list);
}END_TEST

Suite* list_suite(void)
{
	Suite *s = suite_create("List Suite");

	TCase *tc_core = tcase_create("List testcase");
	tcase_add_test(tc_core, test_color_list);
	tcase_add_test(tc_core, test_data_list);
	tcase_add_test(tc_core, test_list_circular_iteration);
	tcase_add_test(tc_core, test_list_index_search);
	tcase_add_test(tc_core, test_sub_lists);

	suite_add_tcase(s, tc_core);
	return s;
}
