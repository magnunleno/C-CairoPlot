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

#ifndef _CP_LIST_UTIL_H
#define _CP_LIST_UTIL_H

#define CP_BASELIST(_ListType)	\
	_ListType *first;			\
	_ListType *last;			\
	_ListType *iter;			\
	int size

#define CP_INIT_LIST(list)		\
	list->first = NULL;			\
	list->last = NULL;			\
	list->iter = NULL;			\
	list->size = 0

#define cp_appendNode(list, node) 					\
	if (list->size == 0)							\
		list->first = node;							\
	else 											\
		list->last->next = node;					\
	list->last = node; 								\
	list->size++

#define cp_startIter(list) list->iter = list->first
#define cp_iterNext(list) list->iter = list->iter->next
#define cp_iterNextCircular(list) list->iter = list->iter->next == NULL?list->first:list->iter->next
#define cp_iterUnpack(list, type) (type)(list->iter->content)

#endif // _CP_LIST_UTIL_H
