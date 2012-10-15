/*
 * Copyright (C) 2012 - Magnun Leno
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
#include "cairo.h"

void test_file_extension()
{
	char *fname = NULL;
	char *name = "teste";
	cp_addFileExtension(&fname, name, CP_SVG);
	free(fname);
}

void test_data_series()
{
	CP_Series *series;

	series = cp_newDataSeries("Series name");
	cp_appendData(series, "label 1", 10.0);
	cp_appendData(series, "label 2", 11.0);
	cp_appendData(series, "label 3", 12.0);

	cp_appendPoint(series, "label 4", 12.0, 12.0);

	int n = 0;
	CP_Data *current = NULL;
	for (cp_startIter(series); series->iter; cp_iterNext(series)){
		current = cp_iterUnpack(series, CP_Data*);
		n++;
	}
	cp_emptySeries(series);
	cp_destroySeries(series);

}
void test_point_lists()
{
	CP_Series *series;
	series = cp_newPointSeries("Series name");
	cp_appendPoint(series, "label 1", 10.0, 11.0);
	cp_appendPoint(series, "label 2", 11.0, 12.0);
	cp_appendPoint(series, "label 3", 12.0, 13.0);

	cp_appendData(series, "label 3", 12.0);

	int n = 0;
	CP_Point *current = NULL;
	for (cp_startIter(series); series->iter; cp_iterNext(series)){
		current = cp_iterUnpack(series, CP_Point*);
		n++;
	}
	cp_destroySeries(series);
}

void test_series_circular_iteration()
{
	double value;
	CP_Series *series = cp_newDataSeries(NULL);
	int count = 0;
	
	cp_appendData(series, NULL, 1.0);
	cp_appendData(series, NULL, 0.5);
	cp_appendData(series, NULL, 0.25);

	// Test iteration in a for loop
	for (cp_startIter(series); series->iter; cp_iterNextCircular(series)){
		value = cp_iterDataAttr(series, value);
		count++;
		if (count == 5)
			break;
	}


	// Test iteration in a while loop
	count = 0;
	cp_startIter(series);
	while (series->iter){
		value = cp_iterDataAttr(series, value);
		count++;
		if (count == 5)
			break;
		cp_iterNextCircular(series);
	}

	cp_destroySeries(series);
}

void test_hbar()
{

	CP_Context *context = cp_newContext("context_test", 400, 250);
	cp_setBgColorHSV(context, 0, 0.0, 0.85, 1.0);
	context->leftMargin = 0.02;
	context->rightMargin = 0.02;
	context->bottomMargin = 0.02;
	context->topMargin = 0.02;
	context->flatColors = true;

	CP_BarPlotSettings *sett = cp_newBarPlotSettings();
	sett->barPadding = 0.01;

	CP_Series *series = cp_newDataSeries("Basic Bar Plot");
	cp_appendData(series, "Value 1", 4);
	cp_appendData(series, "Value 2", 10);
	cp_appendData(series, "Value 3", 6);

	cp_barPlot(context, sett, series, CP_SVG);
	//cp_barPlot(context, series, sett, CP_PNG);
	cp_destroySeries(series);
	free(sett);
	cp_destroyContext(context);

}

int main(int argc, char const *argv[])
{
	test_file_extension();
	test_data_series();
	test_point_lists();
	test_series_circular_iteration();
	test_hbar();
	return 0;
}
