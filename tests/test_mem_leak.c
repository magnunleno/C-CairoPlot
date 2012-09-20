/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (test_mem_leak.c) is part of C-CairoPlot.
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

#include <stdio.h>
#include <stdlib.h>

#include "cairoplot.h"

typedef struct TEST_DATA
{
	int value;
} TestData;

void deleteTestData(void *content)
{
	TestData *data = (TestData *)content;
	printf("Data delete %i\n", data->value);
	free(data);
}

void dummyDelete(void *content)
{
	printf("Dummy delete %i\n", (int)content);
}

TestData *newData(int value)
{
	TestData *data = cp_new(1, TestData);
	data->value = value;
	return data;
}

void test_data_list()
{
	CP_List *list = cp_newList();
	TestData *data = NULL;

	data = cp_new(1, TestData);
	data->value = 12;
	cp_appendNode(list, data); 

	cp_appendNode(list, newData(13));

	data = cp_new(1, TestData);
	data->value = 14;
	cp_appendNode(list, data);

	printf("Size of list %i\n", list->size);
	cp_deleteList(list, &deleteTestData);
}

void test_int_list()
{
	CP_List *list = cp_newList();

	cp_appendNode(list, 10);
	cp_appendNode(list, 11);
	cp_appendNode(list, 12);

	printf("Size of list %i\n", list->size);
	cp_emptyList(list, &dummyDelete);

	free(list);
}

void test_color_list()
{
	CP_List *colorList = cp_newList();
	cp_appendNode(colorList, cp_newColor(0.1, 0.2, 0.3, 0.4));
	cp_appendNode(colorList, cp_newColor(0.2, 0.3, 0.4, 0.5));
	cp_appendNode(colorList, cp_newColor(0.3, 0.4, 0.5, 0.6));

	cp_deleteList(colorList, _cp_deleteColor);
	printf("Done with color list\n");
}

int main(int argc, char const *argv[])
{
	test_int_list();
	test_data_list();
	test_color_list();
	return 0;
}
