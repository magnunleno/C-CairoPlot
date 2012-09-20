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

int CHECKSUM = 0;

void deleteInt(void *content)
{
	CHECKSUM += (int)content;
}

typedef struct DATA
{
	int value;
} Data;

Data *newData(int value)
{
	Data *data = cp_new(1, Data);
	data->value = value;
	return data;
}

void deleteStruct(void *content)
{
	CHECKSUM += ((Data *)content)->value;
}

/***************** Test Functions *********************/
START_TEST(test_simple_int_list)
{
	CHECKSUM = 0;
	CP_List *list = cp_newList();

	cp_appendNode(list, 10);
	cp_appendNode(list, 11);
	cp_appendNode(list, 12);

	cp_emptyList(list, &deleteInt);
	cp_deleteList(list, &deleteInt);

	check_equal_n(CHECKSUM, 33, "Checksum found was %i, expected %i");
	check_equal_null(list);
}END_TEST

START_TEST(test_struct_list)
{
	CHECKSUM = 0;
	CP_List *list = cp_newList();
	
	Data *first = cp_new(1, Data);
	first->value = 10;
	cp_appendNode(list, first);

	cp_appendNode(list, newData(100));

	Data *last = cp_new(1, Data);
	last->value = 1000;
	cp_appendNode(list, last);

	check_equal_n(cp_nodeUnpack(list->first, Data*), first, "Address found was %p, expected %p");
	check_equal_n(cp_nodeUnpack(list->last, Data*), last, "Address found was %p, expected %p");

	cp_deleteList(list, &deleteStruct);

	check_equal_n(CHECKSUM, 1110, "Checksum found was %i, expected %i");
	check_equal_null(list);
}END_TEST

START_TEST(test_list_iteration)
{
	CP_List *list = cp_newList();
	int sum = 0;
	
	cp_appendNode(list, newData(10));
	cp_appendNode(list, newData(100));
	cp_appendNode(list, newData(1000));

	Data *data;
	for (cp_startIter(list); list->iter; cp_iterNext(list)){
		data = cp_iterUnpack(list, Data*);
		sum += data->value;
	}

	check_equal_n(sum, 1110, "Sum found was %i, expected %i");
	cp_deleteList(list, &deleteStruct);
	check_equal_null(list);
}END_TEST

START_TEST(test_list_circular_iteration)
{
	CP_List *list = cp_newList();
	int sum = 0;
	int count = 0;
	
	cp_appendNode(list, newData(10));
	cp_appendNode(list, newData(11));
	cp_appendNode(list, newData(12));

	// Test iteration in a for loop
	Data *data;
	for (cp_startIter(list); list->iter; cp_iterNextCircular(list)){
		data = cp_iterUnpack(list, Data*);
		sum += data->value;
		count++;
		if (count == 5)
			break;
	}

	check_equal_n(sum, 54, "Sum found was %i, expected %i");

	// Test iteration in a while loop
	data = NULL;
	count = 0;
	sum = 0;
	cp_startIter(list);
	while (list->iter){
		data = cp_iterUnpack(list, Data*);
		sum += data->value;
		count++;
		if (count == 5)
			break;
		cp_iterNextCircular(list);
	}

	check_equal_n(sum, 54, "Sum found was %i, expected %i");

	cp_deleteList(list, &deleteStruct);
	check_equal_null(list);
}END_TEST

Suite* list_suite(void)
{
	Suite *s = suite_create("List Suite");

	TCase *tc_core = tcase_create("List testcase");
	tcase_add_test(tc_core, test_simple_int_list);
	tcase_add_test(tc_core, test_struct_list);
	tcase_add_test(tc_core, test_list_iteration);
	tcase_add_test(tc_core, test_list_circular_iteration);

	suite_add_tcase(s, tc_core);
	return s;
}
