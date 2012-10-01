/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (context.c) is part of C-CairoPlot.
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
#include <cairo.h>
#include <cairo-svg.h>
#include "context.h"

CP_Context* cp_newContext(char *name, int width, int height)
{
	CP_Context *context = cp_new(1, CP_Context);
	context->serie = NULL;
	context->bgColor = NULL;
	context->plotColor = NULL;
	context->fname = NULL;
	context->ft = CP_PNG;
	context->name = name;
	context->width = width;
	context->height = height;

	context->surface = NULL;
	context->cr = NULL;
	return context;
}

void cp_contextAddColorList(CP_Context *context, CP_List *colorList)
{
	if (context->plotColor == NULL)
		context->plotColor = cp_newList(CP_LIST);
	cp_appendSubList(context->plotColor, colorList);
	return;
}

void cp_contextAddDataList(CP_Context *context, CP_List *dataList)
{
	if (context->serie == NULL)
		context->serie = cp_newList(CP_LIST);
	cp_appendSubList(context->serie, colorList);
	return;
}

/*
void cp_drawBackground(CP_Context *context)
{
    cairo_pattern_t *pat;
	pat = cairo_pattern_create_linear(0.5, 0, 0.5, 1);
	if(context->bgColor == NULL){
		cairo_pattern_add_color_stop_rgba(pat, 0.0, 1.0, 1.0, 1.0, 1.0);
		cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.9, 0.9, 0.9, 1.0);
		cairo_rectangle(context->cr, 0, 0, 1.0, 1.0);
		cairo_set_source(context->cr, pat);
		cairo_fill(context->cr);
		cairo_pattern_destroy(pat);
	}else{
		cairo_set_source_rgba(context->cr, context->bgColor->red, context->bgColor->green, context->bgColor->blue, context->bgColor->alpha);
		cairo_rectangle(context->cr, 0, 0, context->width, context->height);
		cairo_fill(context->cr);
	}
}

void cp_initEnv(CP_Context *context)
{
	if (context->ft == CP_PNG){
		printf("png\n");
		context->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
				context->width, context->height);
	}else{
		printf("no png\n");
		cp_addFileExtension(&(context->fname), context->name, context->ft);
		context->surface = cairo_svg_surface_create(context->fname,
				context->width, context->height);
		cairo_svg_surface_restrict_to_version(context->surface,
				CAIRO_SVG_VERSION_1_2);
	}
	context->cr = cairo_create(context->surface);
}

void cp_endEnv(CP_Context *context)
{
	if (context->ft == CP_PNG){
		cp_addFileExtension(&(context->fname), context->name, context->ft);
		cairo_surface_write_to_png(context->surface, context->fname);
		cairo_destroy(context->cr);
		cairo_surface_destroy(context->surface);
	}else{
		cairo_surface_flush(context->surface);
		cairo_surface_finish(context->surface);
		cairo_surface_destroy(context->surface);
		cairo_destroy(context->cr);
	}
}
*/

/*
void cp_plot(CP_Context *context)
{
	//cp_initEnv(context);
	//_cp_hbarPlot(context, width, height);
	//cp_endEnv(context);

	//switch(ft){
	//	case CP_SVG:
	//		cp_initSvgEnv(context, width, height, filename);
	//		break;
	//	case CP_PNG:
	//		cp_initPngEnv(context, width, height);
	//		break;
	//}

	//_cp_hbarPlot(context, width, height);

	//switch(ft){
	//	case CP_SVG:
	//		cp_endSvgEnv(context);
	//		break;
	//	case CP_PNG:
	//		cp_endPngEnv(context, filename);
	//		break;
	//}
}
*/
