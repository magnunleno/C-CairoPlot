/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (list_util.c) is part of C-CairoPlot.
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

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

CP_List *cp_newList()
{
	CP_List *list = cp_new(1, CP_List);
	list->first = NULL;	
	list->last = NULL;
	list->iter = NULL;
	list->size = 0;
	return list;
}

void __cp_appendNode(CP_List *list, void* content)
{
	CP_ListNode *node = cp_new(1, CP_ListNode);
	node->next = NULL;
	node->previous = NULL;
	node->content = content;

	if (list->size == 0)
		list->first = node;
	else
	{
		list->last->next = node;
		node->previous = list->last;
	}
	list->last = node;
	list->size++;
}

void cp_emptyList(CP_List *list, void (*deleteNodeFunc)(void *))
{
	CP_ListNode *current;
	cp_startIter(list);
	while (list->iter)
	{
		current = list->iter;
		list->iter = current->next;
		if (current == list->last)
		{
			list->last = NULL;
			list->first = NULL;
		}
		list->first = list->iter;
		deleteNodeFunc(current->content);
		free(current);
		list->size--;
	}
	list->first = NULL;
	list->iter = NULL;
}
