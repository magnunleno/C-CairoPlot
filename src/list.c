/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (list.c) is part of C-CairoPlot.
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

CP_List *cp_newList(CP_ObjectType type)
{
	CP_List *list = cp_new(1, CP_List);
	list->type = type;
	list->first = NULL;	
	list->last = NULL;
	list->iter = NULL;
	list->size = 0;
	return list;
}

void cp_appendNode(CP_List *list, CP_Object* obj)
{
	if (obj->type != list->type)
	{
		printf("This list is not initialized for this kind of object\n");
		return;
	}

	if (list->size == 0)
		list->first = obj;
	else
	{
		list->last->next = obj;
		obj->previous = list->last;
	}
	list->last = obj;
	list->size++;
}

void cp_appendSubList(CP_List *list, CP_List *subList)
{
	CP_Object *obj = cp_newObject((void*)subList, CP_LIST);
	cp_appendNode(list, obj);
}

CP_Object *cp_getNodeN(CP_List *list, int index)
{
	//TODO: Add a verification to ensure that the index is below list size
	int counter = 0;
	CP_Object *obj = NULL;
	if (index == 0)
	{
		obj = list->first;
		return obj;
	}

	if ((index == -1) || (index == (list->size - 1)))
	{
		obj = list->last;
		return obj;
	}

	CP_Object *context_iter = list->iter;

	for (cp_startIter(list); list->iter; cp_iterNext(list))
	{
		if (counter == index)
		{
			obj = list->iter;
			break;
		}
		counter++;
	}

	list->iter = context_iter;
	return obj;
}

void cp_emptyList(CP_List *list)
{
	CP_Object *current;
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
		cp_deleteObject(current);
		list->size--;
	}
	list->first = NULL;
	list->iter = NULL;
}
