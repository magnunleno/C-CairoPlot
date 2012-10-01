#
# Copyright (C) 2012 - Magnun Leno da Silva
# 
# This file (Makefile) is part of C-CairoPlot.
# 
# C-CairoPlot is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
# 
# C-CairoPlot is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
# 
# You should have received a copy of the GNU General Public License along with
# C-CairoPlot. If not, see http://www.gnu.org/licenses/.
#

###############################################################################
#              This Makefile is temporary. Test purposes ONLY!                #
###############################################################################

RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
CLR_END=\033[0m
ifeq ('$(CC)', 'cc')
	CC=gcc
endif

VPATH=src tests
libdeps=cairo glib-2.0 check
CFLAGS=`pkg-config --cflags $(libdeps)`
LIBS=`pkg-config --libs $(libdeps)`
FLAGS=-Wall -I./src -L./build

ALL=util object color list data 
TESTS=util.test color.test data.test list.test main.test
BUILD_DIR=build
TESTS_DIR=tests
TESTS:=$(addprefix $(BUILD_DIR)/$(TESTS_DIR)/,$(TESTS))
OBJECTS=$(addsuffix .o,$(ALL))
OBJECTS:=$(addprefix $(BUILD_DIR)/,$(OBJECTS))

TEST_COMPILE=$(CC) -c $(TESTS_DIR)/$(addsuffix _test, $*).c $(FLAGS) $(CFLAGS) -o $@
ALLTEST_COMPILE=$(CC) $(TESTS) $(FLAGS) $(CFLAGS) -lcairoplot -o $(BUILD_DIR)/$(TESTS_DIR)/test_all.run $(LIBS)
OBJ_COMPILE=$(CC) -c -fPIC $(CFLAGS) src/$(notdir $(@:.o=.c)) -o $@

.PHONY: all clean build_static_libs check test_mem_leak

all: $(OBJECTS) build/libcairoplot.so build/libcairoplot.a
	@echo
	@echo "$(YELLOW)»»» Building all: $(CLR_END)$(ALL_COMPILE)"

check: build/libcairoplot.so build/libcairoplot.a $(TESTS)
	@echo "$(YELLOW)»»» Building all tests: $(CLR_END)$(ALLTEST_COMPILE)"
	@$(ALLTEST_COMPILE)
	@chmod	770 build/$(TESTS_DIR)/test_all.run
	@echo
	@echo "$(YELLOW)»»» Running tests: $(CLR_END)$(ALL_COMPILE)"
	@LD_LIBRARY_PATH=./build ./build/$(TESTS_DIR)/test_all.run

build/libcairoplot.so: $(OBJECTS)
	@echo "$(YELLOW)»»» Creating shared libraries: $(CLR_END)"
	@gcc -shared -fPIC -Wl,-soname,libcairoplot.so $(OBJECTS) $(CFLAGS) -o build/libcairoplot.so.1.0.1 $(LIBS)
	@if ! test -L build/libcairoplot.so; then \
		cd build && ln -s libcairoplot.so.1.0.1 libcairoplot.so; \
	fi

build/libcairoplot.a: $(OBJECTS)
	@echo "$(YELLOW)»»» Creating static libraries: $(CLR_END)"
	@ar rcs build/libcairoplot.a $(OBJECTS)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)
	@mkdir $(BUILD_DIR)/$(TESTS_DIR)

test_mem_leak: build/libcairoplot.so build/libcairoplot.a $(TESTS)
	@echo "$(YELLOW)»»» Building all tests: $(CLR_END)$(ALLTEST_COMPILE)"
	@$(CC) $(TESTS_DIR)/test_mem_leak.c $(FLAGS) -lcairoplot $(CFLAGS) -o build/tests/test_mem_leak.run
	chmod	770 build/$(TESTS_DIR)/test_mem_leak.run
	@LD_LIBRARY_PATH=./build ./build/$(TESTS_DIR)/test_mem_leak.run
	@LD_LIBRARY_PATH=./build valgrind --leak-check=full ./build/$(TESTS_DIR)/test_mem_leak.run

clean:
	@rm -rf build
	@echo "$(GREEN)Exit, left stage...$(CLR_END)"
	@echo

####### Prerequisites
$(BUILD_DIR)/util.o: util.h util.c
$(BUILD_DIR)/object.o: object.h object.c
$(BUILD_DIR)/color.o: color.h color.c
$(BUILD_DIR)/data.o: data.h data.c
$(BUILD_DIR)/list.o: list.h list.c
$(BUILD_DIR)/context.o: context.h context.c

####### Build
$(BUILD_DIR)/$(TESTS_DIR)/%.test: %_test.c
	@echo "$(YELLOW)»»» Building tests $@: $(CLR_END)$(TEST_COMPILE)"
	@$(TEST_COMPILE)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "$(YELLOW)»»» $@:$(CLR_END) $(OBJ_COMPILE)"
	@$(OBJ_COMPILE)
