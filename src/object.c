/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (object.c) is part of C-CairoPlot.
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
#include "object.h"

CP_Object* cp_newObject(void *content, CP_ObjectType type)
{
	CP_Object *obj = cp_new(1, CP_Object);
	obj->type = type;
	obj->content = content;
	obj->next = NULL;
	obj->previous = NULL;
	return obj;
}

void cp_deleteObject(CP_Object *obj)
{
	CP_Data *data;
	switch(obj->type)
	{
		case CP_COLOR:
			free((CP_Color*)obj->content);
			break;
		case CP_DATA:
			free((CP_Data*)obj->content);
			break;
		case CP_LIST:
			printf("Tipo Lista\n");
			cp_emptyList((CP_List*)obj->content);
			free((CP_List*)obj->content);
			break;
		default:
			printf("** Tipo de variável (id=%i) ainda não suportada\n", obj->type);
	}
	obj->next = NULL;
	obj->previous = NULL;
	free(obj);
}
