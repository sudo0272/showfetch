cmake_minimum_required(VERSION 3.16)

project(showfetch)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(showfetch src/main.c lib/icon.h lib/lsb_release.h lib/uptime.h lib/getLsbRelease.c lib/getUptime.c lib/printIconRow.c lib/setIconCharacterRow.c lib/setIconColor.c)

set(CMAKE_INSTALL_PREFIX /usr/bin/)

install(TARGETS showfetch
        DESTINATION ${CMAKE_INSTALL_PREFIX}
)

if (OS STREQUAL "Manjaro")
    add_definitions(-DOS=1)
elseif (OS STREQUAL "RHEL")
    add_definitions(-DOS=2)
elseif (OS STREQUAL "CentOS")
    add_definitions(-DOS=3)
elseif (OS STREQUAL "Ubuntu")
    add_definitions(-DOS=4)
else ()
    add_definitions(-DOS=0)
endif()
