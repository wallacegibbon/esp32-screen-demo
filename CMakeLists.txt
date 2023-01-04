cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS "./components/screen_util")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32-screen-demo)