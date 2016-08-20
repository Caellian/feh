# - Find jansson
# Find the jansson library
#
#  This module defines the following variables:
#     JANSSON_FOUND        - true if XINERAMA_INCLUDE_DIR & XINERAMA_LIBRARY are found
#     JANSSON_LIBRARIES    - Set when XINERAMA_LIBRARY is found
#     JANSSON_INCLUDE_DIRS - Set when XINERAMA_INCLUDE_DIR is found
#
#     JANSSON_INCLUDE_DIR  - where to find jansson.h, etc.
#     JANSSON_LIBRARY      - the XINERAMA library
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

FIND_PATH(JANSSON_INCLUDE_DIRS
        NAMES
        jansson.h
        PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
        /usr/include/jansson
        /usr/local/include/jansson
        /opt/local/include/jansson
        /sw/include/jansson
        )

FIND_LIBRARY(JANSSON_LIBRARIES
        NAMES
        libjansson.so
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
        )

INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(jansson
        REQUIRED_VARS JANSSON_INCLUDE_DIRS JANSSON_LIBRARIES)

# show the JANSSON_INCLUDE_DIRS and JANSSON_LIBRARIES variables only in the advanced view
MARK_AS_ADVANCED(JANSSON_INCLUDE_DIRS JANSSON_LIBRARIES)

