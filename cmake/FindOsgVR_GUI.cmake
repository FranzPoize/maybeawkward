# - Try to find OsgVR_GUI
# Once done this will define
#
#  OsgVR_GUI_FOUND - system has OsgVR_GUI
#  OsgVR_GUI_INCLUDE_DIR - the OsgVR_GUI include directory
#  OsgVR_GUI_LIBRARIES - The libraries needed to use OsgVR_GUI
#  OsgVR_GUI_LIBRARY - The OsgVR_GUI library

##
## Use the OsgVR_GUI_DIR environment variable
##
set(OsgVR_GUI_DIR $ENV{OsgVR_DIR} CACHE PATH "Path to OsgVR_GUI" )

##
## Look for headers and libs
##
find_path(OsgVR_GUI_INCLUDE_DIR Gui/MasterGui.h
    ${OsgVR_GUI_DIR}/include
    ${OsgVR_GUI_DIR}
    $ENV{OsgVR_GUI_DIR}
    NO_DEFAULT_PATH
  )

find_path(OsgVR_GUI_INCLUDE_DIR Gui/MasterGui.h
    $ENV{OsgVR_GUI_HOME}/include
    $ENV{OsgVR_GUI_ROOT}/include
    /usr/local/include
    /usr/include
  )

#
# Looking for the lib
#

# Clear the variable (in case they were forced during a previous "Configure")
set(OsgVR_GUI_LIBRARY_RELEASE OsgVR_GUI_LIBRARY_RELEASE-NOTFOUND CACHE PATH "Path to a library." FORCE)
set(OsgVR_GUI_LIBRARY_DEBUG OsgVR_GUI_LIBRARY_DEBUG-NOTFOUND CACHE PATH "Path to a library." FORCE)

find_library(OsgVR_GUI_LIBRARY_RELEASE
    NAMES libGui Gui
    PATHS
      ${OsgVR_GUI_DIR}
      ${OsgVR_GUI_DIR}/lib
      ${OsgVR_GUI_DIR}/lib/release
      ${OsgVR_GUI_DIR}/bin
    NO_DEFAULT_PATH
  )

find_library(OsgVR_GUI_LIBRARY_RELEASE
    NAMES libGui Gui
    PATHS
    ${OsgVR_GUI_DIR}/lib64
    /usr/lib64
)

find_library(OsgVR_GUI_LIBRARY_DEBUG
    NAMES libGuid Guid
    PATHS
      ${OsgVR_GUI_DIR}
      ${OsgVR_GUI_DIR}/lib
      ${OsgVR_GUI_DIR}/lib/debug
      ${OsgVR_GUI_DIR}/bin
    NO_DEFAULT_PATH
  )

find_library(OsgVR_GUI_LIBRARY_DEBUG
    NAMES libGuid Guid
    PATHS
    ${OsgVR_GUI_DIR}/lib64
    /usr/lib64
)

# In case only one of the compilation type is available for the library
# we force the other type to the only available one
if(OsgVR_GUI_LIBRARY_RELEASE)
        if(NOT OsgVR_GUI_LIBRARY_DEBUG)
                set(OsgVR_GUI_LIBRARY_DEBUG ${OsgVR_GUI_LIBRARY_RELEASE} CACHE PATH "Path to a library." FORCE)
        endif(NOT OsgVR_GUI_LIBRARY_DEBUG)
endif(OsgVR_GUI_LIBRARY_RELEASE)
if(OsgVR_GUI_LIBRARY_DEBUG)
        if(NOT OsgVR_GUI_LIBRARY_RELEASE)
                set(OsgVR_GUI_LIBRARY_RELEASE ${OsgVR_GUI_LIBRARY_DEBUG} CACHE PATH "Path to a library." FORCE)
        endif(NOT OsgVR_GUI_LIBRARY_RELEASE)
endif(OsgVR_GUI_LIBRARY_DEBUG)



##	
## handle the QUIETLY and REQUIRED arguments and set OsgVR_GUI_FOUND to TRUE if 
## all listed variables are TRUE
##
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OsgVR_GUI DEFAULT_MSG OsgVR_GUI_INCLUDE_DIR OsgVR_GUI_LIBRARY_RELEASE OsgVR_GUI_LIBRARY_DEBUG)

#there seems to be a bug : xxx_FOUND is always output in upper case
IF(OSGVR_GUI_FOUND)
  SET( OsgVR_GUI_LIBRARIES optimized ${OsgVR_GUI_LIBRARY_RELEASE} debug ${OsgVR_GUI_LIBRARY_DEBUG})
ELSE(OSGVR_GUI_FOUND)
  SET( OsgVR_GUI_LIBRARIES )
ENDIF(OSGVR_GUI_FOUND)

MARK_AS_ADVANCED( OsgVR_GUI_INCLUDE_DIR OsgVR_GUI_LIBRARIES )
