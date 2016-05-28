cmake_minimum_required(VERSION 3.5)
project(feh)

file(GLOB MAN_FILES "*.pre")
foreach (MAN_FILE ${MAN_FILES})
    message(STATUS "Configuring file ${MAN_FILE}")
    get_filename_component(MAN_FILE_CLEAN ${MAN_FILE} NAME_WE)
    configure_file(${MAN_FILE} ${MAN_FILE_CLEAN}.1)
endforeach (MAN_FILE)
