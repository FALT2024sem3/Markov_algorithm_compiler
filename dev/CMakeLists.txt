cmake_minimum_required(VERSION 3.14)

project(coco_library LANGUAGES CXX)

add_subdirectory(syntax_tree)

set(SOURCES
    syntax_tree/AST.h
    syntax_tree/Includes.h
    syntax_tree/Parser.cpp
    syntax_tree/Scanner.cpp

    get_AST/get_AST.cpp
    get_AST/build_AST.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Gui)

add_library(${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    syntax_tree
    get_AST
)

target_link_libraries(${PROJECT_NAME} Qt6::Gui)
