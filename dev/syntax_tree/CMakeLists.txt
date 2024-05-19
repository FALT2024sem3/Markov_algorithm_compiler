cmake_minimum_required(VERSION 3.14)

project(Coco_generation)

# Generating Scanner and Parser with Coco/R
add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/Scanner.cpp
  OUTPUT ${PROJECT_SOURCE_DIR}/Scanner.h
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

# Deleting .old files from generation
set(generated_old
    Scanner.cpp.old
    Scanner.h.old
    Parser.cpp.old
    Parser.h.old
)
file(REMOVE ${generated_old})
