/*
 * Copyright (C) 2012 - Magnun Leno da Silva
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

#ifndef _CP_UTIL_H_
#define _CP_UTIL_H_

/******** ENUMS ********/
typedef enum _BOOL_
{
	false = 0,
	true = 1
} bool;

typedef enum _CP_FILE_TYPE_
{
	CP_SVG,
	CP_PNG,
} CP_FileType;

typedef enum _CP_OBJECT_TYPE_
{
	CP_DATA=0,
	CP_COLOR=1,
	CP_LIST=2,
} CP_ObjectType;


/******** STRUCTS ********/
typedef struct _CP_OBJECT_
{
	void *content;
	CP_ObjectType type;
	struct _CP_OBJECT_ *next;
	struct _CP_OBJECT_ *previous;
} CP_Object;

typedef struct _CP_COLOR_
{
	double red;
	double green;
	double blue;
	double alpha;
} CP_Color;

typedef struct _CP_DATA_
{
	char *label;
	double x;
	double y;
	double z;
	double param_x;
	double param_y;
	double param_z;
	struct _CP_DATA_ *next;
} CP_Data;

typedef struct _CP_LIST_
{
	CP_Object *first;
	CP_Object *last;
	CP_Object *iter;
	CP_ObjectType type;
	int size;
} CP_List;

typedef struct _CP_CONTEXT_
{
	int width;
	int height;
	char *name;
	char *fname;
	CP_FileType ft;
	CP_Color *bgColor;
	CP_List *plotColor;
	CP_List *serie;

	cairo_surface_t *surface;
	cairo_t *cr;
} CP_Context;


void cp_addFileExtension(char **ppRetFilename, char *filename, CP_FileType ft);

#define cp_new(n, type) (type*)calloc(n, sizeof(type))

#endif // _CP_UTIL_H_
