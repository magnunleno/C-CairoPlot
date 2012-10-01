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

#ifndef _CP_COLOR_H_
#define _CP_COLOR_H_

#include "util.h"
#include "object.h"

CP_Object *cp_newColor(double red, double green, double blue, double alpha);
#define cp_appendColor(list, red, green, blue, alpha) cp_appendNode(list, CP_Color(red, green, blue, alpha))
#define cp_colorAttr(obj, attr) ((CP_Color*)obj->content)->attr

void _cp_deleteColor(void *content);
#endif // _CP_COLOR_H_
