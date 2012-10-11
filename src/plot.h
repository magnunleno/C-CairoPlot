/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (plot.h) is part of C-CairoPlot.
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
#include "context.h"

/*
 * This file defines the basic functions to any plot, such as envidonment
 * initialization, background drawing, axis drawing, grid drawing...
 *
 */

#ifndef _CP_PLOT_H_
#define _CP_PLOT_H_

#define DEFAULT_LINE_WIDTH 0.005

void cp_drawBackground(CP_Context *context);
void cp_drawXAxis(CP_Context *ctx, double x0, double y0, double x1);
void cp_drawYAxis(CP_Context *ctx, double x0, double y0, double y1);
void cp_drawBox(CP_Context *ctx, double x0, double y0, double x1, double y1);
void cp_drawYMarks(CP_Context *ctx, double x0, double y0, double step, int count);

void cp_drawGrid(CP_Context *ctx, double maxData, double x0, double y0, double width, double height);

void cp_initEnv(CP_Context *context, CP_FileType ft);
void cp_endEnv(CP_Context *context, CP_FileType ft);


#endif // _CP_PLOT_H_

