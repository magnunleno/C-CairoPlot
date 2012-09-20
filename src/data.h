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
#include "list.h"

#ifndef _CP_DATA_H_
#define _CP_DATA_H_

typedef struct CP_DATA
{
	char *label;
	double x;
	double y;
	double z;
	double param_x;
	double param_y;
	double param_z;
	struct CP_DATA *next;
} CP_Data;

CP_Data *cp_newData(char *label, double x, double y, double z);
#define cp_newData1d(label, x) cp_newData(label, x, 0.0, 0.0)
#define cp_newData2d(label, x, y) cp_newData(label, x, y, 0.0)
#define cp_newData3d(label, x, y, z) cp_newData(label, x, y, z)

void _cp_deleteData(void *content);

#endif // _CP_DATA_H_
