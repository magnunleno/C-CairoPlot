/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (util.h) is part of CairoPlot.
 * 
 * CairoPlot is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * CairoPlot is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * CairoPlot. If not, see http://www.gnu.org/licenses/.
 *
 */

#ifndef _CP_UTIL_H_
#define _CP_UTIL_H_

typedef enum CP_OBJ_TYPE
{
	CP_LIST_TYPE,
	CP_CIRCULAR_LIST_TYPE,
	CP_NODE_TYPE,
	CP_DATA_TYPE,
	CP_SERIE_TYPE,
	CP_COLOR_TYPE,
} CP_ObjectType;

typedef enum CP_FILE_TYPE
{
	CP_SVG,
	CP_PNG,
} CP_FileType;

typedef enum BOOL
{
	false = 0,
	true = 1
} bool;

char* CP_addFileExtension(char *filename, CP_FileType ft);

#endif // _CP_UTIL_H_
