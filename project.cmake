set(VERSION_MAJOR 2)
set(VERSION_MINOR 16)
set(VERSION_PATCH 0)
set(VERSION_EXTRA "" CACHE STRING "Version information to append to version string")

set(MAIN_DIR ${CMAKE_INSTALL_PREFIX})
set(MAN_DIR ${CMAKE_INSTALL_PREFIX}/share/man)
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DOC_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/feh)
set(IMAGE_DIR ${CMAKE_INSTALL_PREFIX}/share/feh/images)
set(FONT_DIR ${CMAKE_INSTALL_PREFIX}/share/feh/fonts)
set(DESKTOP_DIR ${CMAKE_INSTALL_PREFIX}/share/applications)
set(EXAMPLE_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/feh/examples)

include(config.cmake)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
if (DEVELOPMENT_BUILD AND NOT VERSION_EXTRA)
    set(VERSION_EXTRA "dev")
endif ()
set(VERSION_STRING ${VERSION_STRING}-${VERSION_EXTRA})

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmakemodules")

if (DEVELOPMENT_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG -O0")
    set(MAN_DEBUG ". This is a debug build.")
else ()
    set(MAN_DEBUG ".")
endif ()

if (HELP)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DINCLUDE_HELP")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")

# Optional dependencies
find_package(CURL)
if (CURL_FOUND AND OPTIONAL_CURL)
    include_directories(${CURL_INCLUDE_DIRS})
    set(MAN_CURL enabled)
else ()
    set(MAN_CURL disabled)
endif ()

find_package(XINERAMA)
if (XINERAMA_FOUND AND OPTIONAL_XINERAMA)
    include_directories(${XINERAMA_INCLUDE_DIRS})
    set(MAN_XINERAMA enabled)
else ()
    set(MAN_XINERAMA disabled)
endif ()

find_package(EXIF)
if (EXIF_FOUND AND OPTIONAL_EXIF)
    include_directories(${EXIF_INCLUDE_DIRS})
    add_definitions(${EXIF_DEFINITIONS})
    set(MAN_EXIF enabled)
else ()
    set(MAN_EXIF disabled)
endif ()

find_package(Jansson)
if (JANSSON_FOUND AND OPTIONAL_JANSSON)
    include_directories(${JANSSON_INCLUDE_DIRS})
    set(MAN_JANSSON enabled)
else ()
    set(MAN_JANSSON disabled)
endif ()

# Required dependencies
find_package(PNG REQUIRED)
if (PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    add_definitions(${PNG_DEFINITIONS})
endif (PNG_FOUND)

find_package(X11 REQUIRED)
if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIRS})
endif (X11_FOUND)

find_package(Imlib2 REQUIRED)
if (IMLIB2_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_IMLIB2_C_FLAGS}")
    include_directories(${IMLIB2_INCLUDE_DIRS})
endif (IMLIB2_FOUND)

execute_process(COMMAND "date" "+%B %d, %Y" OUTPUT_VARIABLE MAN_DATE)

# Uncomment the following line to use dmalloc
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_DMALLOC")