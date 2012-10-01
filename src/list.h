/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (list.h) is part of C-CairoPlot.
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


#ifndef _CP_LIST_H_
#define _CP_LIST_H_

#include "util.h"
#include "object.h"

CP_List *cp_newList(CP_ObjectType type);

void cp_appendNode(CP_List *list, CP_Object *object);
void cp_appendSubList(CP_List *list, CP_List *subList);

#define cp_startIter(list) list->iter = list->first

#define cp_iterNext(list) list->iter = list->iter->next
#define cp_iterNextCircular(list) list->iter = list->iter->next == NULL?list->first:list->iter->next
#define cp_iterUnpack(list, type) (type)(list->iter->content)

CP_Object *cp_getNodeN(CP_List *list, int index);

void cp_emptyList(CP_List *list);

#define cp_deleteList(list)						\
	if (list != NULL && list->first != NULL)	\
		cp_emptyList(list);						\
	free(list);									\
	list = NULL


#endif // _CP_LIST_H_
