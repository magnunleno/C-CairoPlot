/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (virtual_list.h) is part of C-CairoPlot.
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

#ifndef _CP_VIRTUAL_LIST_H
#define _CP_VIRTUAL_LIST_H

typedef struct CP_NODE
{
	void *content;
	struct CP_NODE *next;
	void *(*destroyer)(void *);
} CP_Node;

CP_Node* _cp_newNode(void *content, void *(*destroyFunc)(void*));
CP_Node* cp_destroyNode(CP_Node **node);

#define cp_newNode(content, destroyer) _cp_newNode((void*)content, destroyer)
#define CP_LIST_HEADER		\
	CP_Node *first;			\
	CP_Node *last;			\
	CP_Node *iter;			\
	int size

#define cp_appendNode(list, node) 					\
	if (list->size == 0)							\
		list->first = node;							\
	else 											\
		list->last->next = node;					\
	list->last = node; 								\
	list->size++

#define cp_startIter(list) list->iter = list->first;

#define cp_clearListContents(list)							\
	cp_startIter(list)										\
	while (list->iter)										\
		list->iter = cp_destroyNode(&(list->iter));			\
	list->first = list->last = list->iter = NULL

#define cp_iterNext(list) list->iter = list->iter->next;
#define cp_iterNextCircular(list) list->iter = list->iter->next == NULL?list->first:list->iter->next
#define cp_iterUnpack(list, type) (type)(list->iter->content)

#endif // _CP_VIRTUAL_LIST_H
