/*
 * Copyright (C) 2012 - Magnun Leno
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

#include "util.h"
#include "series.h"

// Silence is golden...

#ifndef _CP_CONTEXT_H_
#define _CP_CONTEXT_H_

CP_Context* cp_newContext(char *name, int width, int height);

// Background Color
void cp_setBgColorRGB(CP_Context *ctx, int red, int green, int blue, double alpha);
void cp_setBgColorHTML(CP_Context *ctx, unsigned int value, double alpha);
void cp_setBgColorHSV(CP_Context *ctx, double hue, double saturation, double value, double alpha);

// Background Gradient
CP_Gradient *cp_setBgGradientRGB(CP_Context *ctx, double pos, int red, int green, int blue, double alpha);
CP_Gradient *cp_setBgGradientHTML(CP_Context *ctx, double pos, unsigned int value, double alpha);
CP_Gradient *cp_setBgGradientHSV(CP_Context *ctx, double pos, double hue, double saturation, double value, double alpha);

// Destroy
void _cp_destroyContext(CP_Context **pCtx);
#define cp_destroyContext(ctx) _cp_destroyContext(&ctx)

#endif // _CP_CONTEXT_H_

