/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 * 
 * This file (color_test.c) is part of C-CairoPlot.
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

#include "color_test.h"

START_TEST(test_color_creation)
{
	CP_Object *colorObj = cp_newColor(0.10, 0.11, 0.12, 0.13);
	check_equal_n(cp_colorAttr(colorObj, red), 0.10, "Found '%f' as red, expected '%f'");
	check_equal_n(cp_colorAttr(colorObj, green), 0.11, "Found '%f' as green, expected '%f'");
	check_equal_n(cp_colorAttr(colorObj, blue), 0.12, "Found '%f' as blue, expected '%f'");
	check_equal_n(cp_colorAttr(colorObj, alpha), 0.13, "Found '%f' as alpha, expected '%f'");
	cp_deleteObject(colorObj);
}END_TEST

START_TEST(test_colorlist_creation)
{
	CP_List *colorList = cp_newList(CP_COLOR);
	cp_appendNode(colorList, cp_newColor(0.1, 0.2, 0.3, 0.4));
	cp_appendNode(colorList, cp_newColor(0.2, 0.3, 0.4, 0.5));
	cp_appendNode(colorList, cp_newColor(0.3, 0.4, 0.5, 0.6));

	check_equal_n(3, colorList->size, "Found %i as size list, expected %i.")
	int n = 0;
	double values[3][4] = {
		{0.1, 0.2, 0.3, 0.4},
		{0.2, 0.3, 0.4, 0.5},
		{0.3, 0.4, 0.5, 0.6}
	};
	double *value;
	CP_Color *color;
	for (cp_startIter(colorList); colorList->iter; cp_iterNext(colorList))
	{
		value = values[n];
		color = cp_iterUnpack(colorList, CP_Color*);
		check_equal_n(value[0], color->red,
				"Found '%f' as red, expected '%f'");
		check_equal_n(value[1], color->green,
				"Found '%f' as green, expected '%f'");
		check_equal_n(value[2], color->blue,
				"Found '%f' as blue, expected '%f'");
		check_equal_n(value[3], color->alpha,
				"Found '%f' as alpha, expected '%f'");
		n++;
	}

	cp_deleteList(colorList);
	check_equal_null(colorList);

}END_TEST

Suite* color_suite(void)
{
	Suite *s = suite_create("Color Suite");

	TCase *tc_core = tcase_create("Color testcase");
	tcase_add_test(tc_core, test_color_creation);
	//tcase_add_test(tc_core, test_colorlist_creation);

	suite_add_tcase(s, tc_core);
	return s;
}
