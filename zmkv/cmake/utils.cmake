macro(set_component_found _component )
  if (${_component}_LIBRARIES AND ${_component}_INCLUDE_DIRS)
    message(STATUS "1  - ${_component} found.")
    message(STATUS "1 - ${_component}_LIBRARIES = " ${${_component}_LIBRARIES})
    message(STATUS "1  - ${_component}_INCLUDE_DIRS = " ${${_component}_INCLUDE_DIRS})
    set(${_component}_FOUND TRUE)
  else ()
    message(STATUS "  - ${_component} not found.")
  endif ()
endmacro()

macro(find_component _component _pkgconfig _library _header)

  if (NOT WIN32)
     # use pkg-config to get the directories and then use these values
     # in the FIND_PATH() and FIND_LIBRARY() calls
     find_package(PkgConfig)
     if (PKG_CONFIG_FOUND)
       pkg_check_modules(PC_${_component} ${_pkgconfig})
     endif ()
  endif (NOT WIN32)

  find_path(${_component}_INCLUDE_DIRS ${_header}
    HINTS
      ${PC_LIB${_component}_INCLUDEDIR}
      ${PC_LIB${_component}_INCLUDE_DIRS}
    PATH_SUFFIXES
      ffmpeg
  )

  find_library(${_component}_LIBRARIES NAMES ${_library}
      HINTS
      ${PC_LIB${_component}_LIBDIR}
      ${PC_LIB${_component}_LIBRARY_DIRS}
  )

  set(${_component}_DEFINITIONS  ${PC_${_component}_CFLAGS_OTHER} CACHE STRING "The ${_component} CFLAGS.")
  set(${_component}_VERSION      ${PC_${_component}_VERSION}      CACHE STRING "The ${_component} version number.")

  set_component_found(${_component})

  mark_as_advanced(
    ${_component}_INCLUDE_DIRS
    ${_component}_LIBRARIES
    ${_component}_DEFINITIONS
    ${_component}_VERSION)

endmacro()
