cmake_minimum_required(VERSION 3.14)

project(MarkovCompiler LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Qt_GUI)
add_subdirectory(dev)

set(SOURCES
    main.cpp
)

add_executable(MarkovCompiler ${SOURCES}
    syntax_tree/Includes.h syntax_tree/MyException.h)

target_link_libraries(MarkovCompiler coco_library)
target_link_libraries(MarkovCompiler GUI_library)

include(GNUInstallDirs)
install(TARGETS MarkovCompiler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled)
endif()
