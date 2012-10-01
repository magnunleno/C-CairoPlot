/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (object.h) is part of C-CairoPlot.
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


#ifndef _CP_OBJECT_H_
#define _CP_OBJECT_H_

#include "util.h"
#include "color.h"
#include "data.h"
#include "list.h"

CP_Object* cp_newObject(void *content, CP_ObjectType type);
#define cp_objectUnpack(obj, type) (type)(obj->content)

void cp_deleteObject(CP_Object *object);

#endif // _CP_OBJECT_H_
