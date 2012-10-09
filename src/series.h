/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (series.h) is part of C-CairoPlot.
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


/*
 * Okay, this is a tough one. It defines all series functions (I won't list them
 * all, they're probably be growing and growing...). 
 *
 * Until I found a better way to manage this (and keep it simple) I will keep
 * writing one function for every series type
 *
 */

#ifndef _CP_SERIES_H_
#define _CP_SERIES_H_

#include "util.h"
#include "data.h"
#include "color.h"

/****************************
 *  Basic series functions  *
 ****************************/
CP_Series *cp_newSeries(char *label, CP_ObjectType type);
#define __cp_append_node_series(series, obj)		\
	if (obj->type != series->type) 					\
	{ 												\
		cp_destroyObject(obj); 						\
		return false; 								\
	} 												\
	if (series->size == 0) 							\
		series->first = obj; 						\
	else 											\
	{ 												\
		series->last->next = obj; 					\
		obj->previous = series->last;				\
	} 												\
	series->last = obj; 							\
	series->size++

CP_Object *cp_getNodeN(CP_Series *series, int index);
void cp_emptySeries(CP_Series *series);
#define cp_startIter(series) series->iter = series->first
#define cp_iterNext(series) series->iter = series->iter->next
#define cp_iterNextCircular(series) series->iter = series->iter->next == NULL?series->first:series->iter->next
#define cp_iterUnpack(series, type) (type)(series->iter->content)
#define cp_destroySeries(series)						\
	if (series != NULL && series->first != NULL)	\
		cp_emptySeries(series);						\
	free(series);									\
	series = NULL

/****************************************
 *   Data series functions and macros   *
 ****************************************/
#define cp_newDataSeries(label) cp_newSeries(label, CP_DATA)
bool cp_appendData(CP_Series *series, char *label, double value);
#define cp_iterDataAttr(series, attr) ((CP_Data*)series->iter->content)->attr
#define cp_getDataNodeN(serie, index) ((CP_Data*)cp_getNodeN(series, index)->content)

double cp_maxDataSeries(CP_Series *series);
void cp_normDataSeries(CP_Series *series, double max, double top_value);

/*****************************************
 *   Point series functions and macros   *
 *****************************************/
#define cp_newPointSeries(label) cp_newSeries(label, CP_POINT)
bool cp_appendPoint(CP_Series *series, char *label, double x, double y);
#define cp_iterPointAttr(series, attr) (CP_Point*)(series->iter->content)->attr
#define cp_getPointNodeN(serie, index) ((CP_Point*)cp_getNodeN(series, index)->content)

/*****************************************
 *   Color series functions and macros   *
 *****************************************/
#define cp_newColorSeries() cp_newSeries(NULL, CP_COLOR)
bool cp_appendColor(CP_Series *series, double red, double green, double blue, double alpha);
bool cp_appendColorHTML(CP_Series *series, unsigned int value, double alpha);
bool cp_appendColorHSV(CP_Series *series, double hue, double saturation, double value, double alpha);
#define cp_iterColorAttr(series, attr) (CP_Color*)(series->iter->content)->attr
#define cp_getColorNodeN(serie, index) ((CP_Color*)cp_getNodeN(series, index)->content)

CP_Series *cp_generateFlatColorSeries(int count);

/*********************************************
 *   Grtadient series functions and macros   *
 *********************************************/
#define cp_newGradientSeries() cp_newSeries(NULL, CP_GRADIENT)
CP_Series *cp_generateGradientColorSeries(int count);

#endif // _CP_SERIES_H_
