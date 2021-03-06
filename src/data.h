/*
 * Copyright (C) 2012 - Magnun Leno
 * 
 * This file (data.h) is part of C-CairoPlot.
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

/*
 * This is a very simple file. It only defines the allocation function for the
 * Data and Point structures.
 *
 */

#ifndef _CP_DATA_H_
#define _CP_DATA_H_

CP_Data *cp_newData(char *label, double value);
CP_Point *cp_newPoint(char *label, double x, double y);

#endif // _CP_DATA_H_
