# - Find ClanLib
# ClanLib is a cross platform SDK geared toward making games. It is
# available from http://clanlib.org.
#
# Please define the following before starting this module
#  ClanLib_MAJOR_VERSION
#  ClanLib_MINOR_VERSION
#
# The following are defined by this module:
#  ClanLib_FOUND - TRUE if ClanLib was found
#  ClanLib_INCLUDE_DIRS - Directory containing the ClanLib headers
#  ClanLib_LIBRARIES - If invoked via FIND_PACKAGE(ClanLib COMPONENTS ...),
#                      will only contain the libraries matching each component.
#                      otherwise, it will contain all ClanLib libraries found.
# For the components Core, App, Display, GL, GUI, GUIStyleSilver, MikMod,
# Network, SDL, Signals, Sound and Vorbis, the following variables are set:
#  ClanLib_${COMPONENT}_LIBRARY - Full path to the component's library.
IF(ClanLib_INCLUDE_DIRS)
  #SET(ClanLib_FIND_QUIETLY TRUE)
ENDIF(ClanLib_INCLUDE_DIRS)

IF (NOT ClanLib_ROOT_DIR)
 SET(ClanLib_ROOT_DIR CACHE PATH "path to clanlib")
ENDIF (NOT ClanLib_ROOT_DIR)

IF(NOT ClanLib_FIND_COMPONENTS)
  SET(ClanLib_FIND_COMPONENTS
    App
    Display
    GL
    GUI
    GUIStyleSilver
    MikMod
    Network
    SDL
    Signals
    Sound
    Vorbis)
ENDIF(NOT ClanLib_FIND_COMPONENTS)

MACRO(ClanLib_MSG MSG)
  IF(NOT ClanLib_FIND_QUIETLY)
    MESSAGE(STATUS ${MSG})
  ENDIF(NOT ClanLib_FIND_QUIETLY)
ENDMACRO(ClanLib_MSG)

MACRO(ClanLib_ERR MSG)
  IF(ClanLib_FIND_REQUIRED)
    MESSAGE(SEND_ERROR ${MSG})
  ELSE(ClanLib_FIND_REQUIRED)
    ClanLib_MSG(${MSG})
  ENDIF(ClanLib_FIND_REQUIRED)
ENDMACRO(ClanLib_ERR)

MACRO(ClanLib_FIND_COMPONENT COMPONENT)
  ClanLib_MSG("Checking for Clan${COMPONENT}")
  FIND_LIBRARY(ClanLib_${COMPONENT}_LIBRARY_DEBUG clan${COMPONENT}-static-mt-debug
	${ClanLib_ROOT_DIR}/lib/Win32 /lib /usr/lib /usr/local/lib
    DOC "Library name for clan${COMPONENT}.")
  FIND_LIBRARY(ClanLib_${COMPONENT}_LIBRARY_RELEASE clan${COMPONENT}-static-mt
    ${ClanLib_ROOT_DIR}/lib/Win32 /lib /usr/lib /usr/local/lib
    DOC "Library name for clan${COMPONENT}.")
  FIND_LIBRARY(ClanLib_${COMPONENT}_LIBRARY libclan${ClanLib_MAJOR_VERSION}${ClanLib_MINOR_VERSION}${COMPONENT}.a
    ${ClanLib_ROOT_DIR}/lib /lib /usr/lib /usr/local/lib
    DOC "Library name for clan${COMPONENT}.")
	
  IF(ClanLib_${COMPONENT}_LIBRARY_RELEASE)
    SET(ClanLib_${COMPONENT}_FOUND TRUE)
    ClanLib_MSG("Checking for Clan${COMPONENT} -- ${ClanLib_${COMPONENT}_LIBRARY_RELEASE}")
  ELSE(ClanLib_${COMPONENT}_LIBRARY_RELEASE)
    SET(ClanLib_${COMPONENT}_FOUND FALSE)
    IF(ClanLib_FIND_REQUIRED_${COMPONENT})
      ClanLib_ERR("Checking for Clan${COMPONENT} -- not found")
    ELSE(ClanLib_FIND_REQUIRED_${COMPONENT})
      ClanLib_MSG("Checking for Clan${COMPONENT} -- not found")
    ENDIF(ClanLib_FIND_REQUIRED_${COMPONENT})
  ENDIF(ClanLib_${COMPONENT}_LIBRARY_RELEASE)
ENDMACRO(ClanLib_FIND_COMPONENT)

ClanLib_MSG("Checking for ClanLib")
FIND_PATH(ClanLib_INCLUDE_DIRS ClanLib/core.h
  ${ClanLib_ROOT_DIR}/include ${ClanLib_ROOT_DIR}/include/ClanLib-${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION}
  /usr/local/include          /usr/local/include/ClanLib-${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION}
  /usr/include                /usr/include/ClanLib--${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION}
  DOC "Where to find the ClanLib includes.")
IF(ClanLib_INCLUDE_DIRS)
  ClanLib_MSG("Checking for ClanLib -- headers")
ELSE(ClanLib_INCLUDE_DIRS)
  ClanLib_ERR("Checking for ClanLib -- headers not found")
ENDIF(ClanLib_INCLUDE_DIRS)

ClanLib_FIND_COMPONENT(Core)
IF(ClanLib_INCLUDE_DIRS AND ClanLib_Core_LIBRARY_RELEASE)
  SET(ClanLib_FOUND TRUE)
  SET(ClanLib_LIBRARIES debug ${ClanLib_Core_LIBRARY_DEBUG} optimized ${ClanLib_Core_LIBRARY_RELEASE})
ELSE(ClanLib_INCLUDE_DIRS AND ClanLib_Core_LIBRARY_RELEASE)
  SET(ClanLib_FOUND FALSE)
ENDIF(ClanLib_INCLUDE_DIRS AND ClanLib_Core_LIBRARY_RELEASE)

ClanLib_MSG("Checking for other ClanLib components")
FOREACH(COMPONENT ${ClanLib_FIND_COMPONENTS})
  ClanLib_FIND_COMPONENT(${COMPONENT})
  IF(ClanLib_${COMPONENT}_LIBRARY_RELEASE)
    LIST(APPEND ClanLib_LIBRARIES debug ${ClanLib_${COMPONENT}_LIBRARY_DEBUG} optimized ${ClanLib_${COMPONENT}_LIBRARY_RELEASE})
  ENDIF(ClanLib_${COMPONENT}_LIBRARY_RELEASE)
ENDFOREACH(COMPONENT)

MARK_AS_ADVANCED(
  ClanLib_INCLUDE_DIRS
  ClanLib_App_LIBRARY
  ClanLib_Core_LIBRARY
  ClanLib_Display_LIBRARY
  ClanLib_GL_LIBRARY
  ClanLib_GUI_LIBRARY
  ClanLib_GUIStyleSilver_LIBRARY
  ClanLib_MikMod_LIBRARY
  ClanLib_Network_LIBRARY
  ClanLib_SDL_LIBRARY
  ClanLib_Signals_LIBRARY
  ClanLib_Sound_LIBRARY
  ClanLib_Vorbis_LIBRARY
)