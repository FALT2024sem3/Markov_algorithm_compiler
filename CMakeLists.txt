cmake_minimum_required(VERSION 3.14)

project(test LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/bin/clang.exe")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
#find_package(CoCo REQUIRED)

# include_directories(${CoCo_INCLUDE_DIRS})

add_executable(test
  get_AST.h
  get_AST.cpp
  AST.h
  main.cpp
  Parser.h
  Parser.cpp
  Parser.frame
  Scanner.h
  Scanner.cpp
  Scanner.frame
  coco.exe
  expr.atg
  makefile
)

target_link_libraries(test Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(test Qt6::Widgets)
target_link_libraries(test Qt6::Gui)
target_link_libraries(test ${CoCo_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
