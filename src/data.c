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
#include "data.h"

CP_Data *cp_newData(char *label, double x, double y, double z)
{
	CP_Data *data = cp_new(1, CP_Data);
	data->x = x;
	data->y = y;
	data->z = z;

	data->param_x = 0.0;
	data->param_y = 0.0;
	data->param_z = 0.0;

	data->label = label;
	return data;
}

void _cp_deleteData(void *content)
{
	free((CP_Data *)content);
}
