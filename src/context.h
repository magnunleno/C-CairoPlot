/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (context.h) is part of C-CairoPlot.
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

#include "color.h"

#ifndef _CP_CONTEXT_H_
#define _CP_CONTEXT_H_

CP_Context* cp_newContext(char *name, int width, int height);
void cp_contextAddColorList(CP_Context *context, CP_List *color);
/*
void cp_drawBackground(CP_Context *context);
void cp_context(CP_Context *context);
void cp_initEnv(CP_Context *context);
void cp_endEnv(CP_Context *context);


//#define cp_initEnv(context)												\
//	if (context->ft == CP_PNG){											\
//		context->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, \
//				context->width, context->height);								\
//	}else{																\
//		cp_addFileExtension(&(context->fname), context->name, context->ft);		\
//		context->surface = cairo_svg_surface_create(context->fname,			\
//				context->width, context->height);								\
//		cairo_svg_surface_restrict_to_version(context->surface,			\
//				CAIRO_SVG_VERSION_1_2);									\
//	}
//
//#define cp_endEnv(context)												\
//	if (context->ft == CP_PNG){										\
//		cp_addFileExtension(&(context->fname), context->name, context->ft);	\
//		cairo_surface_write_to_png(context->surface, context->fname);		\
//		cairo_destroy(context->cr);									\
//		cairo_surface_destroy(context->surface);						\
//	}else{															\
//		cairo_surface_flush(context->surface);							\
//		cairo_surface_finish(context->surface);						\
//		cairo_surface_destroy(context->surface);						\
//		cairo_destroy(context->cr);									\
//	}

#define cp_setBgColor(context, red, green, blue)				\
	if (context->bgColor != NULL)								\
		free(context->bgColor);								\
	context->bgColor = cp_newColor(red, green, blue, 1.0)

#define cp_deleteContext(context)								\
	if (context->bgColor != NULL)							\
		free(context->bgColor);							\
	free(context);											\
	context = NULL

//CP_Context* cp_drawBackground(char *name, int width, int height);
*/

#endif // _CP_CONTEXT_H_

