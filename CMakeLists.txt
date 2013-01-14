# CMake file for building CairoPlot

# CMake compatibility issues: don't modify this, please!
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY)
FIND_PACKAGE(PkgConfig REQUIRED)

# allow more human readable "if then else" constructs
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

PROJECT(cairoplot C)

# project version
SET(CP_MAJOR_VERSION 0)
SET(CP_MINOR_VERSION 1)
SET(CP_PATCH_LEVEL 0)

PKG_CHECK_MODULES(CAIRO REQUIRED cairo)
INCLUDE_DIRECTORIES(${CAIRO_INCLUDE_DIRS})
LINK_DIRECTORIES(${CAIRO_LIBRARY_DIRS})
ADD_DEFINITIONS(${CAIRO_CFLAGS_OTHER})

PKG_CHECK_MODULES(CHECK check>=0.9.9)
INCLUDE_DIRECTORIES(${CHECK_INCLUDE_DIRS})
LINK_DIRECTORIES(${CHECK_LIBRARY_DIRS})
ADD_DEFINITIONS(${CHECK_CFLAGS_OTHER})

#ADD_DEFINITIONS(-g -O2 -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
ADD_DEFINITIONS(-g -O2 -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline )

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(man)
IF(CHECK_FOUND)
	ENABLE_TESTING()
	ADD_SUBDIRECTORY(tests)
ELSE()
	message("*** LIBRARY CHECK NOT FOUND")
	ADD_CUSTOM_TARGET(test 
		COMMAND echo -e ' *** ERROR: The test suite requires check 0.9.9 or greater.\\n')
ENDIF()

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
