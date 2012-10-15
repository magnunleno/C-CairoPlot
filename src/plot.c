/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (plot.c) is part of C-CairoPlot.
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
#include "plot.h"

/*
 * Function resposible for drawing the plot background based on the settings
 * defined at CP_Context *ctx
 * 		@ctx:
 * 			CP_Context which point to the plot context.
 *
 * This function uses the following settings:
 * 	- bgGradient: pointer to a CP_Gradient structure. This structure defines
 * 	the gradient settings.
 * 	- bgColor: pointer to a CP_Color structure. This structure defines the flat
 * 	color to be used in the background
 *
 * If both pointers point to some contents C-CairoPlot will prefer to use a
 * Gradient over a flat color.
 * If none color is supported (neither flat or gradient) this function draws a
 * default background.
 *
 */
void cp_drawBackground(CP_Context *ctx)
{
	// Gradient Color
	if (ctx->bgGradient != NULL)
	{
		// TODO: Gradients should let users define the "orientation"
		// (left to right, right to left, up to down ou down to up) and the
		// gradient type (liner, radial or mesh)
		// mesh demo: https://gist.github.com/3159434
		cairo_pattern_t *pat;
		CP_Gradient *iter;
		pat = cairo_pattern_create_linear(0.5, 0.0, 0.5, 1);
		
		for (iter=ctx->bgGradient; iter; iter=iter->next)
			cairo_pattern_add_color_stop_rgba(pat, iter->position,
					iter->color->red, iter->color->green,
					iter->color->blue, iter->color->alpha);

		cairo_rectangle(ctx->cr, 0.0, 0.0, 1.0, 1.0);
		cairo_set_source(ctx->cr, pat);
		cairo_fill(ctx->cr);
		cairo_pattern_destroy(pat);
		return;
	}
	// Flat color
	else if (ctx->bgColor != NULL)
	{
		cairo_set_source_rgba(ctx->cr, ctx->bgColor->red,
				ctx->bgColor->green, ctx->bgColor->blue,
				ctx->bgColor->alpha);
		cairo_rectangle(ctx->cr, 0, 0, 1, 1);
		cairo_fill(ctx->cr);
	}
	else
	{
		// Default Color
		cairo_pattern_t *pat;
		pat = cairo_pattern_create_linear(0.5, 0.0, 0.5, 1);
		cairo_pattern_add_color_stop_rgba(pat, 0.0, 1.0, 1.0, 1.0, 1.0);
		cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.9, 0.9, 0.9, 1.0);
		cairo_rectangle(ctx->cr, 0.0, 0.0, 1.0, 1.0);
		cairo_set_source(ctx->cr, pat);
		cairo_fill(ctx->cr);
		cairo_pattern_destroy(pat);
		return;
	}

}

/*
 * This function draws the plot box (a square around the plotting area).
 *		ctx: CP_Context structure in which the box will bre drawn;
 *		x0:	the starting point in the X coordinate;
 *		y0:	the starting point in the Y coordinate;
 *		x1:	the ending point in the X coordinate;
 *		y1:	the ending point in the Y coordinate;
 */
void cp_drawBox(CP_Context *ctx, double x0, double y0, double x1, double y1)
{
    cairo_set_line_width(ctx->cr, DEFAULT_LINE_WIDTH);

	cairo_set_source_rgba(ctx->cr, 0.7, 0.7, 0.7, 1.0);
	cairo_rectangle(ctx->cr, x0, y0, x1, y1);
	cairo_stroke(ctx->cr);

    cairo_set_line_width(ctx->cr, DEFAULT_LINE_WIDTH);
}

/*
 * This function initializes any supported environment (Cairo Surface and Cairo
 * main object, cairo_t). It must be called before ANY cairo operation.
 * 		@context:
 * 			CP_Context which holds the pointers to the cairo structures, and
 * 			other plot settings.
 * 		@ft:
 * 			File Type, to be plotted. For supported filetypes check the util.h
 * 			file (_CP_FILETYPE_ structure).
 */
void cp_initEnv(CP_Context *context, CP_FileType ft)
{
	if (ft == CP_PNG){
		context->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
				context->width, context->height);
	}else{
		cp_addFileExtension(&(context->fname), context->name, ft);
		context->surface = cairo_svg_surface_create(context->fname,
				context->width, context->height);
		cairo_svg_surface_restrict_to_version(context->surface,
				CAIRO_SVG_VERSION_1_2);
	}
	context->cr = cairo_create(context->surface);
}

/*
 * This function terminates the environment (Cairo Surface and Cairo main
 * object, cairo_t). It must be called at the end of the plot.
 * 		@context:
 * 			CP_Context which holds the pointers to the cairo structures, and
 * 			other plot settings.
 * 		@ft:
 * 			File Type, to be plotted. For supported filetypes check the util.h
 * 			file (_CP_FILETYPE_ structure).
 */
void cp_endEnv(CP_Context *context, CP_FileType ft)
{
	if (ft == CP_PNG){
		cp_addFileExtension(&(context->fname), context->name, ft);
		cairo_surface_write_to_png(context->surface, context->fname);
	}else{
		cairo_surface_flush(context->surface);
		cairo_surface_finish(context->surface);
	}
	cairo_destroy(context->cr);
	cairo_surface_destroy(context->surface);
	context->cr = NULL;
	context->surface = NULL;
}
