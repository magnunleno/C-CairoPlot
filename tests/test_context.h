/*
 * Copyright (C) 2012 - Magnun Leno da Silva
 *
 * This file (test_context.h) is part of C-CairoPlot.
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
#include <check.h>
#include <string.h>

#ifndef _CP_TEST_CONTEXT_H_
#define _CP_TEST_CONTEXT_H_

#define check_equal_n(received, expected, err_msg) fail_unless(received == expected, err_msg, received, expected);
#define check_equal_s(received, expected, err_msg) fail_unless(strcmp(received, expected) == 0, err_msg, received, expected);
#define check_equal_null(received) fail_unless(received == NULL, "Variable '%s' wasn't NULL", #received);

#endif // _CP_TEST_CONTEXT_H_


