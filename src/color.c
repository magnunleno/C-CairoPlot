/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (color.c) is part of C-CairoPlot.
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
#include "color.h"

CP_Color *cp_newColor(double red, double green, double blue, double alpha)
{
	//TODO: Check if is betwen 0 and 1
	CP_Color *color = cp_new(1, CP_Color);
	color->red = red;
	color->green = green;
	color->blue = blue;
	color->alpha = alpha;
	return color;
}

CP_ColorList *cp_newColorList()
{
	CP_ColorList *list = cp_new(1, CP_ColorList);
	CP_INIT_LIST(list);
	return list;
}

void cp_emptyColorList(CP_ColorList *list)
{
	CP_Color *current = NULL;
	cp_startIter(list);
	while (list->iter)
	{
		current = list->iter;
		list->iter = current->next;
		if(current == list->last)
			list->last = NULL;
		list->first = list->iter;
		cp_deleteColor(current);
		list->size--;
	}
	list->first = NULL;
	list->iter = NULL;
}
