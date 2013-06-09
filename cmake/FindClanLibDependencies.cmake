# - Try to find ClanLibDependencies
# Once done this will define
#
#  ClanLibDependencies_FOUND - system has ClanLibDependencies
#  ClanLibDependencies_INCLUDE_DIR - the ClanLibDependencies include directory
#  ClanLibDependencies_LIBRARIES - The libraries needed to use ClanLibDependencies
#  ClanLibDependencies_LIBRARY - The ClanLibDependencies library

##
## Use the ClanLibDependencies_DIR environment variable
##
set(ClanLibDependencies_DIR $ENV{ClanLibDependencies_DIR} CACHE PATH "Path to ClanLibDependencies" )

##
## Look for headers and libs
##
find_path(ClanLibDependencies_INCLUDE_DIR zlib.h
    ${ClanLibDependencies_DIR}/include
    ${ClanLibDependencies_DIR}
    $ENV{ClanLibDependencies_DIR}
    NO_DEFAULT_PATH
  )

find_path(ClanLibDependencies_INCLUDE_DIR zlib.h
    $ENV{ClanLibDependencies_HOME}/include
    $ENV{ClanLibDependencies_ROOT}/include
    /usr/local/include
    /usr/include
  )

#
# Looking for the lib
#

IF(NOT ClanLibDependencies_FIND_COMPONENTS)
  SET(ClanLibDependencies_FIND_COMPONENTS
    zlib
	libjpeg
	libpng
	freetype
	pcre
	assimp
	sqlite
	mikmod
	libvorbis
	libogg)
ENDIF(NOT ClanLibDependencies_FIND_COMPONENTS)

# Clear the variable (in case they were forced during a previous "Configure")
set(ClanLibDependencies_LIBRARY_RELEASE ClanLibDependencies_LIBRARY_RELEASE-NOTFOUND CACHE PATH "Path to a library." FORCE)
set(ClanLibDependencies_LIBRARY_DEBUG ClanLibDependencies_LIBRARY_DEBUG-NOTFOUND CACHE PATH "Path to a library." FORCE)

MACRO(FIND_COMPONENT COMPONENT)
find_library(ClanLibDependencies_${COMPONENT}_LIBRARY_RELEASE
    NAMES ${COMPONENT}-static-mt
    PATHS
      ${ClanLibDependencies_DIR}
      ${ClanLibDependencies_DIR}/lib
      ${ClanLibDependencies_DIR}/lib/Win32
      ${ClanLibDependencies_DIR}/bin
    NO_DEFAULT_PATH
  )

find_library(ClanLibDependencies_${COMPONENT}_LIBRARY_RELEASE
    NAMES ${COMPONENT}-static-mt
    PATHS
    ${ClanLibDependencies_DIR}/lib64
    /usr/lib64
)

find_library(ClanLibDependencies_${COMPONENT}_LIBRARY_DEBUG
    NAMES ${COMPONENT}-static-mt-debug
    PATHS
      ${ClanLibDependencies_DIR}
      ${ClanLibDependencies_DIR}/lib
      ${ClanLibDependencies_DIR}/lib/Win32
      ${ClanLibDependencies_DIR}/bin
    NO_DEFAULT_PATH
  )

find_library(ClanLibDependencies_${COMPONENT}_LIBRARY_DEBUG
    NAMES ${COMPONENT}-static-mt
    PATHS
    ${ClanLibDependencies_DIR}/lib64
    /usr/lib64
)
ENDMACRO(FIND_COMPONENT COMPONENT)

# In case only one of the compilation type is available for the library
# we force the other type to the only available one
# if(ClanLibDependencies_LIBRARY_RELEASE)
        # if(NOT ClanLibDependencies_LIBRARY_DEBUG)
                # set(ClanLibDependencies_LIBRARY_DEBUG ${ClanLibDependencies_LIBRARY_RELEASE} CACHE PATH "Path to a library." FORCE)
        # endif(NOT ClanLibDependencies_LIBRARY_DEBUG)
# endif(ClanLibDependencies_LIBRARY_RELEASE)
# if(ClanLibDependencies_LIBRARY_DEBUG)
        # if(NOT ClanLibDependencies_LIBRARY_RELEASE)
                # set(ClanLibDependencies_LIBRARY_RELEASE ${ClanLibDependencies_LIBRARY_DEBUG} CACHE PATH "Path to a library." FORCE)
        # endif(NOT ClanLibDependencies_LIBRARY_RELEASE)
# endif(ClanLibDependencies_LIBRARY_DEBUG)

FOREACH(COMPONENT ${ClanLibDependencies_FIND_COMPONENTS})
  FIND_COMPONENT(${COMPONENT})
  IF(ClanLibDependencies_${COMPONENT}_LIBRARY_RELEASE AND ClanLibDependencies_${COMPONENT}_LIBRARY_DEBUG)
    LIST(APPEND ClanLibDependencies_LIBRARIES debug ${ClanLibDependencies_${COMPONENT}_LIBRARY_DEBUG} optimized ${ClanLibDependencies_${COMPONENT}_LIBRARY_RELEASE})
  ENDIF()
  LIST(APPEND ClanListDependenciesLibraries ClanLibDependencies_${COMPONENT}_LIBRARY_RELEASE ClanLibDependencies_${COMPONENT}_LIBRARY_DEBUG)
ENDFOREACH(COMPONENT)


##	
## handle the QUIETLY and REQUIRED arguments and set ClanLibDependencies_FOUND to TRUE if 
## all listed variables are TRUE
##
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ClanLibDependencies DEFAULT_MSG ClanLibDependencies_INCLUDE_DIR ClanListDependenciesLibraries)

#there seems to be a bug : xxx_FOUND is always output in upper case
# IF(CLANLIBDEPENDENCIES_FOUND)
  # SET( ClanLibDependencies_LIBRARIES optimized ${ClanLibDependencies_LIBRARY_RELEASE} debug ${ClanLibDependencies_LIBRARY_DEBUG})
# ELSE(CLANLIBDEPENDENCIES_FOUND)
  # SET( ClanLibDependencies_LIBRARIES )
# ENDIF(CLANLIBDEPENDENCIES_FOUND)

MARK_AS_ADVANCED( ClanLibDependencies_INCLUDE_DIR ClanLibDependencies_LIBRARIES )
