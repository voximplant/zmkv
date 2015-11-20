include(${CMAKE_MODULE_PATH}/utils.cmake)

find_component(EBML  libebml  ebml  ebml/EbmlVersion.h)

message("EBML_LIBRARIES = ${EBML_LIBRARIES}")
message("EBML_INCLUDE_DIRS = ${EBML_INCLUDE_DIRS}")
message("EBML_VERSION = ${EBML_VERSION}")
