# - Try to find GFLAGS
#
# The following variables are optionally searched for defaults
#  GFLAGS_ROOT_DIR:            Base directory where all GFLAGS components are found
#
# The following are set after configuration is done:
#  GFLAGS_FOUND
#  GFLAGS_INCLUDE_DIRS
#  GFLAGS_LIBRARIES
#  GFLAGS_LIBRARYRARY_DIRS

include(FindPackageHandleStandardArgs)

set(GFLAGS_ROOT_DIR "" CACHE PATH "Folder contains Gflags")

find_path(GFLAGS_INCLUDE_DIR gflags/gflags.h
    PATHS ${GFLAGS_ROOT_DIR})

find_library(GFLAGS_LIBRARY NAMES gflags)


find_package_handle_standard_args(GFlags DEFAULT_MSG GFLAGS_INCLUDE_DIR GFLAGS_LIBRARY)

if(GFLAGS_FOUND)
  set(GFLAGS_INCLUDE_DIRS ${GFLAGS_INCLUDE_DIR})
  set(GFLAGS_LIBRARIES ${GFLAGS_LIBRARY})
  get_filename_component (GFLAGS_LIBRARY_DIRECTORY ${GFLAGS_LIBRARY} DIRECTORY)
  get_filename_component (GFLAGS_LIBRARY_FILENAME ${GFLAGS_LIBRARY} NAME_WE)
  set(GFLAGS_LIBRARIES_STATIC ${GFLAGS_LIBRARY_DIRECTORY}/${GFLAGS_LIBRARY_FILENAME}.a)
  message(STATUS "Found gflags  (include: ${GFLAGS_INCLUDE_DIR}, library: ${GFLAGS_LIBRARY}, static: ${GFLAGS_LIBRARIES_STATIC})")
  mark_as_advanced(GFLAGS_LIBRARY_DEBUG GFLAGS_LIBRARY_RELEASE
    GFLAGS_LIBRARY GFLAGS_INCLUDE_DIR GFLAGS_ROOT_DIR)
  endif()
