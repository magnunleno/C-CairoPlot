SET(LIBS ${LIBS} ${CAIRO_LIBRARIES} ${GLIB_LIBRARIES} ${CHECK_LIBRARIES} cairoplot)

INCLUDE_DIRECTORIES(. ../src)

ADD_EXECUTABLE(test_cairoplot 
	util_test.c
	data_test.c
	color_test.c
	series_test.c
	barplot_test.c
	main_test.c
	)

TARGET_LINK_LIBRARIES(test_cairoplot ${LIBS})
ADD_TEST(test_cairoplot ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot)
