/*
 * Copyright (C) 2012 - Magnun Leno
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

/*
 * This function initializes a Context Structure used to set the most generic
 * settings to all plots.
 * 		@name: 
 * 			The name of the plot
 * 		@width: 
 * 			The width (in pixels) of the output image
 * 		@height: 
 * 			The height (in pixels) of the output image
 *
 */
CP_Context* cp_newContext(char *name, int width, int height)
{
	CP_Context *context = cp_new(1, CP_Context);
	context->name = name;
	context->width = width;
	context->height = height;

	context->bgColor = NULL;
	context->colors = NULL;
	context->flatColors = true;

	context->fname = NULL;
	context->surface = NULL;
	context->cr = NULL;

	context->drawAxis = true;
	context->drawBox = true;
	return context;
}

/*
 * Function that safely sets the Background color (using RGB) to the CP_Context
 * structure
 * 		@ctx:
 * 			CP_Context structure that holds the background color.
 * 		@red: 
 * 			Red part of color (from 0 to 255)
 * 		@green: 
 * 			Green part of color (from 0 to 255)
 * 		@blue: 
 * 			Blue part of color (from 0 to 255)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
void cp_setBgColorRGB(CP_Context *ctx, int red, int green, int blue, double alpha)
{
	if (ctx->bgColor != NULL)
		free(ctx->bgColor);
	ctx->bgColor = cp_newColorRGB(red, green, blue, alpha);
}

/*
 * Function that safely sets the Background color (using HTML) to the CP_Context
 * structure
 * 		@ctx:
 * 			CP_Context structure that holds the background color.
 * 		@value: 
 * 			The HTML notation which used hexadecimal numbers to define the RGB
 * 			values (values like 0xADFAA0)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
void cp_setBgColorHTML(CP_Context *ctx, unsigned int value, double alpha)
{
	if (ctx->bgColor != NULL)
		free(ctx->bgColor);
	ctx->bgColor = cp_newColorHTML(value, alpha);
}

/*
 * Function that safely sets the Background color (using HSV) to the CP_Context
 * structure
 * 		@ctx:
 * 			CP_Context structure that holds the background color.
 * 		@hue: 
 * 			Between 0 and 360º. Determines the color family.
 * 		@saturation: 
 * 			Between 0 and 1. Is the degree of strength or purity (how much
 * 			white is added to the color). 1.0 == No white
 * 		@value:
 *			Between 0 and 1. Determines the color brightness (how much black is
 *			added to the color). 1.0 == No Black
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
void cp_setBgColorHSV(CP_Context *ctx, double hue, double saturation, double value, double alpha)
{
	if (ctx->bgColor != NULL)
		free(ctx->bgColor);
	ctx->bgColor = cp_newColorHSV(hue, saturation, value, alpha);
}

/*
 * Function that safely sets the Background gradient (using RGB) to the
 * CP_Context structure
 * 		@ctx:
 * 			CP_Context structure that holds the background gradient.
 * 		@red: 
 * 			Red part of color (from 0 to 255)
 * 		@green: 
 * 			Green part of color (from 0 to 255)
 * 		@blue: 
 * 			Blue part of color (from 0 to 255)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
CP_Gradient *cp_setBgGradientRGB(CP_Context *ctx, double pos, int red, int green, int blue, double alpha)
{
	if(ctx->bgGradient != NULL)
	{
		cp_destroyGradient(ctx->bgGradient);
	}

	ctx->bgGradient = cp_newGradientRGB(pos, red, green, blue, alpha);
	return ctx->bgGradient;
}

/*
 * Function that safely sets the Background gradient (using HTML notation) to
 * the CP_Context structure
 * 		@ctx:
 * 			CP_Context structure that holds the background gradient.
 * 		@value: 
 * 			The HTML notation which used hexadecimal numbers to define the RGB
 * 			values (values like 0xADFAA0)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
CP_Gradient *cp_setBgGradientHTML(CP_Context *ctx, double pos, unsigned int value, double alpha)
{
	if(ctx->bgGradient != NULL)
	{
		cp_destroyGradient(ctx->bgGradient);
	}

	ctx->bgGradient = cp_newGradientHTML(pos, value, alpha);
	return ctx->bgGradient;
}

/*
 * Function that safely sets the Background gradient (using HSV) to the
 * CP_Context structure
 * 		@ctx:
 * 			CP_Context structure that holds the background gradient.
 * 		@hue: 
 * 			Between 0 and 360º. Determines the color family.
 * 		@saturation: 
 * 			Between 0 and 1. Is the degree of strength or purity (how much
 * 			white is added to the color). 1.0 == No white
 * 		@value:
 *			Between 0 and 1. Determines the color brightness (how much black is
 *			added to the color). 1.0 == No Black
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 */
CP_Gradient *cp_setBgGradientHSV(CP_Context *ctx, double pos, double hue, double saturation, double value, double alpha)
{
	if(ctx->bgGradient != NULL)
	{
		cp_destroyGradient(ctx->bgGradient);
	}

	ctx->bgGradient = cp_newGradientHSV(pos, hue, saturation, value, alpha);
	return ctx->bgGradient;
}

/*
 * Function destroys the CP_Context structure and points it to NULL
 * 		@ctx:
 * 			CP_Context structure to be destroyed.
 *
 */
void _cp_destroyContext(CP_Context **pCtx)
{
	CP_Context *ctx;

	ctx = *pCtx;
	// Background Color
	if (ctx->bgColor != NULL)
	{
		free(ctx->bgColor);
		ctx->bgColor = NULL;
	}
	// Background Gradient
	if(ctx->bgGradient != NULL)
	{
		cp_destroyGradient(ctx->bgGradient);
	}
	// Plot Color
	if(ctx->colors != NULL)
	{
		cp_destroySeries(ctx->colors);
	}
	// File Name
	if(ctx->fname != NULL)
	{
		free(ctx->fname);
		ctx->fname = NULL;
	}

	// Free the CP_Context structure and points it to NULL
	free(ctx);
	*pCtx = NULL;
}
