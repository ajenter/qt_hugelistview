cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(hugelistview)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Widgets CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(hugelistview ${SOURCES})
set_target_properties(hugelistview PROPERTIES AUTOMOC ON)
target_link_libraries(hugelistview Qt::Widgets)

