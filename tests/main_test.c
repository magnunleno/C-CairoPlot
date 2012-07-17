/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 *
 * This file (main_test.c) is part of CairoPlot.
 *
 * CairoPlot is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * CairoPlot is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * CairoPlot. If not, see http://www.gnu.org/licenses/.
 *
 */

#include <stdio.h>
#include <glib.h>
#include <check.h>

int main(void){
	int number_failed;

	SRunner *sr;
	//sr = srunner_create(data_suite());
	//srunner_add_suite(sr, serie_suite());
	//srunner_run_all(sr, CK_NORMAL);

	//number_failed = srunner_ntests_failed (sr);
	//srunner_free(sr);
	return (number_failed == 0)?0:1;
}
