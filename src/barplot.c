/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (barplot.c) is part of C-CairoPlot.
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
#include "barplot.h"

/*
 * This function returns a newly allocated CP_BarPlotSettings structure with
 * it's defaults settings.
 *
 */
CP_BarPlotSettings *cp_newBarPlotSettings()
{
	CP_BarPlotSettings *sett = cp_new(1, CP_BarPlotSettings);
	sett->barPadding = 0.005;
	sett->borderRadius = 0.04;
	return sett;
}

/*
 * This functions draws a bar at a desired location. The bar can be rounded or
 * not.
 * 		@ctx:
 * 			Context in which the bar will be plotted;
 * 		@sett:
 * 			The CP_BarPlotSettings, it defines some specific settings used in
 * 			this function like border radius and others.
 * 		@x0:
 * 			Define the start point in the X axis (from left to right).
 * 		@y0:
 * 			Define the start point in the Y axis (from top to bottom).
 * 		@width:
 * 			Define the bar width. In fact, this is the Data value.
 * 		@height:
 * 			Define the bar height. This value an vary depending on the values
 * 			defined by the bar padding.
 */
void cp_drawBar(CP_Context *ctx, CP_BarPlotSettings *sett, double x0, double y0, double width, double height)
{
	// Go to the Top left
	cairo_move_to(ctx->cr, x0, y0);

	// Line to top right 
	cairo_line_to(ctx->cr, x0+width-sett->borderRadius, y0);

	// Line to bottom right 
	cairo_curve_to(ctx->cr, x0+width, y0, x0+width, y0, x0+width, y0+sett->borderRadius);
	cairo_line_to(ctx->cr, x0+width, y0+height-sett->borderRadius);

	// Line to bottom left 
	cairo_curve_to(ctx->cr, x0+width, y0+height, x0+width, y0+height, x0+width-sett->borderRadius, y0+height);
	cairo_line_to(ctx->cr, x0, y0+height);

	// Close box (go to top left)
	cairo_close_path(ctx->cr);
}

/*
 * This is the "Main Bar Plot" function. It calculates all values and call
 * other functions. It also initialize and clean the Cairo Environment.
 * 		@ctx:
 * 			CP_Context structure which holds the generic plot settings.
 * 		@sett:
 * 			CP_BarSettings structure which holds the specific bar plot
 * 			settings.
 * 		@series:
 * 			Series structure which stores the plotting values.
 * 		@ft:
 * 			The file type in which the plot will be drawn.
 */
void cp_barPlot(CP_Context *ctx, CP_BarPlotSettings *sett, CP_Series *series, CP_FileType ft)
{
	// TODO: Should this method distinct simple series from "nested series"?

	// Needed variables
	cairo_pattern_t *pat;
	CP_Color *color;
	CP_Gradient *gradient, *iter;
	double plottable_width, plottable_height, slot_size, x0, y0;

	// Initializes the Cairo Environment
	cp_initEnv(ctx, ft);

	// Set some basic configurations to Cairo
    cairo_set_line_width(ctx->cr, DEFAULT_LINE_WIDTH);
	cairo_set_line_join(ctx->cr, CAIRO_LINE_JOIN_MITER);

	// Translate the coordinate systems. Now the plot area is a 1x1 square.
	cairo_translate(ctx->cr, 0, 0);
	cairo_scale(ctx->cr, ctx->width, ctx->height);

	// Checks if the user provided us some colors
	if (ctx->colors == NULL)
	{
		if (ctx->flatColors == true)
			//Generate some flat colors
			ctx->colors = cp_generateFlatColorSeries(series->size);
		else
			//Generate some gradients
			ctx->colors = cp_generateGradientColorSeries(series->size);
	}


	/*********************************
	 * Graph Plotting pre-requisites *
	 *********************************/
	// Calculate the "plotting area"
	plottable_width = 1 - (ctx->left_margin + ctx->right_margin);
	plottable_height = 1 - (ctx->top_margin + ctx->bottom_margin);

	// TODO: should this vary depending on the orientation?
	// Calculates the slot size (based on how many bars will be plotted)
	slot_size = (plottable_height/series->size) - sett->barPadding;

	// Starting points
	x0 = ctx->left_margin;
	y0 = ctx->top_margin + (sett->barPadding/2);

	// Normalizes the data series
	cp_normDataSeries(series, cp_maxDataSeries(series), plottable_width);


	/**********************
	 * Pre graph plotting *
	 **********************/
	// Draw some optional things...
	cp_drawBackground(ctx);


	/******************
	 * Graph Plotting *
	 ******************/
	cp_startIter(ctx->colors);
	for (cp_startIter(series); series->iter; cp_iterNext(series))
	{
		// Draw Bar
		cp_drawBar(ctx, sett, x0, y0, cp_iterDataAttr(series, norm_value), slot_size);

		// Data Series will be colored with flat colors
		if (ctx->colors->type == CP_COLOR)
		{
			// unpack the series item as a CP_Color
			color = cp_iterUnpack(ctx->colors, CP_Color*);

			// Set color and Paint
			cairo_set_source_rgba(ctx->cr, color->red, color->green, color->blue, color->alpha);
			cairo_fill(ctx->cr);
		}
		// Data Series will be colored with gradients
		else
		{
			// unpack the series item as a CP_Gradient
			gradient = cp_iterUnpack(ctx->colors, CP_Gradient*);

			// Initializes the cairo_pattern_t
			pat = cairo_pattern_create_linear(x0, y0, x0, y0+slot_size);
			for (iter=gradient; iter; iter = iter->next)
			{
				cairo_pattern_add_color_stop_rgba(pat, iter->position, iter->color->red, iter->color->green, iter->color->blue, iter->color->alpha);
			}

			// Set color and Paint
			cairo_set_source(ctx->cr, pat);
			cairo_fill(ctx->cr);
			cairo_pattern_destroy(pat);
		}

		// Calculates next y0 point
		y0 += slot_size + sett->barPadding;
		printf("Ending Y = %f\n", y0+slot_size);
		// Iterate to next color
		cp_iterNextCircular(ctx->colors);
	}

	// Restore x0, y0
	x0 = ctx->left_margin;
	y0 = ctx->top_margin;

	/**********************
	 * Post graph plotting *
	 **********************/
	// Draw some optional things...
	if (ctx->drawBox)
		cp_drawBorder(ctx, x0, y0, plottable_width, plottable_height);
	if (ctx->drawAxis)
		cp_drawAxis(ctx, x0, y0, plottable_width, plottable_height);
	printf("Ending border = %f\n", y0+plottable_height);

	// End Cairo Environment
	cp_endEnv(ctx, ft);
}
