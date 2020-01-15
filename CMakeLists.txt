cmake_minimum_required(VERSION 2.4)

project(showfetch)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(showfetch src/main.c lib/icon.h lib/lsb_release.h lib/uptime.h lib/getLsbRelease.c lib/getUptime.c lib/printIconRow.c lib/setIconCharacterRow.c lib/setIconColor.c)
