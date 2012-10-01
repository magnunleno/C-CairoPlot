/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 *
 * This file (context_text.c) is part of C-CairoPlot.
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

#include "context_test.h"

/*
START_TEST(test_context_creation){
	CP_Context *context = cp_newContext("test", 800, 600);
	check_equal_s(context->name, "test", "Expected '%s' as plot name, found '%s'");
	check_equal_n(context->width, 800, "Expected '%i' as plot width, found '%i'");
	check_equal_n(context->height, 600, "Expected '%i' as plot height, found '%i'");
	check_equal_null(context->bgColor);
	check_equal_null(context->plotColor);
	check_equal_null(context->serie);
	cp_deleteContext(context);
	check_equal_null(context);
}END_TEST

START_TEST(test_context_basic_functions){
	CP_Context *context = cp_newContext("test", 800, 600);
	check_equal_null(context->bgColor);

	cp_setBgColor(context, 0.5, 0.6, 0.7);
	check_equal_n(context->bgColor->red, 0.5, "Expected '%i' as bgColor red, found '%i'");
	check_equal_n(context->bgColor->green, 0.6, "Expected '%i' as bgColor green, found '%i'");
	check_equal_n(context->bgColor->blue, 0.7, "Expected '%i' as bgColor blue, found '%i'");

	cp_setBgColor(context, 1.5, 1.6, 1.7);
	check_equal_n(context->bgColor->red, 1.5, "Expected '%i' as bgColor red, found '%i'");
	check_equal_n(context->bgColor->green, 1.6, "Expected '%i' as bgColor green, found '%i'");
	check_equal_n(context->bgColor->blue, 1.7, "Expected '%i' as bgColor blue, found '%i'");
	cp_deleteContext(context);
}END_TEST

START_TEST(test_bg_context){
	CP_Context *context = cp_newContext("context_test", 800, 600);
	context->ft = CP_SVG;
	cp_setBgColor(context, 0.5, 0.6, 0.7);
	cp_initEnv(context);
	cp_drawBackground(context);
	cp_endEnv(context);
	//cp_context(context);
}END_TEST
*/

Suite* context_suite(void){
	Suite *s = suite_create("Context Suite");

	TCase *tc_core = tcase_create("Context Test Case");
	//tcase_add_test(tc_core, test_context_creation);
	//tcase_add_test(tc_core, test_context_basic_functions);
	//tcase_add_test(tc_core, test_bg_context);

	suite_add_tcase(s, tc_core);
	return s;
}
