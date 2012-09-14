/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (test_mem_leak.c) is part of C-CairoPlot.
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

#include <stdio.h>
#include <stdlib.h>

#include "cairoplot.h"

void test_colors()
{
	CP_Color *color1 = cp_newColor(0.1, 0.2, 0.3, 0.4);
	CP_Color *color2 = cp_newColor(0.2, 0.3, 0.4, 0.5);
	CP_Color *color3 = cp_newColor(0.3, 0.4, 0.5, 0.6);

	CP_ColorList *colorList = cp_newColorList();
	cp_appendNode(colorList, color1);
	cp_appendNode(colorList, color2);
	cp_appendNode(colorList, color3);

	cp_emptyColorList(colorList);

	int n = 0;
	for (cp_startIter(colorList); colorList->iter; cp_iterNext(colorList))
	{
		n++;
	}
	cp_deleteColorList(colorList);
}
int main(int argc, char const *argv[])
{
	test_colors();
	return 0;
}
