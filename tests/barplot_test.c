/*
 * Copyright (C) 2012 - Magnun Leno
 *
 * This file (barplot_test.c) is part of C-CairoPlot.
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

#include "barplot_test.h"
START_TEST(test_default_hbar_plot)
{
	CP_Series *series = cp_newDataSeries("Basic Bar Plot");
	cp_appendData(series, NULL, 4);
	cp_appendData(series, NULL, 10);
	cp_appendData(series, NULL, 6);

	cp_barPlot(NULL, NULL, series, CP_PNG);
	cp_destroySeries(series);
	check_equal_null(series);
}END_TEST


START_TEST(test_basic_hbar_plot){
	return;
	//CP_Gradient *bgGradient;
	CP_Context *context = cp_newContext("context_test", 400, 250);
	//cp_setBgColorRGB(context, 120, 150, 170, 1.0);
	//cp_setBgColorHTML(context, 0xF00000, 0.5);
	//cp_setBgColorHSV(context, 0, 0.0, 0.85, 1.0);

	//bgGradient = cp_setBgGradientHSV(context, 0.0, 0.0, 0.5, 0.5, 1.0);
	//cp_addColorStopHSV(bgGradient, 1.0, 0.0, 0.0, 0.85, 1.0);

	//context->left_margin = 0.02;
	//context->right_margin = 0.02;
	//context->bottom_margin = 0.02;
	//context->top_margin = 0.02;

	//context->flatColors = true;

	//context->drawXAxis = true;
	//context->drawYAxis = true;
	//context->drawBox = true;
	//context->drawBackground = true;

	CP_BarPlotSettings *sett = cp_newBarPlotSettings();
	//sett->horBoxPadding = 0.02;
	//sett->verBoxPadding = 0.05;
	//sett->barPadding = 0.01;
	//sett->borderRadius = 0.04;

	CP_Series *series = cp_newDataSeries("Basic Bar Plot");
	cp_appendData(series, "Value 1", 4);
	cp_appendData(series, "Value 2", 10);
	cp_appendData(series, "Value 3", 6);

	cp_barPlot(context, NULL, series, CP_SVG);
	//cp_barPlot(context, series, sett, CP_PNG);
	cp_destroySeries(series);
	free(sett);
	cp_destroyContext(context);

	check_equal_null(context);

}END_TEST

Suite* barplot_suite(void){
	Suite *s = suite_create("Bar Plot Suite");

	TCase *tc_core = tcase_create("Bar Plot Test Case");
	tcase_add_test(tc_core, test_default_hbar_plot);
	tcase_add_test(tc_core, test_basic_hbar_plot);
	suite_add_tcase(s, tc_core);
	return s;
}
