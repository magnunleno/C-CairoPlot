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

#ifndef _CP_UTIL_H_
#define _CP_UTIL_H_

typedef enum BOOL
{
	false = 0,
	true = 1
} bool;

typedef enum CP_FILE_TYPE
{
	CP_SVG,
	CP_PNG,
} CP_FileType;

void cp_addFileExtension(char **ppRetFilename, char *filename, CP_FileType ft);

#define cp_new(n, type) (type*)calloc(n, sizeof(type))

#endif // _CP_UTIL_H_
