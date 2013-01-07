/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (barplot.h) is part of C-CairoPlot.
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
#include "context.h"
#include "plot.h"

#ifndef _CP_BARPLOT_H_
#define _CP_BARPLOT_H_

CP_BarPlotSettings *cp_newBarPlotSettings(void);
void cp_drawBar(CP_Context *ctx, CP_BarPlotSettings *sett, double x0, double y0, double width, double height);
void cp_barPlot(CP_Context *context, CP_BarPlotSettings *sett, CP_Series *series, CP_FileType ft);


#endif // _CP_BARPLOT_H_

