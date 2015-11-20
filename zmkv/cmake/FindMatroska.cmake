include(${CMAKE_MODULE_PATH}/utils.cmake)

find_component(MATROSKA libmatroska  matroska  matroska/KaxVersion.h)

message("MATROSKA_LIBRARIES = ${MATROSKA_LIBRARIES}")
message("MATROSKA_INCLUDE_DIRS = ${MATROSKA_INCLUDE_DIRS}")
message("MATROSKA_VERSION = ${MATROSKA_VERSION}")
