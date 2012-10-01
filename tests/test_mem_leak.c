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

void test_color_list()
{
	CP_Color *color = NULL;
	CP_List *list = cp_newList(CP_COLOR);

	cp_appendNode(list, cp_newColor(0.1, 0.2, 0.3, 1.0));
	cp_appendNode(list, cp_newColor(0.2, 0.3, 0.4, 1.0));
	cp_appendNode(list, cp_newColor(0.3, 0.4, 0.5, 1.0));
	for (cp_startIter(list); list->iter; cp_iterNext(list))
	{
		color = cp_iterUnpack(list, CP_Color*);
	}

	cp_deleteList(list);
}
void test_sub_lists()
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

	CP_List *subList = NULL;
	CP_Color *color;
	for (cp_startIter(list); list->iter; cp_iterNext(list)){
		subList = cp_iterUnpack(list, CP_List*);
		for (cp_startIter(subList); subList->iter; cp_iterNext(subList))
		{
			color = cp_iterUnpack(list, CP_Color*);
		}
	}

	cp_deleteList(list);
}

int main(int argc, char const *argv[])
{
	test_color_list();
	test_sub_lists();
	return 0;
}
