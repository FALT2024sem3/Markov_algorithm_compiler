@echo off
setlocal

rem Сборка основной программы и тестов с использованием CMake
if not exist build mkdir build
cd build
cmake ..
cmake --build .

rem Копируем файл Markov.IN в каталог сборки
if exist ..\Markov.IN (
    copy ..\Markov.IN .
    echo File Markov.IN copied successfully.
) else (
    echo Error: File Markov.IN not found.
    exit /b 1
)

rem Запуск тестов
ctest --rerun-failed --output-on-failure

endlocal
