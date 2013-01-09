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

build:
	@mkdir build
	@cd build && cmake ../ 
	@cd build && make

build-v:
	@mkdir build
	@cd build && cmake ../ 
	@cd build && VERBOSE=1 make

install: build
	@cd build && make install

uninstall: build
	@cd build && make uninstall

check: build
	@cd build && CTEST_OUTPUT_ON_FAILURE=true make -d test

clean: 
	@rm -rf build
