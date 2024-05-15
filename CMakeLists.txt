cmake_minimum_required(VERSION 3.14)

project(MarkovCompiler LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

include_directories(syntax_tree get_AST Qt_GUI)
add_subdirectory(syntax_tree)

set(SOURCES
    main.cpp
    test.txt

    get_AST/get_AST.cpp
    get_AST/get_AST.h
    get_AST/build_AST.cpp
    get_AST/build_AST.h

    syntax_tree/AST.h
    syntax_tree/Parser.cpp
    syntax_tree/Parser.h
    syntax_tree/Scanner.cpp
    syntax_tree/Scanner.h

    Qt_GUI/mainwindow.cpp
    Qt_GUI/mainwindow.h
    Qt_GUI/mainwindow.ui

    Qt_GUI/codehighlighter.h
    Qt_GUI/codehighlighter.cpp
)

add_executable(MarkovCompiler ${SOURCES})

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
