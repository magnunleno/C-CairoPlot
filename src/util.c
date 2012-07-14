/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (util.c) is part of CairoPlot.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

char* CP_addFileExtension(char *filename, CP_FileType ft)
{
	/* Adds an extension to a given filename
	 *     @filename: String containing the filename;
	 *     @ft: Enum which defines the extension;
	 *     @return: pointer to the new allocated string (filenameExt);
	 *
	 */
	char *filenameExt;
	filenameExt = (char*)calloc(strlen(filename)+5, sizeof(char));
	strcpy(filenameExt, filename);
	switch(ft)
	{
		case CP_SVG:
			strcat(filenameExt, ".svg");
			break;
		case CP_PNG:
			strcat(filenameExt, ".png");
			break;
	}
	return filenameExt;
}
