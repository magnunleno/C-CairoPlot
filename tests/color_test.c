/*
 * Copyright (C) 2012 - Magnun Leno
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

START_TEST(test_color_rgb_creation)
{
	// Tests simple color declaration and values storage
	CP_Color *color = cp_newColorRGB(255, 0, 10, 0.13);
	check_equal_n(color->red, 1.0, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, 0.0, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, (double)10/255, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 0.13, "Found '%f' as alpha, expected '%f'");
	free(color);
}END_TEST

START_TEST(test_color_html_creation)
{
	// Tests simple color declaration and values storage
	CP_Color *color = cp_newColorHTML(0xF0A0D5, 0.8);
	check_equal_n(color->red, (double)240/255, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, (double)160/255, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, (double)213/255, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 0.8, "Found '%f' as alpha, expected '%f'");
	free(color);
}END_TEST

START_TEST(test_color_hsv_creation)
{
	// Tests simple color declaration and values storage
	CP_Color *color = cp_newColorHSV(300, 0.5, 0.5, 0.8);
	check_equal_n(color->red, 0.5, "Found '%f' as red, expected '%f'");
	check_equal_n(color->green, 0.25, "Found '%f' as green, expected '%f'");
	check_equal_n(color->blue, 0.5, "Found '%f' as blue, expected '%f'");
	check_equal_n(color->alpha, 0.8, "Found '%f' as alpha, expected '%f'");
	free(color);
}END_TEST

START_TEST(test_gradient_rgb_creation_and_iteration)
{
	// Tests color gradients iterations and values attributions
	CP_Gradient *iter;
	CP_Gradient *gradient;
	int count = 0;

	gradient = cp_newGradientRGB(0.1, 250, 200, 100, 0.5);
	cp_addColorStopRGB(gradient, 0.5, 200, 150, 100, 0.8);
	cp_addColorStopRGB(gradient, 1.0, 150, 50, 100, 1.0);

	double pos_values[3] = {0.1, 0.5, 1.0};
	double rgb_values[3][4] = {
		{(double)250/255, (double)200/255, (double)100/255, 0.5},
		{(double)200/255, (double)150/255, (double)100/255, 0.8},
		{(double)150/255, (double)50/255, (double)100/255, 1.0},
	};

	for (iter=gradient; iter; iter=iter->next)
	{
		check_equal_n(iter->position, pos_values[count], "Found '%f' as gradient stop, expected '%f'");
		check_equal_n(iter->color->red, rgb_values[count][0], "Found '%f' as red, expected '%f'");
		check_equal_n(iter->color->green, rgb_values[count][1], "Found '%f' as green, expected '%f'");
		check_equal_n(iter->color->blue, rgb_values[count][2], "Found '%f' as blue, expected '%f'");
		check_equal_n(iter->color->alpha, rgb_values[count][3], "Found '%f' as alpha, expected '%f'");
		count++;
	}
	cp_destroyGradient(gradient);
	check_equal_null(gradient);
}END_TEST

START_TEST(test_gradient_hsv_creation_and_iteration)
{
	// Tests color gradients iterations and values attributions
	CP_Gradient *iter;
	CP_Gradient *gradient;
	int count = 0;

	gradient = cp_newGradientHSV(0.2, 300, 0.4, 0.4, 0.5);
	cp_addColorStopHSV(gradient, 0.5, 300, 0.3, 0.3, 0.8);
	cp_addColorStopHSV(gradient, 1.0, 300, 0.5, 0.5, 1.0);

	double pos_values[3] = {0.2, 0.5, 1.0};
	double rgb_values[3][4] = {
		{0.4, 0.24, 0.4, 0.5},
		{0.3, 0.21, 0.3, 0.8},
		{0.5, 0.25, 0.5, 1.0},
	};

	for (iter=gradient; iter; iter=iter->next)
	{
		check_equal_n(iter->position, pos_values[count], "Found '%f' as gradient stop, expected '%f'");
		check_equal_n(iter->color->red, rgb_values[count][0], "Found '%f' as red, expected '%f'");
		check_equal_n(iter->color->green, rgb_values[count][1], "Found '%f' as green, expected '%f'");
		check_equal_n(iter->color->blue, rgb_values[count][2], "Found '%f' as blue, expected '%f'");
		check_equal_n(iter->color->alpha, rgb_values[count][3], "Found '%f' as alpha, expected '%f'");
		count++;
	}
	cp_destroyGradient(gradient);
	check_equal_null(gradient);
}END_TEST

Suite* color_suite(void)
{
	Suite *s = suite_create("Color Suite");

	TCase *tc_core = tcase_create("Colors creation");
	tcase_add_test(tc_core, test_color_rgb_creation);
	tcase_add_test(tc_core, test_color_html_creation);
	tcase_add_test(tc_core, test_color_hsv_creation);
	suite_add_tcase(s, tc_core);

	tc_core = tcase_create("Gradients creation and iteration");
	tcase_add_test(tc_core, test_gradient_rgb_creation_and_iteration);
	tcase_add_test(tc_core, test_gradient_hsv_creation_and_iteration);
	suite_add_tcase(s, tc_core);
	return s;
}
