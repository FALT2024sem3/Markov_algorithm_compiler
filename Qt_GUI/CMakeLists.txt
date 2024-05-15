cmake_minimum_required(VERSION 3.14)

project(GUI_library LANGUAGES CXX)

set(SOURCES
   mainwindow.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} coco_library)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
