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

#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lmmmm")

TARGET_LINK_LIBRARIES(test_cairoplot ${LIBS} "-lm")

ADD_TEST(Util_Suite ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot "util")
ADD_TEST(Data_Suite ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot "data")
ADD_TEST(Color_Suite ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot "color")
ADD_TEST(Series_Suite ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot "series")
ADD_TEST(Barplot_Suite ${CMAKE_CURRENT_BINARY_DIR}/test_cairoplot "barplot")
