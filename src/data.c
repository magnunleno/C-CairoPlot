/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (data.c) is part of C-CairoPlot.
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

/*
 * Returns a pointer to the newly created Data structure
 * 		@label:
 * 			A string used to give a label to the value;
 * 		@value:
 * 			The value that will be plotted
 *
 */
CP_Data *cp_newData(char *label, double value)
{
	CP_Data *data = cp_new(1, CP_Data);

	data->label = label;
	data->value = value;
	data->norm_value = 0.0;

	return data;
}

/*
 * Returns a pointer to the newly created Point structure
 * 		@label:
 * 			A string used to give a label to the value;
 * 		@x:
 * 			The value that will be plotted in the x axis
 * 		@y:
 * 			The value that will be plotted in the y axis
 *
 */
CP_Point *cp_newPoint(char *label, double x, double y)
{
	CP_Point *point = cp_new(1, CP_Point);

	point->label = label;
	point->x = x;
	point->y = y;
	point->norm_x = 0.0;
	point->norm_y = 0.0;

	return point;
}
