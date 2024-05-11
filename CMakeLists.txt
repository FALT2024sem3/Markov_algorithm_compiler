cmake_minimum_required(VERSION 3.14)

project(MarkovCompiler LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/Scanner.h
  OUTPUT ${PROJECT_SOURCE_DIR}/Scanner.cpp
  OUTPUT ${PROJECT_SOURCE_DIR}/Parser.cpp
  OUTPUT ${PROJECT_SOURCE_DIR}/Parser.h
  COMMAND cd ${PROJECT_SOURCE_DIR}
  COMMAND coco Markov_algo.cpp.atg
  DEPENDS Markov_algo.cpp.atg
  COMMENT "Generating coco files"
)

set(coco_gen_files
    Scanner.h Scanner.cpp
    Parser.cpp Parser.h
)

add_custom_target(
    coco_gen
    ALL
    DEPENDS ${coco_gen_files}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

add_executable(MarkovCompiler
  get_AST.cpp
  AST.h
  main.cpp
  Parser.cpp
  Scanner.cpp
  MARKOV.IN
  tree_creation.h
  Markov_algo.cpp.atg
)

add_dependencies(MarkovCompiler coco_gen)

target_link_libraries(MarkovCompiler Qt6::Core)
target_link_libraries(MarkovCompiler Qt6::Widgets)
target_link_libraries(MarkovCompiler Qt6::Gui)

include(GNUInstallDirs)
install(TARGETS MarkovCompiler
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(generated_old
    Scanner.cpp.old Scanner.h.old
    Parser.cpp.old Parser.h.old
)

file(REMOVE ${generated_old})
