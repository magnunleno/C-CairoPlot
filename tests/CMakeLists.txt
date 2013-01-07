SET(LIBS ${LIBS} ${CAIRO_LIBRARIES} ${GLIB_LIBRARIES} ${CHECK_LIBRARIES} cairoplot)

INCLUDE_DIRECTORIES(. ../src)

set(SOURCES
	util_test
	data_test
	color_test
	series_test
	barplot_test
	)

FOREACH(executable ${SOURCES})
	ADD_EXECUTABLE(${executable} ${executable}.c)
	TARGET_LINK_LIBRARIES(${executable} ${LIBS})
	ADD_TEST(${executable} ${CMAKE_CURRENT_BINARY_DIR}/${executable})
ENDFOREACH()
