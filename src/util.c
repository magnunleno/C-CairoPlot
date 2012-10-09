/*
 * Copyright (C) 2012 - Magnun Leno
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

/* Adds an extension to a given filename
 *     @ppRetFilename:
 *     		A pointer to the destiny filename;
 *     @filename:
 *     		String containing the filename;
 *     @ft:
 *     		Enum which defines the extension;
 *
 */
void cp_addFileExtension(char **ppRetFilename, char *filename, CP_FileType ft)
{
	if (*ppRetFilename != NULL)
		free(*ppRetFilename);

	// This switch explains itself
	switch(ft)
	{
		case CP_SVG:
			*ppRetFilename = cp_new(strlen(filename)+strlen(".svg")+1, char);
			strcpy(*ppRetFilename, filename);
			strcat(*ppRetFilename, ".svg");
			break;
		case CP_PNG:
			*ppRetFilename = cp_new(strlen(filename)+strlen(".png")+1, char);
			strcpy(*ppRetFilename, filename);
			strcat(*ppRetFilename, ".png");
			break;
	}
}

/*
 * Returns a new allocated object with its contents
 * 		@content:
 * 			"generic" pointer to the stored object;
 * 		@type:
 * 			Define the type of the stored object. This information is useful
 * 			when unpacking, deleting and iterating through objects;
 *
 */
CP_Object* cp_newObject(void *content, CP_ObjectType type)
{
	CP_Object *obj;

	obj = cp_new(1, CP_Object);
	obj->type = type;
	obj->content = content;
	obj->next = NULL;
	obj->previous = NULL;

	return obj;
}

/*
 * Generic function that destroy an object and its contents based on the object
 * type (defined at obj->type);
 * 		@obj:
 * 			The object to be destroyed
 *
 */
void cp_destroyObject(CP_Object *obj)
{
	CP_Data *data;
	switch(obj->type)
	{
		case CP_DATA:
			free((CP_Data*)obj->content);
			break;
		case CP_POINT:
			free((CP_Point*)obj->content);
			break;
		case CP_COLOR:
			free((CP_Color*)obj->content);
			break;
		case CP_GRADIENT:
			_cp_destroyGradient(((CP_Gradient**)obj->content));
			break;
		default:
			printf("** Variable Type (id=%i) isn't supported yet.\n", obj->type);
	}
	obj->next = NULL;
	obj->previous = NULL;
	free(obj);
}
