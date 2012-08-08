/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (util.c) is part of C-CairoPlot.
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
#include <string.h>
#include "util.h"

void cp_addFileExtension(char **ppRetFilename, char *filename, CP_FileType ft)
{
	/* Adds an extension to a given filename
	 *     @ppRetFilename: A pointer to the destiny filename;
	 *     @filename: String containing the filename;
	 *     @ft: Enum which defines the extension;
	 *
	 */
	if (*ppRetFilename != NULL)
		free(*ppRetFilename);

	*ppRetFilename = cp_new(strlen(filename)+5, char);
	strcpy(*ppRetFilename, filename);
	switch(ft)
	{
		case CP_SVG:
			strcat(*ppRetFilename, ".svg");
			break;
		case CP_PNG:
			strcat(*ppRetFilename, ".png");
			break;
	}
}
