/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (util.h) is part of C-CairoPlot.
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

#include <cairo.h>
#include <cairo-svg.h>
#include <math.h>
#include "color.h"

/*
 * Hi there stranger! This is the C-CairoPlot most basic file. It stores all
 * enums, structures and the most basic constants. If you're willing to hack
 * this labrary you should really start reading this file. 
 *
 */

#ifndef _CP_UTIL_H_
#define _CP_UTIL_H_

/*
 * Some math definitions that will help me finding maximum and minimum series
 * values
 */
#define POS_INF 1.0/0.0
#define NEG_INF (1.0/0.0)*-1

/******** ENUMS ********/
// Why doesn't C lang defines this by default? o.O
typedef enum _BOOL_
{
	false = 0,
	true = 1
} bool;

// Supported file extensions
typedef enum _CP_FILE_TYPE_
{
	CP_SVG,
	CP_PNG,
} CP_FileType;

// Supported Object types
typedef enum _CP_OBJECT_TYPE_
{
	CP_COLOR,
	CP_GRADIENT,
	CP_DATA,
	CP_POINT,
} CP_ObjectType;

typedef enum _CP_DRAWABLE_PARTS_
{
	CP_DRAW_BACKGOUND	= 0x00001,
	CP_DRAW_X_AXIS		= 0x00002,
	CP_DRAW_Y_AXIS 		= 0x00004,
	CP_DRAW_GRID		= 0x00008,
	CP_DRAW_BOX			= 0x00010,
} CP_DrawableType;

/******** STRUCTS ********/
// Color structure
typedef struct _CP_COLOR_
{
	double red;
	double green;
	double blue;
	double alpha;
} CP_Color;

// Gradient structure
typedef struct _CP_GRADIENT_
{
	double position;
	CP_Color *color;
	struct _CP_GRADIENT_ *next;
} CP_Gradient;

// Object structure
typedef struct _CP_OBJECT_
{
	void *content;
	CP_ObjectType type;
	struct _CP_OBJECT_ *next;
	struct _CP_OBJECT_ *previous;
} CP_Object;

// Point structure
typedef struct _CP_POINT_
{
	char *label;
	double x;
	double y;
	double norm_x;
	double norm_y;
} CP_Point;

// Data structure
typedef struct _CP_DATA_
{
	char *label;
	double value;
	double norm_value;
} CP_Data;

// Series structure
typedef struct _CP_SERIES_
{
	char *label;
	CP_Object *first;
	CP_Object *last;
	CP_Object *iter;
	CP_ObjectType type;
	int size;
} CP_Series;

// Context structure
typedef struct _CP_CONTEXT_
{
	int width;
	int height;
	char *name;

	CP_Color *bgColor;
	CP_Gradient *bgGradient;
	CP_Series *colors;
	bool flatColors;
	bool draw;

	double leftMargin;
	double rightMargin;
	double bottomMargin;
	double topMargin;


	char *fname;
	cairo_surface_t *surface;
	cairo_t *cr;
} CP_Context;

// Bar Plot settings structure
typedef struct _CP_BARPLOT_SETTINGS_
{
	bool roundBorders;
	double borderRadius;
	double barPadding;
	double horBoxPadding;
	double verBoxPadding;

	// TODO: Implement orientation;
} CP_BarPlotSettings;

/***** Functions *****/
void cp_addFileExtension(char **ppRetFilename, char *filename, CP_FileType ft);
CP_Object* cp_newObject(void *content, CP_ObjectType type);
void cp_destroyObject(CP_Object *obj);

/***** Macros ******/
#define cp_new(n, type) (type*)calloc(n, sizeof(type))

#endif  // _CP_UTIL_H_
