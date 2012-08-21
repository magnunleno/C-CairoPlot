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

#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "cairoplot.h"
#include "test_context.h"
#include "virtual_list.h"

int GLOBAL_N = 0;

typedef struct LIST
{
	CP_LIST_HEADER;
} List;

List* newList()
{
	List *list = cp_new(1, List);
	list->first = NULL;
	list->last = NULL;
	list->iter = NULL;
	list->size = 0;
	return list;
}

void *dummyDestroyer(void *content)
{
	int num;
	num = (int)content;
	GLOBAL_N += num;
	return NULL;
}

void *deleteList(List **ppList)
{
	cp_clearListContents((*ppList));
	free(*ppList);
	*ppList = NULL;
	return NULL;
}

START_TEST(test_list_initialization)
{
	List *list = newList();
	CP_Node *node = NULL;

	node = cp_newNode(12, &dummyDestroyer);
	//node = cp_newNode(12, NULL);
	cp_appendNode(list, node);

	node = cp_newNode(13, &dummyDestroyer);
	//node = cp_newNode(13, NULL);
	cp_appendNode(list, node);

	int sum = 0, count = 0, n = 0;

	cp_startIter(list);
	while(list->iter)
	{
		n = (int)(list->iter->content);
		sum = sum + n;
		count++;
		cp_iterNext(list);
	}
	check_equal_n(sum, 25, "Found '%i' as sum, expected '%i'");
	check_equal_n(count, 2, "Found '%i', expected '%i'");

	sum = 0, n = 0, count = 0;
	cp_startIter(list);
	while(list->iter)
	{
		count++;
		sum = sum + cp_iterUnpack(list, int);
		if (count == 5)
			break;
		cp_iterNextCircular(list);
	}
	check_equal_n(sum, 62, "Found '%i' as sum, expected '%i'");
	check_equal_n(count, 5, "Found '%i' as count, expected '%i'");
	
	node = cp_newNode(10, &dummyDestroyer);
	cp_appendNode(list, node);

	GLOBAL_N = 0;
	deleteList(&list);
	check_equal_n(GLOBAL_N, 35, "Erro while freeing. Found %i, expected %i");
	check_equal_null(list);
}END_TEST

Suite* vlist_suite(void)
{
	Suite *s = suite_create("Virtual List Suite");

	TCase *tc_core = tcase_create("Virtual List testcase");
	tcase_add_test(tc_core, test_list_initialization);

	suite_add_tcase(s, tc_core);
	return s;
}
