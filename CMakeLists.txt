cmake_minimum_required(VERSION 3.14)

project(MarkovCompiler LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generating Scanner and Parser with Coco/R
add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/syntax_tree/Scanner.h
  OUTPUT ${PROJECT_SOURCE_DIR}/syntax_tree/Scanner.cpp
  OUTPUT ${PROJECT_SOURCE_DIR}/syntax_tree/Parser.cpp
  OUTPUT ${PROJECT_SOURCE_DIR}/syntax_tree/Parser.h
  COMMAND cd ${PROJECT_SOURCE_DIR}/syntax_tree
  COMMAND coco Markov_algo.cpp.atg
  DEPENDS syntax_tree/Markov_algo.cpp.atg
  COMMENT "Generating coco files"
)
set(coco_gen_files
    syntax_tree/Scanner.h syntax_tree/Scanner.cpp
    syntax_tree/Parser.cpp syntax_tree/Parser.h
)

add_custom_target(
    coco_gen
    ALL
    DEPENDS ${coco_gen_files}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
include_directories(syntax_tree get_AST Qt_GUI)
set(SOURCES
    get_AST/get_AST.cpp
    get_AST/get_AST.h
    MARKOV.IN
    syntax_tree/AST.h
    syntax_tree/Parser.cpp
    syntax_tree/Scanner.cpp
    syntax_tree/Markov_algo.cpp.atg
        Qt_GUI/mainwindow.cpp
        Qt_GUI/mainwindow.h
        Qt_GUI/mainwindow.ui
        main.cpp
)
add_executable(MarkovCompiler
  ${SOURCES}
        Qt_GUI/test_tables.cpp
        Qt_GUI/test_tables.h
        Qt_GUI/file.cpp
        Qt_GUI/file.h
        Qt_GUI/file.ui
        test.txt
)

add_dependencies(MarkovCompiler coco_gen)

target_link_libraries(MarkovCompiler Qt6::Core)
target_link_libraries(MarkovCompiler Qt6::Widgets)
target_link_libraries(MarkovCompiler Qt6::Gui)

include(GNUInstallDirs)
install(TARGETS MarkovCompiler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled)
endif()
# Deleting .old files from generation
set(generated_old
    ${PROJECT_SOURCE_DIR}/syntax_tree/Scanner.cpp.old
    ${PROJECT_SOURCE_DIR}/syntax_tree/Scanner.h.old
    ${PROJECT_SOURCE_DIR}/syntax_tree/Parser.cpp.old
    ${PROJECT_SOURCE_DIR}/syntax_tree/Parser.h.old
)
file(REMOVE ${generated_old})
