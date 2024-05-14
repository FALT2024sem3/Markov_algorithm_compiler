cmake_minimum_required(VERSION 3.20)
project(MarkovCompiler)  # Замените "YourProjectName" на имя вашего проекта

include_directories(tests/Sample-Test1)
# Указываем исходные файлы
set(SOURCES
    Parser.cpp
    Scanner.cpp
    main.cpp
    Markov_algo.cpp.atg
)
find_package(GTest)
# Компилируем исходные файлы
add_executable(Compiler ${SOURCES})
target_link_libraries(Markov_algorithm_compiler{GTEST_LIBRARY})
# Указываем команду для компиляции
target_compile_options(Compiler PRIVATE -std=c++11)

# Указываем, что исполняемый файл должен быть помещен в корневой каталог проекта
set_target_properties(Compiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Указываем команду для выполнения программы
add_custom_command(TARGET Compiler POST_BUILD
    # COMMAND Compiler Markov.txt
    COMMAND del Scanner.cpp.old Scanner.h.old Parser.cpp.old Parser.h.old 
    COMMAND del scanner.o parser.o main.o
)
