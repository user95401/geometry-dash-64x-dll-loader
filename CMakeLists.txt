cmake_minimum_required(VERSION 3.10.0)

#curly-eureka
set(GAME_VERSION "2.206")
include($ENV{CE64_INCL})

project("XInput1_4")

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

#mod src
file(GLOB_RECURSE SRC
Src/*
#${CURLY_EUREKA_DIR}/somelib/any.cpp to include exact stuff from ce
)
add_library(${PROJECT_NAME} SHARED ${SRC} ${CURLY_EUREKA_SRC})
include_directories(Src)