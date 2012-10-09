/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (color.c) is part of C-CairoPlot.
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
#include "color.h"

/*
 * Return a pointer to the newly allocated Color structure
 * With this function you can define a color with the RGB parameters
 * 		@red: 
 * 			Red part of color (from 0 to 255)
 * 		@green: 
 * 			Green part of color (from 0 to 255)
 * 		@blue: 
 * 			Blue part of color (from 0 to 255)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Color *cp_newColorRGB(int red, int green, int blue, double alpha)
{
	CP_Color *color = cp_new(1, CP_Color);

	//TODO: Check if it's betwen 0 and 255

	color->red = red/255.0;
	color->green = green/255.0;
	color->blue = blue/255.0;
	color->alpha = alpha;

	return color;
}

/*
 * Return a pointer to the newly allocated Color structure
 * With this function you can define a color with the HSV parameters
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
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Color *cp_newColorHSV(double hue, double saturation, double value, double alpha)
{
	int i;
	CP_Color *color;

	color = cp_newColorRGB(0.0, 0.0, 0.0, alpha);

	if(saturation == 0)
	{
		// Achromatic (grey)
		color->red = value;
		color->green = value;
		color->blue = value;
		return color;
	}

	// sector 0 to 5
	hue = hue/60.0;
	i = floor(hue);

	switch(i) {
		case 0:
			color->red = value;
			color->green = value*(1 - saturation*(1 - (hue - i)));
			color->blue = value*(1 - saturation);
			break;
		case 1:
			color->red = value*(1 - saturation*(hue - i));
			color->green = value;
			color->blue = value*(1 - saturation);
			break;
		case 2:
			color->red = value*(1 - saturation);
			color->green = value;
			color->blue = value*(1 - saturation*(1 - (hue - i)));
			break;
		case 3:
			color->red = value*(1 - saturation);
			color->green = value*(1 - saturation*(hue - i));
			color->blue = value;
			break;
		case 4:
			color->red = value*(1 - saturation*(1 - (hue - i)));
			color->green = value*(1 - saturation);
			color->blue = value;
			break;
		default:
			color->red = value;
			color->green = value*(1 - saturation);
			color->blue = value*(1 - saturation*(hue - i));
			break;
	}

	return color;
}

/*
 * Return a pointer to the newly allocated Color structure
 * With this function you can define a color with the HTML notation
 * 		@value: 
 * 			The HTML notation which used hexadecimal numbers to define the RGB
 * 			values (values like 0xADFAA0)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *  
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Color *cp_newColorHTML(unsigned int value, double alpha)
{
	CP_Color *color;

	color = cp_new(1, CP_Color);
	// Shift right 2 bytes and normalizes
	color->red = ((value&0xff0000)>>16)/255.0;
	// Shift right 1 byte and normalizes
	color->green = ((value&0x00ff00)>>8)/255.0;
	color->blue = (value&0x0000ff)/255.0;

	//TODO: Check if it's betwen 0 and 1
	color->alpha = alpha;

	return color;
}

/*
 * Return a pointer to the newly allocated Gradient structure
 * With this function you can define a new gradient and its first stop in the
 * RGB notation
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
 * 		@red: 
 * 			Red part of color (from 0 to 255)
 * 		@green: 
 * 			Green part of color (from 0 to 255)
 * 		@blue: 
 * 			Blue part of color (from 0 to 255)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *  
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Gradient *cp_newGradientRGB(double position, int red, int green, int blue, double alpha)
{
	CP_Gradient *gradient;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorRGB(red, green, blue, alpha);
	gradient->position = position;
	gradient->next = NULL;

	return gradient;
}

/*
 * Return a pointer to the newly allocated Gradient structure
 * With this function you can define a new gradient and its first stop in the
 * HTML notation
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
 * 		@value: 
 * 			The HTML notation which used hexadecimal numbers to define the RGB
 * 			values (values like 0xADFAA0)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *  
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Gradient *cp_newGradientHTML(double position, unsigned int value, double alpha)
{
	CP_Gradient *gradient;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorHTML(value, alpha);
	gradient->position = position;
	gradient->next = NULL;

	return gradient;
}

/*
 * Return a pointer to the newly allocated Gradient structure
 * With this function you can define a new gradient and its first stop in the
 * HSV notation
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
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
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
CP_Gradient *cp_newGradientHSV(double position, double hue, double saturation, double value, double alpha)
{
	CP_Gradient *gradient;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorHSV(hue, saturation, value, alpha);
	gradient->position = position;
	gradient->next = NULL;

	return gradient;
}

/*
 * Adds a new color stop (using RGB notation) to an existing gradient structure
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
 * 		@red: 
 * 			Red part of color (from 0 to 255)
 * 		@green: 
 * 			Green part of color (from 0 to 255)
 * 		@blue: 
 * 			Blue part of color (from 0 to 255)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *  
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
void cp_addColorStopRGB(CP_Gradient *root, double position, int red, int green, int blue, double alpha)
{
	CP_Gradient *gradient;
	CP_Gradient *iter;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorRGB(red, green, blue, alpha);
	gradient->position = position;
	gradient->next = NULL;

	__append_gradient(gradient, iter, root);
}

/*
 * Adds a new color stop (using HTML notation) to an existing gradient structure
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
 * 		@value: 
 * 			The HTML notation which used hexadecimal numbers to define the RGB
 * 			values (values like 0xADFAA0)
 * 		@alpha: 
 * 			Transparency percentage (from 0.0 to 1.0)
 *  
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
void cp_addColorStopHTML(CP_Gradient *root, double position, unsigned int value, double alpha)
{
	CP_Gradient *gradient;
	CP_Gradient *iter;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorHTML(value, alpha);
	gradient->position = position;
	gradient->next = NULL;

	__append_gradient(gradient, iter, root);
}

/*
 * Adds a new color stop (using HSV notation) to an existing gradient structure
 * 		@root: 
 * 			The pointer to the existing Gradient structure
 * 		@position: 
 * 			The position in witch this gradient stop will be positioned (values
 * 			between 0~1)
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
 * All portions of the color (except alpha) are "normalized" and stored in
 * RGB values between 0~1.
 *
 */
void cp_addColorStopHSV(CP_Gradient *root, double position, double hue, double saturation, double value, double alpha)
{
	CP_Gradient *gradient;
	CP_Gradient *iter;

	gradient = cp_new(1, CP_Gradient);
	gradient->color = cp_newColorHSV(hue, saturation, value, alpha);
	gradient->position = position;
	gradient->next = NULL;

	__append_gradient(gradient, iter, root);
}

/*
 * Destroys the gradient and all its colors preventing any memory leak
 * 		@gradient:
 * 			The pointer to the gradient to be destroyed
 *
 */
void _cp_destroyGradient(CP_Gradient **pGradient)
{
	CP_Gradient *iter;

	iter = *pGradient;
	while (iter)
	{
		iter = iter->next;
		free((*pGradient)->color);
		free(*pGradient);
		(*pGradient) = iter;
	}
	pGradient = NULL;
}
