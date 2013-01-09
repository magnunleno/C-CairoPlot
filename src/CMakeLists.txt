#INCLUDE_DIRECTORIES(.)

SET(SOURCES
	util.c
	data.c
	color.c
	series.c
	context.c
	plot.c
	barplot.c
	)

ADD_LIBRARY(cairoplot SHARED ${SOURCES})
ADD_LIBRARY(cairoplot_static STATIC ${SOURCES})

SET_TARGET_PROPERTIES(cairoplot
                      PROPERTIES
		      VERSION ${CP_MAJOR_VERSION}.${CP_MINOR_VERSION}.${CP_PATCH_LEVEL}
		      SOVERSION ${CP_MAJOR_VERSION})

# Installation of the library
INSTALL(TARGETS cairoplot
        DESTINATION lib
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

INSTALL(TARGETS cairoplot_static
        DESTINATION lib
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

# Installation of the include files
INSTALL(FILES cairoplot.h
        DESTINATION include
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
