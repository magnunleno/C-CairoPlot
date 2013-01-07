CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_TESTING()
FIND_PACKAGE(PkgConfig REQUIRED)

PROJECT(cairoplot C)

PKG_CHECK_MODULES(CAIRO REQUIRED cairo)
INCLUDE_DIRECTORIES(${CAIRO_INCLUDE_DIRS})
LINK_DIRECTORIES(${CAIRO_LIBRARY_DIRS})
ADD_DEFINITIONS(${CAIRO_CFLAGS_OTHER})

PKG_CHECK_MODULES(CHECK check)
INCLUDE_DIRECTORIES(${CHECK_INCLUDE_DIRS})
LINK_DIRECTORIES(${CHECK_LIBRARY_DIRS})
ADD_DEFINITIONS(${CHECK_CFLAGS_OTHER})

#ADD_DEFINITIONS(-g -O2 -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
ADD_DEFINITIONS(-g -O2 -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(man)
IF(CHECK_FOUND)
	ADD_SUBDIRECTORY(tests)
ELSE(CHECK_FOUND)
	message("*** LIBRARY CHECK NOT FOUND")
ENDIF(CHECK_FOUND)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)