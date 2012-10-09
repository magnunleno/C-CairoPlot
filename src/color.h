/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (color.h) is part of C-CairoPlot.
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

/*
 * Hi stranger! This file defines the "colors" functions that C-CairoPlot use
 * to "communicate" with the Cairo Library. By colors I mean anything that have
 * to do with colors basics (conversion from HSV->RGB, HTML encoding->RGB,
 * memory allocation and deallocation and gradients)
 *
 * Have fun!
 *
 */


#ifndef _CP_COLOR_H_
#define _CP_COLOR_H_

#include "util.h"

/* Basic Color Structure Allocation */
CP_Color *cp_newColorRGB(int red, int green, int blue, double alpha);
CP_Color *cp_newColorHTML(unsigned int value, double alpha);
CP_Color *cp_newColorHSV(double hue, double saturation, double value, double alpha);

/* Gradient Structure Allocation */
CP_Gradient *cp_newGradientRGB(double position, int red, int green, int blue, double alpha);
CP_Gradient *cp_newGradientHTML(double position, unsigned int value, double alpha);
CP_Gradient *cp_newGradientHSV(double position, double hue, double saturation, double value, double alpha);

/* Gradient series management */
void cp_addColorStopRGB(CP_Gradient *root, double position, int red, int green, int blue, double alpha);
void cp_addColorStopHTML(CP_Gradient *root, double position, unsigned int value, double alpha);
void cp_addColorStopHSV(CP_Gradient *root, double position, double hue, double saturation, double value, double alpha);

void _cp_destroyGradient(CP_Gradient **pGradient);
#define cp_destroyGradient(gradient) _cp_destroyGradient(&gradient)

/**** LIBRARY ONLY MACROS ****/
#define __append_gradient(gradient, iter, root) 		\
	iter = root; 										\
	while(iter) 										\
	{ 													\
		if (iter->next == NULL) 						\
			break; 										\
		iter = iter->next; 								\
	} 													\
	iter->next = gradient

#endif // _CP_COLOR_H_
