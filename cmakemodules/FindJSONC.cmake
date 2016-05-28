# - Find json-c
# Find the json-c library
#
#  This module defines the following variables:
#     JSONC_FOUND        - true if XINERAMA_INCLUDE_DIR & XINERAMA_LIBRARY are found
#     JSONC_LIBRARIES    - Set when XINERAMA_LIBRARY is found
#     JSONC_INCLUDE_DIRS - Set when XINERAMA_INCLUDE_DIR is found
#
#     JSONC_INCLUDE_DIR  - where to find json-c.h, etc.
#     JSONC_LIBRARY      - the XINERAMA library
#

#=============================================================================
# Copyright 2016 Tin Svagelj <tin.svagelj.email@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#=============================================================================

if (JSONC_LIBRARIES AND JSONC_INCLUDE_DIRS)
    # in cache already
    set(JSONC_FOUND TRUE)
else (JSONC_LIBRARIES AND JSONC_INCLUDE_DIRS)
    find_path(JSONC_INCLUDE_DIRS
            NAMES
            json.h
            PATHS
            /usr/include
            /usr/local/include
            /opt/local/include
            /sw/include
            /usr/include/json-c
            /usr/local/include/json-c
            /opt/local/include/json-c
            /sw/include/json-c
            )

    # debian uses version suffixes
    # add suffix evey new release
    find_library(JSONC_LIBRARIES
            NAMES
            libjson-c.so
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            /sw/lib
            )

    if (JSONC_INCLUDE_DIRS AND JSONC_LIBRARIES)
        set(JSONC_FOUND TRUE)
    endif (JSONC_INCLUDE_DIRS AND JSONC_LIBRARIES)

    if (JSONC_FOUND)
        if (NOT JSONC_FIND_QUIETLY)
            message(STATUS "Found JSONC: ${JSONC_LIBRARIES}")
        endif (NOT JSONC_FIND_QUIETLY)
    else (JSONC_FOUND)
        if (JSONC_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find JSONC")
        endif (JSONC_FIND_REQUIRED)
    endif (JSONC_FOUND)

    # show the JSONC_INCLUDE_DIRS and JSONC_LIBRARIES variables only in the advanced view
    mark_as_advanced(JSONC_INCLUDE_DIRS JSONC_LIBRARIES)

endif (JSONC_LIBRARIES AND JSONC_INCLUDE_DIRS)
