cmake_minimum_required(VERSION 3.20)
project(MarkovCompiler)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем исходные файлы для основной программы
set(SOURCES
    syntax_tree/Parser.cpp
    syntax_tree/Scanner.cpp
    main.cpp
)

# Компилируем исходные файлы для основной программы
add_executable(Compiler ${SOURCES})

# Укажите путь к директории со скачанным GoogleTest
add_subdirectory(googletest)

# Указываем пути к заголовочным файлам GoogleTest для основной программы
target_include_directories(Compiler PRIVATE ${PROJECT_SOURCE_DIR}/googletest/googletest/include)
target_include_directories(Compiler PRIVATE ${PROJECT_SOURCE_DIR}/googletest/googlemock/include)

# Подключаем библиотеки GoogleTest к исполняемому файлу основной программы
target_link_libraries(Compiler PRIVATE gtest gtest_main)

# Указываем, что исполняемый файл должен быть помещен в корневой каталог проекта
set_target_properties(Compiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Добавляем тесты в CMake
enable_testing()

# Указываем исходные файлы для тестов
set(TEST_SOURCES
    syntax_tree/Parser.cpp
    syntax_tree/Scanner.cpp
    test_main.cpp
)

# Создаем исполняемый файл для тестов
add_executable(CompilerTests ${TEST_SOURCES})

# Указываем пути к заголовочным файлам GoogleTest для тестов
target_include_directories(CompilerTests PRIVATE ${PROJECT_SOURCE_DIR}/googletest/googletest/include)
target_include_directories(CompilerTests PRIVATE ${PROJECT_SOURCE_DIR}/googletest/googlemock/include)

# Подключаем библиотеки GoogleTest к исполняемому файлу тестов
target_link_libraries(CompilerTests PRIVATE gtest gtest_main)

# Указываем, что исполняемый файл тестов должен быть помещен в корневой каталог проекта
set_target_properties(CompilerTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Добавляем тест для CTest
# add_test(NAME CompilerTests COMMAND CompilerTests)
