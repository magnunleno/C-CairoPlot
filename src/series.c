/*
 * Copyright (C) 2012 - Magnun Leno

 * This file (series.c) is part of C-CairoPlot.
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
#include "series.h"

/*
 * This method allocates a new Series structure and returns a pointer
 * 		@label:
 * 			A label that might be used to name the series in the plot;
 * 		@type:
 * 			The object type defined at the enum _CP_OBJECT_TYPE_
 *
 * You probably won't use this function, you'll use some of the macros that
 * expands to this function, such as: cp_newDataSeries, cp_newColorSeries and
 * etc...
 *
 */
CP_Series *cp_newSeries(char *label, CP_ObjectType type)
{
	CP_Series *series;

	series = cp_new(1, CP_Series);
	series->label = label;
	series->type = type;
	series->first = NULL;
	series->last = NULL;
	series->iter = NULL;
	series->size = 0;

	return series;
}

/*
 * This method tries to appends a new Data to an existing Data series and
 * returns a "bool" indicating if the object was successfully appended or not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@label:
 * 			The data label
 * 		@value:
 * 			The data value
 *
 */
bool cp_appendData(CP_Series *series, char *label, double value)
{
	CP_Data *data;
	CP_Object *obj;

	data = cp_newData(label, value);
	obj = cp_newObject((void *)data, CP_DATA);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method tries to appends a new Point to an existing Point series and
 * returns a "bool" indicating if the object was successfully appended or not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@label:
 * 			The data label
 * 		@x:
 * 			The point's x coordinate
 * 		@y:
 * 			The point's y coordinate
 *
 */
bool cp_appendPoint(CP_Series *series, char *label, double x, double y)
{
	CP_Point *point;
	CP_Object *obj;

	point = cp_newPoint(label, x, y);
	obj = cp_newObject((void *)point, CP_POINT);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method tries to appends a new Color to an existing Color series and
 * returns a "bool" indicating if the object was successfully appended or not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@red:
 * 			The color's red component
 * 		@green:
 * 			The color's green component
 * 		@blue:
 * 			The color's blue component
 * 		@alpha:
 * 			The color's alpha component
 *
 */
bool cp_appendColor(CP_Series *series, double red, double green, double blue, double alpha)
{
	CP_Color *color;
	CP_Object *obj;

	color = cp_newColorRGB(red, green, blue, alpha);
	obj = cp_newObject((void *)color, CP_COLOR);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method tries to appends a new Color to an existing Color series and
 * returns a "bool" indicating if the object was successfully appended or not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@value:
 * 			The color's HTML value
 * 		@alpha:
 * 			The color's alpha component
 *
 */
bool cp_appendColorHTML(CP_Series *series, unsigned int value, double alpha)
{
	CP_Color *color;
	CP_Object *obj;

	color = cp_newColorHTML(value, alpha);
	obj = cp_newObject((void *)color, CP_COLOR);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method tries to appends a new Color to an existing Color series and
 * returns a "bool" indicating if the object was successfully appended or not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@hue:
 * 			The color's hue component
 * 		@saturation:
 * 			The color's saturation component
 * 		@value:
 * 			The color's value component
 * 		@alpha:
 * 			The color's alpha component
 *
 */
bool cp_appendColorHSV(CP_Series *series, double hue, double saturation, double value, double alpha)
{
	CP_Color *color;
	CP_Object *obj;

	color = cp_newColorHSV(hue, saturation, value, alpha);
	obj = cp_newObject((void *)color, CP_COLOR);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method tries to appends a new Gradient to an existing gradient series
 * and returns a "bool" indicating if the object was successfully appended or
 * not.
 * 		@series:
 * 			Existing series to which we will append the object
 * 		@gradient:
 * 			The existing gradient
 *
 */
bool cp_appendGradient(CP_Series *series, CP_Gradient *gradient)
{
	CP_Object *obj;

	obj = cp_newObject((void *)gradient, CP_GRADIENT);
	__cp_append_node_series(series, obj);

	return true;
}

/*
 * This method iters through the series and returns the node nth node.
 * 		@series:
 * 			Existing series in which we will search for the indexed node
 * 		@index:
 * 			The index of the node which will be returned. The index can be
 * 			bigger then the series size, it will be "adjusted" to the size of
 * 			the list. You can also use negative values the request the last
 * 			item for example (-1).
 *
 */
CP_Object *cp_getNodeN(CP_Series *series, int index)
{
	int counter;
	CP_Object *obj;
	CP_Object *context_iter;

	counter = 0;
	obj = NULL;

	// Assures that the index will always be below the series size
	index = index % series->size;

	// If first object avoid iterating through the series
	if (index == 0)
	{
		obj = series->first;
		return obj;
	}

	// If last object avoid iterating through the series
	if ((index == -1) || (index == (series->size - 1)))
	{
		obj = series->last;
		return obj;
	}

	// If negative convert to positive
	if (index < 0)
		index = series->size + index;

	// Saves the "context" to prevent from losing any "user iteration position"
	context_iter = series->iter;

	// Start iteration
	for (cp_startIter(series); series->iter; cp_iterNext(series))
	{
		if (counter == index)
		{
			obj = series->iter;
			break;
		}
		counter++;
	}

	// Restores the "user context"
	series->iter = context_iter;

	return obj;
}

/*
 * Finds and returns the max value from the specified series.
 * 		@series:
 * 			The series in witch the function will search.
 *
 */
double cp_maxDataSeries(CP_Series *series)
{

	double max, current;

	max= NEG_INF;
	current = 0;

	for (cp_startIter(series); series->iter; cp_iterNext(series))
	{
		current = cp_iterDataAttr(series, value);
		if (current > max)
			max = current;
	}

	return max;
}

/*
 * Normalizes the series data based on the values specified on max and
 * top_value.
 * 		@series:
 * 			Series to be normalized
 * 		@max:
 * 			Every value in the series will be normalized using max as the
 * 			"maximum scale";
 * 		@top_value:
 * 			The top value that you'll find in the series after the
 * 			normalization.
 *
 * Ex 1: If I have a series with the values 10, 5, 2 and I normalize it with
 * max=10 and top_value=1 the resulting series will be 1, 0.5, 0.2
 *
 * Ex 2: If I have a series with the values 10, 5, 2 and I normalize it with
 * max=10 and top_value=2 the resulting series will be 2, 1, 0.4
 *
 * Ex 3: If I have a series with the values 10, 5, 2 and I normalize it with
 * max=20 and top_value=1 the resulting series will be 0.5, 0.25, 0.1
 *
 * Ex 4: If I have a series with the values 10, 5, 2 and I normalize it with
 * max=20 and top_value=2 the resulting series will be 1, 0.5, 0.2
 *
 */
void cp_normDataSeries(CP_Series *series, double max, double top_value)
{
	CP_Data *current;

	for (cp_startIter(series); series->iter; cp_iterNext(series))
	{
		current = cp_iterUnpack(series, CP_Data*);
		current->norm_value = (current->value/max) * top_value;
	}
}

/*
 * This function will generate a series of N colors using the HSV space.
 * 		@size:
 * 			The number of colors to be generated.
 *
 */
CP_Series *cp_generateFlatColorSeries(int size)
{
	int counter;
	double step;
	CP_Series *series;
	CP_Color *c;

	// Calculates the step (trying to get the "center" of the Hue space)
	step = 360/(size + 1);

	series = cp_newColorSeries();
	for (counter=1; counter <= size; counter++)
		cp_appendColorHSV(series, step*counter, 0.6, 0.80, 1.0);

	return series;

}

/*
 * This function generate a series of N gradients using the HSV space.
 * 		@size:
 * 			The number of colors to be generated.
 *
 */
CP_Series *cp_generateGradientColorSeries(int count)
{
	// TODO: Review this function
	int counter;
	double start, end, step;
	CP_Series *series;
	CP_Gradient *gradient;

	series = cp_newGradientSeries();
	start = 60;
	end = 420.0;
	step = (end - start)/(count + 1);
	//double step = (end - start)/(count);

	CP_Color *c;
	for (counter=1; counter <= count; counter++)
	{
		gradient = cp_newGradientHSV(0.0, start+(step*counter), 0.7, 0.5, 1.0);
		cp_addColorStopHSV(gradient, 1.0, start+(step*counter), 0.6, 0.8, 1.0);
		cp_appendGradient(series, gradient);
	}
	return series;
}

/*
 * Deletes all the content of the specified series
 * 		@series:
 * 			The series which contents will be erased
 *
 */
void cp_emptySeries(CP_Series *series)
{
	CP_Object *current;

	cp_startIter(series);
	while (series->iter)
	{
		// point to current object
		current = series->iter;
		// point iter to next object
		series->iter = current->next;
		// point the first to the current object
		series->first = series->iter;
		// destroy object
		cp_destroyObject(current);
		// decrement the series size
		series->size--;
	}
	// point everything to null
	series->first = NULL;
	series->iter = NULL;
}
