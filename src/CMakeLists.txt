#INCLUDE_DIRECTORIES(.)
ADD_LIBRARY(cairoplot SHARED 
	util.c
	data.c 
	color.c 
	series.c 
	context.c 
	plot.c 
	barplot.c 
	)

SET_TARGET_PROPERTIES(cairoplot
                      PROPERTIES
                      VERSION 0.0.1
                      SOVERSION 1)

# Installation of the library
INSTALL(TARGETS cairoplot
        DESTINATION lib
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

# Installation of the include files
INSTALL(FILES cairoplot.h
        DESTINATION include
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
