/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (list_util.h) is part of C-CairoPlot.
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

#include "util.h"

#ifndef _CP_LIST_H
#define _CP_LIST_H

typedef struct CP_LIST_NODE
{
	struct CP_LIST_NODE *next;
	struct CP_LIST_NODE *previous;
	void* content;
} CP_ListNode;

typedef struct CP_LIST
{
	CP_ListNode *first;
	CP_ListNode *last;
	CP_ListNode *iter;
	int size;
	struct CP_COLOR *next;
} CP_List;

CP_List *cp_newList();

void __cp_appendNode(CP_List *list, void* node);
#define cp_appendNode(list, node) __cp_appendNode(list, (void*)node)

#define cp_startIter(list) list->iter = list->first

#define cp_iterNext(list) list->iter = list->iter->next
#define cp_iterNextCircular(list) list->iter = list->iter->next == NULL?list->first:list->iter->next
#define cp_nodeUnpack(node, type) (type)(node->content)
#define cp_iterUnpack(list, type) (type)(list->iter->content)

void cp_emptyList(CP_List *list, void (*deleteNodeFunc)(void *));

#define cp_deleteList(list, deleteFunc)			\
	if (list != NULL && list->first != NULL)	\
		cp_emptyList(list, deleteFunc);			\
	free(list);									\
	list = NULL


#endif // _CP_LIST_H
