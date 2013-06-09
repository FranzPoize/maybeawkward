### CMakeLists.txt
## 
######################################################################

cmake_minimum_required(VERSION 2.6)

 #It allows to override default CMAKE_INSTALL_PREFIX while the user remains able to change it.
 #Since we have to force the CMAKE_INSTALL_PREFIX value change (then the user changes are not taken into account), we only do it if the user did not define the variable in the GUI.
 #this hack must be present before project() is called
 #source : http://dynamorio.googlecode.com/svn-history/r355/trunk/CMakeLists.txt
 if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(install_override ON)
else (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(install_override OFF)
endif (NOT DEFINED CMAKE_INSTALL_PREFIX)

# TODO : set project name
project(MaybeAwkward)

#If the user has not explicitely defined CMAKE_INSTALL_PREFIX and that the envvar CM_INSTALL_DIR is set, we use it to prefix the install directory
if (install_override)
  if (DEFINED ENV{CM_INSTALL_DIR})
    set (CMAKE_INSTALL_PREFIX "$ENV{CM_INSTALL_DIR}/${PROJECT_NAME}" CACHE PATH "install path" FORCE)
  endif (DEFINED ENV{CM_INSTALL_DIR})
endif (install_override)

## #################################################################
## Setup version numbering
## #################################################################
set(VERSION_MAJOR 0 CACHE STRING "Major version number.")
set(VERSION_MINOR 1 CACHE STRING "Minor version number.")
set(VERSION_BUILD 0 CACHE STRING "Build version number.")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
set(SOVERSION "${VERSION_BUILD}")

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

## #################################################################
## Setup output paths
## #################################################################

set(CMAKE_DEBUG_POSTFIX "d")
### from osg CMakeLists.txt
IF(UNIX AND NOT WIN32 AND NOT APPLE)
  IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET(LIB_POSTFIX "64" CACHE STRING "suffix for 32/64 dir placement")
      MARK_AS_ADVANCED(LIB_POSTFIX)
  ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
ENDIF(UNIX AND NOT WIN32 AND NOT APPLE)
IF(NOT DEFINED LIB_POSTFIX)
    SET(LIB_POSTFIX "")
ENDIF(NOT DEFINED LIB_POSTFIX)


if(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY bin)
  set(ARCHIVE_OUTPUT_DIRECTORY lib)
else(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
  set(ARCHIVE_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
endif(WIN32)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})

## #################################################################
## Setup CMake Modules
## #################################################################
# Where to look for custom FindXXX.cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

## #################################################################
## Setup installation settings
## #################################################################
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#list(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIBRARY_OUTPUT_DIRECTORY}" )

## #################################################################
## Resolve dependencies
## #################################################################
#if(APPLE)
#  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
#  mark_as_advanced(CMAKE_OSX_SYSROOT)
#endif(APPLE)

# TODO : find all your dependencies packages
find_package(ClanLib)
find_package(ClanLibDependencies)
find_package(DirectX)


# Allows the libraries contained in the current project to expose their headers
# to all the source files of the project (syntex eg. #include <{$libname}/${libfile}>)
include_directories(src/libs)

# Directory where custom headers are exported.
# It is notably where ${libname}_Export.h files will be exported for DLL libraries,
#   and those file must be seen for libraries and clients compilations.
include_directories(${CMAKE_BINARY_DIR}/include)
## #################################################################
## Build options
## #################################################################

#option(BUILD_DOCUMENTATION "Build doxygen's documentation" true)
#if (BUILD_DOCUMENTATION)
#    add_subdirectory(docs)
#endif (BUILD_DOCUMENTATION)

# CMake automatically checks this variable value when calling add_library command.
option(BUILD_SHARED_LIBS "Build shared libraries" True)

# 
# C++11 support
# 
option(BUILD_WITH_C++11_SUPPORT "Set the compiler flags/options required to compile with C++11 support" true)
if(BUILD_WITH_C++11_SUPPORT)
	IF(UNIX)
		LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x")
	ENDIF(UNIX)
endif(BUILD_WITH_C++11_SUPPORT)

# Start recursive crawling of the sources
add_subdirectory(src)

