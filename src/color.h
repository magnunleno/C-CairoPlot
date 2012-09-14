/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (color.h) is part of C-CairoPlot.
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
#include "list_util.h"

#ifndef _CP_COLOR_H
#define _CP_COLOR_H

typedef struct CP_COLOR
{
	double red;
	double green;
	double blue;
	double alpha;
	struct CP_COLOR *next;
} CP_Color;

typedef struct CP_COLOR_LIST
{
	CP_BASELIST(CP_Color);
} CP_ColorList;

CP_Color *cp_newColor(double red, double green, double blue, double alpha);
#define cp_appendColor(list, red, green, blue, alpha) cp_appendNode(list, cp_newColor(red, green, blue, alpha))

CP_ColorList *cp_newColorList();
void cp_emptyColorList(CP_ColorList *list);
#define cp_deleteColor(color) free(color)
#define cp_deleteColorList(colotList) \
	free(colorList);\
	colorList = NULL

#endif // _CP_COLOR_H
