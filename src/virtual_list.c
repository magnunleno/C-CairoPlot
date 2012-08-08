/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (virtual_list.c) is part of C-CairoPlot.
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
#include "virtual_list.h"

CP_Node* _cp_newNode(void *content, void *(*destroyFunc)(void*))
{
	/*
	 * Allocates, initialize  and returns a new node with the specified 
	 * content/destroy function.
	 * 	@content: anything;
	 * 	@destroyFunc: function pointer that knows how to destroy this content;
	 * 	@return: pointer to the allocated node;
	 *
	 */
	CP_Node *node;
	node = cp_new(1, CP_Node);
	node->next = NULL;
	node->content = content;
	node->destroyer = destroyFunc;
	return node;
}

CP_Node* cp_destroyNode(CP_Node **node)
{
	CP_Node *next = NULL;
	if ((*node)->next)
		next = (*node)->next;
	if ((*node)->destroyer)
		(*(*node)->destroyer)((*node)->content);
	*node = NULL;
	return next;
}
