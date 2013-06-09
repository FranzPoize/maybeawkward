
# TODO : library name goes here
project(QuadTree)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
        @ONLY)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
	${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
	QuadTree.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
	QuadTree.cpp
)

add_library(${PROJECT_NAME}
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_HEADERS}
)

include_directories(
)

#target_link_libraries(${PROJECT_NAME}
#)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)
