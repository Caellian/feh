cmake_minimum_required(VERSION 3.5)
project(feh)

file(GLOB SOURCE_FILES
        "json/*.h"
        "json/*.c"
        "*.h"
        "*.c")

configure_file(
        "${PROJECT_SOURCE_DIR}/constants.h.in"
        "${PROJECT_BINARY_DIR}/constants.h"
)

configure_file(
        "${PROJECT_SOURCE_DIR}/help.raw"
        "${PROJECT_BINARY_DIR}/help.inc"
)

add_executable(feh ${SOURCE_FILES})

target_link_libraries(feh
        m
        ${X11_LIBRARIES}
        ${IMLIB2_LIBRARIES}
        ${PNG_LIBRARIES})

if (CURL_FOUND)
    target_link_libraries(feh ${CURL_LIBRARIES})
endif (CURL_FOUND)

if (EXIF_FOUND)
    target_link_libraries(feh ${EXIF_LIBRARIES})
endif (EXIF_FOUND)

if (XINERAMA_FOUND)
    target_link_libraries(feh ${XINERAMA_LIBRARIES})
endif (XINERAMA_FOUND)

if (JANSSON_FOUND)
    target_link_libraries(feh ${JANSSON_LIBRARIES})
endif (JANSSON_FOUND)